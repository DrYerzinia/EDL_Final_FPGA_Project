
module EDL_Final (
	ble_uart_rxd,
	ble_uart_txd,
	button_external_connection_export,
	clk_clk,
	encoder_left_export,
	encoder_right_export,
	led_external_connection_export,
	lidar_motor_en_export,
	lidar_uart_rxd,
	lidar_uart_txd,
	line_detect_export,
	motor_direction_export,
	on_button_export,
	peak_1_export,
	peak_2_export,
	peak_3_export,
	peak_reset_export,
	pwm_export,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	uptime_export,
	video_dma_sink_data,
	video_dma_sink_startofpacket,
	video_dma_sink_endofpacket,
	video_dma_sink_valid,
	video_dma_sink_ready);	

	input		ble_uart_rxd;
	output		ble_uart_txd;
	input	[1:0]	button_external_connection_export;
	input		clk_clk;
	input	[31:0]	encoder_left_export;
	input	[31:0]	encoder_right_export;
	output	[9:0]	led_external_connection_export;
	output		lidar_motor_en_export;
	input		lidar_uart_rxd;
	output		lidar_uart_txd;
	input	[3:0]	line_detect_export;
	output	[3:0]	motor_direction_export;
	input		on_button_export;
	input	[31:0]	peak_1_export;
	input	[31:0]	peak_2_export;
	input	[31:0]	peak_3_export;
	output		peak_reset_export;
	output	[15:0]	pwm_export;
	input		reset_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input	[31:0]	uptime_export;
	input	[23:0]	video_dma_sink_data;
	input		video_dma_sink_startofpacket;
	input		video_dma_sink_endofpacket;
	input		video_dma_sink_valid;
	output		video_dma_sink_ready;
endmodule
