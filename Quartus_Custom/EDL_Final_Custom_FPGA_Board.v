// Copyright (C) 2018  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details.

module EDL_Final_Custom_FPGA_Board
(
// {ALTERA_ARGS_BEGIN} DO NOT REMOVE THIS LINE!

	BLUETOOTH_FPGA_RX,
	BLUETOOTH_FPGA_TX,
	BUMP,
	CAM_D,
	CAM_HSYNC,
	CAM_PAN_PWM,
	CAM_PCLK,
	CAM_TILT_PWM,
	CAM_VSYNC,
	CAM_XVCLK,
	CLK_50MHZ,
	DRAM_A,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_D,
	DRAM_LDQM,
	DRAM_RAS_N,
	DRAM_UDQM,
	DRAM_WE_N,
	ENC_1A,
	ENC_1B,
	ENC_2A,
	ENC_2B,
	GPIO,
	I2C_0_SCL,
	I2C_0_SDA,
	LIDAR_FPGA_RX,
	LIDAR_FPGA_TX,
	LIDAR_MOTOR_EN,
	M1_C,
	M1_CW,
	M1_REF,
	M2_C,
	M2_CW,
	M2_REF,
	ON_BUTTON,
	ON_BUTTON_LED,
	PDM_CLK,
	SD_CLK,
//	SD_CMD,
	SD_DATA,
	PDM
// {ALTERA_ARGS_END} DO NOT REMOVE THIS LINE!

);

// {ALTERA_IO_BEGIN} DO NOT REMOVE THIS LINE!
input			BLUETOOTH_FPGA_RX;
output			BLUETOOTH_FPGA_TX;
input	[2:0]	BUMP;
input	[7:0]	CAM_D;
input			CAM_HSYNC;
output			CAM_PAN_PWM;
input			CAM_PCLK;
output			CAM_TILT_PWM;
input			CAM_VSYNC;
output			CAM_XVCLK;
input			CLK_50MHZ;
output	[12:0]	DRAM_A;
output	[1:0]	DRAM_BA;
output			DRAM_CAS_N;
output			DRAM_CKE;
output			DRAM_CLK;
output			DRAM_CS_N;
inout	[15:0]	DRAM_D;
output			DRAM_LDQM;
output			DRAM_RAS_N;
output			DRAM_UDQM;
output			DRAM_WE_N;
input			ENC_1A;
input			ENC_1B;
input			ENC_2A;
input			ENC_2B;
inout	[2:0]	GPIO;
inout			I2C_0_SCL;
inout			I2C_0_SDA;
input			LIDAR_FPGA_RX;
output			LIDAR_FPGA_TX;
output			LIDAR_MOTOR_EN;
output			M1_C;
output			M1_CW;
output			M1_REF;
output			M2_C;
output			M2_CW;
output			M2_REF;
input			ON_BUTTON;
output			ON_BUTTON_LED;
output			PDM_CLK;
output			SD_CLK;
//output			SD_CMD;
inout	[3:0]	SD_DATA;
input	[5:0]	PDM;

// {ALTERA_IO_END} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_BEGIN} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_END} DO NOT REMOVE THIS LINE!

wire signed [31:0] LEFT_ENC;
wire signed [31:0] RIGHT_ENC;

wire [23:0] RGB_DATA;
wire 			SOP;
wire 			EOP;
wire 			VALID;
wire 			READY;

wire [7:0] PWM_1;
wire [7:0] PWM_2;

wire ON_OFF;

wire LOCKED;

wire [31:0] UPTIME;

wire [3:0] LINE_DETECT;

wire PCM_CLK;

wire [15:0] PCM_1, PCM_2, PCM_3;

wire [31:0] PEAK_1, PEAK_2, PEAK_3;
wire 			PEAK_RESET;

system_clocks sys_clks (

	.inclk0			(CLK_50MHZ),

	.c0				(CAM_XVCLK),
	.c1				(PWM_CLOCK),
	.c2				(PDM_CLK),
	.c3				(SYS_CLK),
	.c4				(DRAM_CLK),

	.locked        (LOCKED)
	
);

Uptime uptime(

    .clk				(PWM_CLOCK),
    .uptime			(UPTIME)

);

PWM pwm_1(
    .clk				(PWM_CLOCK),
    .PWM_in			(PWM_1),
    .PWM_out		(M1_REF)
);

PWM pwm_2(
    .clk				(PWM_CLOCK),
    .PWM_in			(PWM_2),
    .PWM_out		(M2_REF)
);

quadrature left_wheel(
	.clk 					(PWM_CLOCK),
	.quadA				(ENC_A1),
	.quadB				(ENC_B1),
	.count				(LEFT_ENC)
);

quadrature right_wheel(
	.clk 					(PWM_CLOCK),
	.quadA				(ENC_A2),
	.quadB				(ENC_B2),
	.count				(RIGHT_ENC)
);

Edge_Detecting_Line_Follower edlf (

	.camera_data		(CAM_D),
	.pixel_clock		(CAM_PCLK),
	.vsync				(CAM_VSYNC),
	.href					(CAM_HSYNC),

	.line_position     (LINE_DETECT)

);

// Because these are all started at the same time
// they will have syncronized clocks, but better
// to structure it differently at some point

PDM_to_PCM pdm_to_pcm_1 (

	.pdm_clk				(PDM_CLK),
	.pdm					(PDM[0]),

	.pcm_clk				(PCM_CLK),
	.pcm					(PCM_1)

);

PDM_to_PCM pdm_to_pcm_2 (

	.pdm_clk				(PDM_CLK),
	.pdm					(PDM[1]),

	.pcm_clk				(),
	.pcm					(PCM_2)

);

PDM_to_PCM pdm_to_pcm_3 (

	.pdm_clk				(PDM_CLK),
	.pdm					(PDM[2]),

	.pcm_clk				(),
	.pcm					(PCM_3)

);

TDoA tdoa (

	.reset				(PEAK_RESET),

	.pcm_clk				(PCM_CLK),
	
	.pcm_data_1			(PCM_1),
	.pcm_data_2			(PCM_2),
	.pcm_data_3			(PCM_3),

	.trigger_time_1	(PEAK_1),
	.trigger_time_2	(PEAK_2),
	.trigger_time_3	(PEAK_3)
	
);


CameraStreamer streamer (

	.clk					(SYS_CLK),
	.n_reset				(LOCKED),
	.ready				(READY),

	.camera_data		(CAM_D),
	.pixel_clock		(CAM_PCLK),
	.vsync				(CAM_VSYNC),
	.href					(CAM_HSYNC),

	.data					(RGB_DATA),
	.startofpacket		(SOP),
	.endofpacket		(EOP),
	.empty				(),
	.valid				(VALID)
	
);

EDL_Final cpu (

		.clk_clk                            (SYS_CLK),                    //             clk.clk
		.reset_reset_n								(LOCKED), 			      	   //           reset.reset_n

		.button_external_connection_export  (KEY),

		.led_external_connection_export		(LEDR),

		.pwm_export									({PWM_1, PWM_2}),             //             pwm.export

		.encoder_left_export						(LEFT_ENC),                   //    encoder_left.export
		.encoder_right_export					(RIGHT_ENC),                  //   encoder_right.export

		.motor_direction_export					({M1_C, M1_CW, M2_C, M2_CW}), // motor_direction.export
		.on_button_export							(ON_BUTTON),                  //       on_button.export

		.uptime_export								(UPTIME),                     //          uptime.export

		.line_detect_export						(LINE_DETECT),                //     line_detect.export

      .ble_uart_rxd								(BLUETOOTH_FPGA_RX),          //         ble_uart.rxd
		.ble_uart_txd								(BLUETOOTH_FPGA_TX),          //                 .txd

		.lidar_uart_rxd                     (LIDAR_FPGA_RX),              //       lidar_uart.rxd
		.lidar_uart_txd                     (LIDAR_FPGA_TX),              //                 .txd
		.lidar_motor_en_export              (LIDAR_MOTOR_EN),             //   lidar_motor_en.export
		
		.sdram_wire_addr							(DRAM_A),				      	//      sdram_wire.addr
		.sdram_wire_ba								(DRAM_BA),				         //                .ba
		.sdram_wire_cas_n							(DRAM_CAS_N),				      //                .cas_n
		.sdram_wire_cke 							(DRAM_CKE),					      //                .cke
		.sdram_wire_cs_n							(DRAM_CS_N),				      //                .cs_n
		.sdram_wire_dq								(DRAM_D), 					      //                .dq
		.sdram_wire_dqm							({DRAM_UDQM, DRAM_LDQM}),     //                .dqm
		.sdram_wire_ras_n							(DRAM_RAS_N),				      //                .ras_n
		.sdram_wire_we_n							(DRAM_WE_N),   			      //                .we_n

		.video_dma_sink_data						(RGB_DATA),                   //  video_dma_sink.data
		.video_dma_sink_startofpacket			(SOP),      				      //                .startofpacket
		.video_dma_sink_endofpacket			(EOP),        				      //                .endofpacket
		.video_dma_sink_valid					(VALID),              	      //                .valid
		.video_dma_sink_ready               (READY), 				         //                .ready

		.peak_1_export								(PEAK_1),                     //          peak_1.export
		.peak_2_export								(PEAK_2),                     //          peak_2.export
		.peak_3_export								(PEAK_3),                     //          peak_3.export
		.peak_reset_export						(PEAK_RESET)                  //      peak_reset.export

	);

endmodule
