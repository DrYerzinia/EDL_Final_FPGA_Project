
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unistd.h>

#include "altera_avalon_pio_regs.h"
#include "system.h"

#include "kiss.h"

// Tiny JPEG library to shrink image for transmission
#define TJE_IMPLEMENTATION
#include "tiny_jpeg.h"

// VIDEO DMA CONTROLLER defines
#define VIDEO_DMA_CONTROLLER_BASE							0x8001000
#define VIDEO_DMA_CONTROLLER__BUFFER_OFFSET					0
#define VIDEO_DMA_CONTROLLER__BACK_BUFFER_OFFSET			4
#define VIDEO_DMA_CONTROLLER__STATUS_CONTROL_OFFSET			12

#define VIDEO_DMA_CONTROLLER__CONTROL__MASK__EN				0xFFFFFFFB // TODO fix name and invert
#define VIDEO_DMA_CONTROLLER__STATUS_CONTROL__MASK__SWAP	0x00000001

#define VIDEO_DMA_CONTROLLER__BUFFER_A_BASE					0x06000000;
#define VIDEO_DMA_CONTROLLER__BUFFER_B_BASE					0x07000000;

// KISS Interface defines
typedef enum {
	KISS_PACKET_OPCODES__LOG			= 0x81,
	KISS_PACKET_OPCODES__JPEG_IMAGE 	= 0x82,
	KISS_PACKET_OPCODES__RAW_IMAGE 		= 0x83
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

#define JTAG_UART_BASE 0x8001030

#define JTAG_UART_DATA ((volatile int*) JTAG_UART_BASE)
#define JTAG_UART_CONTROL ((volatile int*) (JTAG_UART_BASE+4))

#define PWM_BASE 0x8001000

static void set_motors(int speed_left, int speed_right){

  if(speed_left == 0){               // Stop left motor if input 0
    //digitalWrite(pinCW_Right,LOW);
    //digitalWrite(pinCC_Right,LOW);
  } else if(speed_left < 0){
    //digitalWrite(pinCW_Left,HIGH);
    //digitalWrite(pinCC_Left,LOW);
    speed_left *= -1;
  } else {
    //digitalWrite(pinCW_Left,LOW);
    //digitalWrite(pinCC_Left,HIGH);
  }

  if(speed_right == 0){              // Stop right motor if input 0
    //digitalWrite(pinCW_Right,LOW);
    //digitalWrite(pinCC_Right,LOW);
  } else if(speed_right < 0){
    //digitalWrite(pinCW_Right,HIGH);
    //digitalWrite(pinCC_Right,LOW);
    speed_right *= -1;
  } else {
    //digitalWrite(pinCW_Right, LOW);
    //digitalWrite(pinCC_Right,HIGH);
  }

  // Set the PWM values
  volatile uint32_t pwm_command = ( ((uint32_t)speed_right) << 8) | ((uint32_t)speed_left);
  IOWR_ALTERA_AVALON_PIO_DATA(PWM_BASE, pwm_command);

}

static void jtag_kiss_send(uint8_t byte){

         // Wait for room in buffer
         while( ! ( (*JTAG_UART_CONTROL) & 0xffff0000 ) );

         // Send byte
         *JTAG_UART_DATA = byte;

}

uint8_t jpeg_image_buffer[IMAGE_SIZE];

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

}

int main()
{

	// Setup JTAG kiss interface
	jtag_kiss.send = jtag_kiss_send;

	// Send startup message
	//const char hello_world[] = "\x81Hello from Nios II!";
	//kiss_send_packet(&jtag_kiss, (const uint8_t *) hello_world, sizeof(hello_world) - 1);


	// Motor ramp test
	while(1){
		int i;
		for(i = 0; i < 255; i++){
			set_motors(i, i);
			usleep(10000);
		}
	}

	/*
	usleep(1000000);


	// Send image
	const static bool jpeg_transfer = false;
	if(jpeg_transfer){
		take_jpeg_picture_and_send_to_jtag();
	} else {
		// Naive Slow Transfer
		take_raw_picture_and_send_to_jtag();
	}
	*/
	while(1);

	return 0;

}
