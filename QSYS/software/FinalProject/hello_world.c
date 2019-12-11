
/* TODO
 * Execute code from flash for faster access
 * Create onboard block RAM memory for small regularly used variables to speed up execution
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unistd.h>

#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "system.h"

#include "kiss.h"

#include "pid.h"

// Tiny JPEG library to shrink image for transmission
//#define TJE_IMPLEMENTATION
//#include "tiny_jpeg.h"

#define JTAG_UART_BASE					0x8001090

#define VIDEO_DMA_CONTROLLER_BASE		0x8001080

#define ENCODER_LEFT_BASE 				0x8001030
#define ENCODER_RIGHT_BASE 				0x8001040

#define PWM_BASE						0x8001050

#define ON_BUTTON_BASE					0x8001010

#define MOTOR_DIRECTION_BASE			0x8001020

#define UPTIME_BASE						0x8001000

#define LINE_DETECT_BASE				0x80010a0

// VIDEO DMA CONTROLLER defines
#define VIDEO_DMA_CONTROLLER__BUFFER_OFFSET					0
#define VIDEO_DMA_CONTROLLER__BACK_BUFFER_OFFSET			4
#define VIDEO_DMA_CONTROLLER__STATUS_CONTROL_OFFSET			12

#define VIDEO_DMA_CONTROLLER__CONTROL__MASK__EN				0xFFFFFFFB // TODO fix name and invert
#define VIDEO_DMA_CONTROLLER__STATUS_CONTROL__MASK__SWAP	0x00000001

#define VIDEO_DMA_CONTROLLER__BUFFER_A_BASE					0x06000000;
#define VIDEO_DMA_CONTROLLER__BUFFER_B_BASE					0x07000000;

// KISS Interface defines
typedef enum {

	KISS_PACKET_OPCODES__DO_LOOP		= 0x50,
	KISS_PACKET_OPCODES__DO_SPIN_5		= 0x51,
	KISS_PACKET_OPCODES__MOVE_FORWARD	= 0x52,
	KISS_PACKET_OPCODES__MOVE_BACKWARD	= 0x53,
	KISS_PACKET_OPCODES__TURN_LEFT		= 0x54,
	KISS_PACKET_OPCODES__TURN_RIGHT		= 0x55,

	KISS_PACKET_OPCODES__GET_LINE_POS	= 0x70,
	KISS_PACKET_OPCODES__FOLLOW_LINE	= 0x71,

	KISS_PACKET_OPCODES__LOG			= 0x81,
	KISS_PACKET_OPCODES__JPEG_IMAGE 	= 0x82,
	KISS_PACKET_OPCODES__RAW_IMAGE 		= 0x83,
	KISS_PACKET_OPCODES__STATES			= 0x90

} KISS_PACKET_OPCODES;

// Camera image properties
#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480
#define IMAGE_CHANNELS 3

#define IMAGE_SIZE   ( IMAGE_HEIGHT * IMAGE_WIDTH )
#define IMAGE_BYTES  ( IMAGE_WIDTH * IMAGE_HEIGHT * IMAGE_CHANNELS )

// Image data buffer location
volatile uint32_t * const image_buffer_a = (uint32_t *) VIDEO_DMA_CONTROLLER__BUFFER_A_BASE;
volatile uint32_t * const image_buffer_b = (uint32_t *) VIDEO_DMA_CONTROLLER__BUFFER_B_BASE;

kiss_t jtag_kiss;

uint8_t jtag_kiss_rx_buffer[100];

#define JTAG_UART_DATA ((volatile int*) JTAG_UART_BASE)
#define JTAG_UART_CONTROL ((volatile int*) (JTAG_UART_BASE+4))


#define BLE_UART_BASE 0x80000c0
#define BLE_UART_IRQ 1
#define BLE_UART_IRQ_INTERRUPT_CONTROLLER_ID 0

#define BLE_UART_RX_DATA ((volatile int*) BLE_UART_BASE)
#define BLE_UART_TX_DATA ((volatile int*) (BLE_UART_BASE+4))
#define BLE_UART_STATUS  ((volatile int*) (BLE_UART_BASE+8))
#define BLE_UART_CONTROL ((volatile int*) (BLE_UART_BASE+12))
#define BLE_UART_DIVISOR ((volatile int*) (BLE_UART_BASE+16))
#define BLE_UART_EOP     ((volatile int*) (BLE_UART_BASE+20))

#define JTAG_UART__MASK__RVALID		0x00008000

#define max( a, b ) ( ( a > b) ? a : b )
#define min( a, b ) ( ( a < b) ? a : b )

static void jtag_kiss_send(uint8_t byte){

         // Wait for room in buffer
         while( ! ( (*JTAG_UART_CONTROL) & 0xffff0000 ) );

         // Send byte
         *JTAG_UART_DATA = byte;

}

static void camera_dma_enable(bool enable){

	volatile uint32_t * control = (uint32_t *)(VIDEO_DMA_CONTROLLER_BASE + VIDEO_DMA_CONTROLLER__STATUS_CONTROL_OFFSET);
	if(enable){
		*control |= ~VIDEO_DMA_CONTROLLER__CONTROL__MASK__EN;
	} else {
		*control &= VIDEO_DMA_CONTROLLER__CONTROL__MASK__EN;
	}

}

static volatile uint32_t * swap_buffer(){

	volatile uint32_t * buffer_address = (uint32_t *)(VIDEO_DMA_CONTROLLER_BASE + 	VIDEO_DMA_CONTROLLER__BUFFER_OFFSET);
	volatile uint32_t * back_buffer_address = (uint32_t *)(VIDEO_DMA_CONTROLLER_BASE + 	VIDEO_DMA_CONTROLLER__BACK_BUFFER_OFFSET);

	volatile uint32_t * status_control = (uint32_t *)(VIDEO_DMA_CONTROLLER_BASE + VIDEO_DMA_CONTROLLER__STATUS_CONTROL_OFFSET);

	volatile uint32_t * current_image_buffer;

	// instead of disabling DMA trigger buffer swap
	{

		// Setup back buffer register for swap
		if(*buffer_address == (uint32_t) image_buffer_a){
			current_image_buffer = image_buffer_a;
			*back_buffer_address = (uint32_t) image_buffer_b;
		} else {
			current_image_buffer = image_buffer_b;
			*back_buffer_address = (uint32_t) image_buffer_a;
		}

		// Trigger buffer swap
		*buffer_address = 0;

		// Wait for buffer swap
		while(*status_control & VIDEO_DMA_CONTROLLER__STATUS_CONTROL__MASK__SWAP);

	}

	return current_image_buffer;

}


static void  take_raw_picture_and_send_to_jtag(void){

	volatile uint32_t * current_image_buffer = swap_buffer();

	kiss_start(&jtag_kiss);

	// Inject packet type
	uint8_t packet_type = KISS_PACKET_OPCODES__RAW_IMAGE;
	kiss_send_data(&jtag_kiss, &packet_type, 1);


	uint32_t i;
	for (i = 0; i < IMAGE_SIZE; i++) {

		uint8_t pixel_data[3];

		pixel_data[0] = (current_image_buffer[i] & 0x00FF0000) >> 16;
		pixel_data[1] = (current_image_buffer[i] & 0x0000FF00) >> 8;
		pixel_data[2] = (current_image_buffer[i] & 0x000000FF) >> 0;

		kiss_send_data(&jtag_kiss, pixel_data, 3);

	}

	kiss_end(&jtag_kiss);
}

static void jpeg_jtag_send(void* context, void* data, int size) {

	kiss_send_data(&jtag_kiss, data, size);

};

/*
uint8_t jpeg_image_buffer[IMAGE_SIZE];

static void take_jpeg_picture_and_send_to_jtag(void) {

	volatile uint32_t * current_image_buffer = swap_buffer();

	// copy image buffer to correct format
	uint32_t i;
	for(i = 0; i < IMAGE_SIZE; i++){
		jpeg_image_buffer[i*3 + 0] = (current_image_buffer[i] & 0x00FF0000) >> 16;
		jpeg_image_buffer[i*3 + 1] = (current_image_buffer[i] & 0x000000FF) >> 0;
		jpeg_image_buffer[i*3 + 2] = (current_image_buffer[i] & 0x0000FF00) >> 8;
	}

	kiss_start(&jtag_kiss);

	// Inject packet type
	uint8_t packet_type = KISS_PACKET_OPCODES__JPEG_IMAGE;
	kiss_send_data(&jtag_kiss, &packet_type, 1);

	// Convert image to JPEG and send over JTAG
 	tje_encode_with_func(
		jpeg_jtag_send,
		NULL, // Context is null TODO should it be?
		1,
		IMAGE_WIDTH,
		IMAGE_HEIGHT,
		IMAGE_CHANNELS,
		jpeg_image_buffer // TODO select image buffer based on above swap
	);

	kiss_end(&jtag_kiss);

}*/

/**
 * Gets system uptime in ms
 *
 * @return uptime in ms
 */
static uint32_t read_uptime(void){

	return IORD_ALTERA_AVALON_PIO_DATA(UPTIME_BASE);

}

// CORE FUNCTIONS /////////////////////////////////////////////////////////////

/*************************************************
 *                   DEFINES
 *************************************************/

// Distance defines in state units (quadrature decoder output divided by 1000)
#define TWO_FEET	4.250f            // State change corresponding to moving 2 feet
#define CM_100		6.960f            // State change corresponding to moving 100 cm
#define TURN_180	6.080f            // State change corresponding to a 180 degree turn
#define TURN_90		3.040f		     // State change corresponding to a 90 degree turn

// State reached tolerance for transitioning states
#define TOLERANCE 	0.10f            // Positional tolerance for setpoint reached in state machine

// PWM thresholds
const uint8_t maxPWM = 220;
const uint8_t minimum_zero = 1;        // Speed where we stop motors
const uint8_t minimum_stable_pwm = 60; // Minimum PWM with steady motor rotation

/*************************************************
 *             PID Loop Globals
 *************************************************/

PID_t drive_pid;
PID_t yaw_pid;

static uint32_t read_line_detect(void){

	return IORD_ALTERA_AVALON_PIO_DATA(LINE_DETECT_BASE);

}

/**
 * Reads the left encoder ticks
 *
 * @return left encoder ticks
 */
static int32_t read_encoder_left(void){

	return IORD_ALTERA_AVALON_PIO_DATA(ENCODER_LEFT_BASE);

}

/**
 * Reads the right encoder ticks
 *
 * @return right encoder ticks
 */
static int32_t read_encoder_right(void){

	return IORD_ALTERA_AVALON_PIO_DATA(ENCODER_RIGHT_BASE);

}

/**
 * Sets the motors forward/reverse and speed reference using a -255 to 255 pwm output for each motor
 *
 * @param speed_left The desired PWM control signal for the left motor
 * @param speed_left The desired PWM control signal for the right motor
 */
static void set_motors(int16_t speed_left, int16_t speed_right){

	uint32_t motor_direction = 0;

	if(speed_left == 0){               // Stop left motor if input 0
		motor_direction |= 0b00;
	} else if(speed_left < 0){
		motor_direction |= 0b01;
		speed_left *= -1;
	} else {
		motor_direction |= 0b10;
	}

	if(speed_right == 0){              // Stop right motor if input 0
		motor_direction |= 0b0000;
	} else if(speed_right < 0){
		motor_direction |= 0b1000;
		speed_right *= -1;
	} else {
		motor_direction |= 0b0100;
	}

	// Set motor directions
	IOWR_ALTERA_AVALON_PIO_DATA(MOTOR_DIRECTION_BASE, motor_direction);

	// Set the PWM values
	volatile uint32_t pwm_command = ( ((uint32_t)speed_right) << 8) | ((uint32_t)speed_left);
	IOWR_ALTERA_AVALON_PIO_DATA(PWM_BASE, pwm_command);

}

/**
 * Scales the PWM value from max scale ot match the maximum possible motor speed
 *
 * @param output The desired PWM control signal for the motor before scaling
 */
double scale_output(double output){

  return output * (maxPWM / 255.0);

}

/**
 * Prevents PWM output value from exeding maximum range and keeps it from
 * the zone where the motor jumps, opting for a higher minimum speed before
 * cutoff
 *
 * @param output The desired PWM control signal for the motor before correction
 */
int normalize_output(double output){

  output = max(min(output, 255.0), -255.0);

  if( output < minimum_zero && output > -1 * minimum_zero){

    output = 0;

  } else if( output < minimum_stable_pwm && output > -1 * minimum_stable_pwm ){

    if(output > 0){
      output = minimum_stable_pwm;
    } else {
      output = -1 * minimum_stable_pwm;
    }

  }

  return output;

}

// Init motor pin states
static void motor_init(void){

	// Default state to motors not enabled
	//digitalWrite(pinCW_Left, LOW);   // stop clockwise
	//digitalWrite(pinCC_Left, LOW);   // stop counter-clockwise

	// Stop motors
	set_motors(0, 0);

	/* Note: We limit the PID loop output range to 1/2 full scale so we don't
	* end up saturating the motors preventing small yaw control adjustments
	* when the drive PID is at full output.
	*/

	// Setup the Drive PID

	drive_pid.kp   = 15;
	drive_pid.ki   = 0;
	drive_pid.kd   = 2;
	drive_pid.max  =  120;					// Limit range to -128 to 128
	drive_pid.min  = -120;
	drive_pid.mode = FORWARD;
	//drive_pid.SetSampleTime(20);          // 50 Hz update rate

	// Setup the Yaw PID
	yaw_pid.kp   = 20;
	yaw_pid.ki   = 0;
	yaw_pid.kd   = 2;
	yaw_pid.max  =  140;
	yaw_pid.min  = -140;
	yaw_pid.mode = REVERSE;

}

typedef struct {

	uint16_t num_states;

	fp_t * drive_changes;
	fp_t * yaw_changes;

} control_t;

fp_t figure_8_drive_changes[] =
	{
		CM_100,
		0.0f,
		2 * CM_100,
		0.0f,
		CM_100,
		0.0f,
		CM_100,
		0.0f,
		2 * CM_100,
		0.0f,
		CM_100,
		0.0f
	};
fp_t figure_8_yaw_changes[] =
	{
		0.0f,
		TURN_90,
		0.0f,
		-1 * TURN_90,
		0.0f,
		-1 * TURN_90,
		0.0f,
		-1 * TURN_90,
		0.0f,
		TURN_90,
		0.0f,
		TURN_90
	};
control_t figure_8_ctrl = {
	.num_states = 12,
	.drive_changes = figure_8_drive_changes,
	.yaw_changes = figure_8_yaw_changes
};

fp_t spin_5_drive_changes[] = { 0.0f };
fp_t spin_5_yaw_changes[] = { 4 * 5 * TURN_90 };
control_t spin_5_times_ctrl = {
	.num_states = 1,
	.drive_changes = spin_5_drive_changes,
	.yaw_changes = spin_5_yaw_changes
};

fp_t spin_1_drive_changes[] = { 0.0f };
fp_t spin_1_yaw_changes[] = { 4 * TURN_90 };
control_t spin_1_time_ctrl = {
	.num_states = 1,
	.drive_changes = spin_1_drive_changes,
	.yaw_changes = spin_1_yaw_changes
};

fp_t forward_drive_changes[] = { 0.5f };
fp_t forward_yaw_changes[] = { 0.0f };
control_t forward_ctrl = {
	.num_states = 1,
	.drive_changes = forward_drive_changes,
	.yaw_changes = forward_yaw_changes
};

fp_t backward_drive_changes[] = { -0.5f };
fp_t backward_yaw_changes[] = { 0.0f };
control_t backward_ctrl = {
	.num_states = 1,
	.drive_changes = backward_drive_changes,
	.yaw_changes = backward_yaw_changes
};

fp_t left_drive_changes[] = { 0.0f };
fp_t left_yaw_changes[] = { -0.25f * TURN_90 };
control_t left_ctrl = {
	.num_states = 1,
	.drive_changes = left_drive_changes,
	.yaw_changes = left_yaw_changes
};

fp_t right_drive_changes[] = { 0.0f };
fp_t right_yaw_changes[] = { 0.25f * TURN_90 };
control_t right_ctrl = {
	.num_states = 1,
	.drive_changes = right_drive_changes,
	.yaw_changes = right_yaw_changes
};

static void wait_button_press(void){

	// wait for ON switch
	while ( ( IORD_ALTERA_AVALON_PIO_DATA(ON_BUTTON_BASE) & 1 )  == 0){
		usleep(1000);
	}

}
static void motor_control_loop(control_t * instructions, bool wait){

	motor_init();

	//  Initialize drive and yaw setpoints to 0
	drive_pid.setpoint = 0.0f;
	yaw_pid.setpoint = 0.0f;

	// State machine variables to allow transition between pre-programmed motions
	int state = 0;
	bool state_change = false;

	// State machine finished, allows exiting of task loop to wait for another switch press to run again
	bool done = false;

	if(wait){
		wait_button_press();
	}

	usleep(100000);    // Allow user to step away before robot moves

	// Reset state variables
	done = false;
	state = 0;

	// setup encoder offsets
	float left_offset = read_encoder_left() / 1000.0f;
	float right_offset = read_encoder_right() / 1000.0f;

	// reset state
	drive_pid.setpoint = 0.0f;
	yaw_pid.setpoint = 0.0f;

	float last_time = read_uptime() / 1000.0;

	// Run control loops while robot is operating
	while(!done){

		float uptime = read_uptime() / 1000.0;

		float dt = uptime - last_time;

		// scale encoder outputs to be more consistent with PID gains
		float left_value = ( read_encoder_left() / 1000.0f ) - left_offset;
		float right_value = ( read_encoder_right() / 1000.0f ) - right_offset;

		// Convert encoder values to Drive and Yaw state values for control
		float drive_value = ( left_value + right_value ) / 2.0f;
		float yaw_value = left_value - right_value;

		/*{
			uint8_t states_msg[9];

			states_msg[0] = KISS_PACKET_OPCODES__STATES;
			memcpy(states_msg + 1, &dt, sizeof(dt));
			memcpy(states_msg + 5, &yaw_value, sizeof(yaw_value));

			kiss_send_packet(&jtag_kiss, (const uint8_t *) states_msg, 9);
		}*/

		// Compute the control efforts from the PID loops
		fp_t drive_output = pid_compute(&drive_pid, drive_value, dt);
		fp_t yaw_output   = pid_compute(&yaw_pid, yaw_value, dt);

		// Mix the control efforts into the motors
		int16_t left_output = normalize_output(scale_output(drive_output) + scale_output(yaw_output));
		int16_t right_output = normalize_output(scale_output(drive_output) - scale_output(yaw_output));

		// send the control efforts to the motors
		set_motors(left_output, right_output);

		// Wait for drive and yaw goals to be met, then start a state transition
		if(drive_value < drive_pid.setpoint + TOLERANCE && drive_value > drive_pid.setpoint - TOLERANCE
		   && yaw_value < yaw_pid.setpoint + TOLERANCE && yaw_value > yaw_pid.setpoint - TOLERANCE){
			state++;
			state_change = true;
		}

		// Switch states to perform a figure 8 motion
		if(state_change){

			if(state == ( instructions->num_states + 1) ){
				set_motors(0, 0);
				done = true;
			} else {
				drive_pid.setpoint += instructions->drive_changes[state - 1];
				yaw_pid.setpoint += instructions->yaw_changes[state - 1];
			}

			state_change = false;

		}

		last_time = uptime;

	}

}

// Tests //////////////////////////////////////////////////////////////////////

static void encoder_test(){

	while(1){

		float left_value = read_encoder_left() / 1000.0f;
		float right_value = read_encoder_right() / 1000.0f;

		uint8_t states_msg[9];

		states_msg[0] = KISS_PACKET_OPCODES__STATES;
		memcpy(states_msg + 1, &left_value, sizeof(left_value));
		memcpy(states_msg + 5, &right_value, sizeof(right_value));

		kiss_send_packet(&jtag_kiss, (const uint8_t *) states_msg, 9);

		usleep(10000);
	}

}

static void follow_line(){

	uint32_t i;
	for(i = 0; i < 100000; i++){

		// line position -8 to 8
		int8_t line = read_line_detect() - 8;

		int8_t yaw_bias = 0;

		if(line < 0){
			yaw_bias = line * -10;
			//set_motors(-1 * 15, 15);
		} else if(line > 0){
			yaw_bias = line * -10;
			//set_motors(15, -1 * 15);
		} else {
			//set_motors(0, 0);
			//break;
		}

		set_motors(35 - yaw_bias, 35 + yaw_bias);

		usleep(100);

	}

	set_motors(0, 0);

}

static void motor_ramp_test(){

	// Motor ramp test
	while(1){

		int16_t i;

		// Ramp up
		for(i = -255; i < 255; i++){
			set_motors(i, i);
			usleep(2000);
		}

		// Ramp down
		for(i = 255; i > -255; i--){
			set_motors(i, i);
			usleep(2000);
		}

		set_motors(0, 0);
		usleep(1000000);

	}

}

static void image_download_test(){

	// Send image
	const static bool jpeg_transfer = false;
	if(jpeg_transfer){
		//take_jpeg_picture_and_send_to_jtag();
	} else {
		// Naive Slow Transfer
		take_raw_picture_and_send_to_jtag();
	}

}

// MAIN ///////////////////////////////////////////////////////////////////////

#define BLE_BUFFER_LEN 20

uint8_t ble_buffer[BLE_BUFFER_LEN] = {0};
uint8_t ble_buffer_position = 0;

void ble_uart_handler(void * context){

	if( (*BLE_UART_STATUS & 0x0080 ) != 0){

		uint8_t byte = *BLE_UART_RX_DATA;

		ble_buffer[ble_buffer_position++] = byte;

		if((byte & 0xFF) == '\n'){

			/*
			 * Receive commands
			 *
			 * If first character then motor command
			 * M+000,+000 for stop
			 * M+255,+255 forward
			 * M-255,-255 reverse
			 * M-255,+255 right
			 */
			if( ble_buffer[0] == 'M' && ble_buffer_position == 11 ){

				int16_t left = 1;
				int16_t right = 1;

				// Deal with negatives
				if(ble_buffer[1] == '-'){
					left = -1;
				}
				if(ble_buffer[6] == '-'){
					right = -1;
				}

				// Convert text to magnitude
				left *=   ( ( ble_buffer[2] - '0' ) * 100 )
						+ ( ( ble_buffer[3] - '0' ) *  10 )
						+ ( ( ble_buffer[4] - '0' )       );

				right *=   ( ( ble_buffer[7] - '0' ) * 100 )
						 + ( ( ble_buffer[8] - '0' ) *  10 )
						 + ( ( ble_buffer[9] - '0' )       );

				set_motors(left, right);

			}

			// Echo back
			/*
			uint8_t i;
			for(i = 0; i < ble_buffer_position; i++){
				while( ! ( (*BLE_UART_STATUS) & 0x0040 ) );
				*BLE_UART_TX_DATA = ble_buffer[i];
			}
			 */

			ble_buffer_position = 0;

		}

	}

}

bool packet_ready = false;
uint16_t packet_length = 0;

void jtag_uart_handler(void * context){

	bool has_data = true;

	while(has_data){

		// Read UART and see if there is data
		uint32_t data = *JTAG_UART_DATA;
		if( (data & JTAG_UART__MASK__RVALID ) != 0){

			uint16_t len = kiss_rx_byte(&jtag_kiss, (uint8_t)( data & 0xFF ) );

			if(len > 0){

				packet_ready = true;
				packet_length = len;

			}

		} else {

			has_data = false;

		}

	}

}


int main()
{

	set_motors(0, 0);

	// Setup JTAG kiss interface
	jtag_kiss.send 				 = jtag_kiss_send;
	jtag_kiss.rx_state 			 = KISS_STATE__NORMAL;
	jtag_kiss.rx_buffer 		 = jtag_kiss_rx_buffer;
	jtag_kiss.rx_buffer_position = 0;

	//alt_ic_isr_register(JTAG_UART_IRQ, JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID, jtag_uart_handler, NULL, NULL);

	*JTAG_UART_CONTROL = 0; // Disable interrupts
	alt_irq_register(JTAG_UART_IRQ, NULL,  jtag_uart_handler);
	*JTAG_UART_CONTROL = 0x00000001; // Read interrupt

	*BLE_UART_CONTROL = 0; // Disable interrupts
	alt_irq_register(BLE_UART_IRQ, NULL,  ble_uart_handler);
	*BLE_UART_CONTROL = 0x0000080; // Read interrupt

	// Send startup message
	const char hello_world[] = "\x81Hello from Nios II!";
	kiss_send_packet(&jtag_kiss, (const uint8_t *) hello_world, sizeof(hello_world) - 1);

	usleep(1000000);

	//while(1){
	//	wait_button_press();
	//	follow_line();
	//}

	while(1){

		if(packet_ready){

			packet_ready = false;

			switch(jtag_kiss.rx_buffer[0]){

				case KISS_PACKET_OPCODES__DO_LOOP:
					motor_control_loop(&figure_8_ctrl, false);
					break;

				case KISS_PACKET_OPCODES__DO_SPIN_5:
					motor_control_loop(&spin_5_times_ctrl, false);
					break;

				case KISS_PACKET_OPCODES__MOVE_FORWARD:
					motor_control_loop(&forward_ctrl, false);
					break;

				case KISS_PACKET_OPCODES__MOVE_BACKWARD:
					motor_control_loop(&backward_ctrl, false);
					break;

				case KISS_PACKET_OPCODES__TURN_LEFT:
					motor_control_loop(&left_ctrl, false);
					break;

				case KISS_PACKET_OPCODES__TURN_RIGHT:
					motor_control_loop(&right_ctrl, false);
					break;


				case KISS_PACKET_OPCODES__GET_LINE_POS:
					{

						uint8_t line_detect_message[2];

						line_detect_message[0] = KISS_PACKET_OPCODES__GET_LINE_POS;
						line_detect_message[1] = read_line_detect();

						kiss_send_packet(&jtag_kiss, (const uint8_t *) line_detect_message, 2);
					}
					break;

				case KISS_PACKET_OPCODES__FOLLOW_LINE:
					follow_line();
					break;

				case KISS_PACKET_OPCODES__RAW_IMAGE:
					image_download_test();
					break;

				default:
					break;

			}

		}

	}

	//image_download_test();
	//motor_control_loop();
	//motor_ramp_test();
	//encoder_test();

	return 0;

}
