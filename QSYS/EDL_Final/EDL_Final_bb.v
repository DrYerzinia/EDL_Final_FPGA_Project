
module EDL_Final (
	button_external_connection_export,
	clk_clk,
	led_external_connection_export,
	pixel_clk_clk,
	pixel_reset_reset,
	pwm_export,
	reset_reset,
	reset_bridge_reset,
	sdram_clk_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	sysclk_clk,
	video_dma_sink_data,
	video_dma_sink_startofpacket,
	video_dma_sink_endofpacket,
	video_dma_sink_valid,
	video_dma_sink_ready);	

	input	[1:0]	button_external_connection_export;
	input		clk_clk;
	output	[9:0]	led_external_connection_export;
	input		pixel_clk_clk;
	input		pixel_reset_reset;
	output	[15:0]	pwm_export;
	input		reset_reset;
	output		reset_bridge_reset;
	output		sdram_clk_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output		sysclk_clk;
	input	[23:0]	video_dma_sink_data;
	input		video_dma_sink_startofpacket;
	input		video_dma_sink_endofpacket;
	input		video_dma_sink_valid;
	output		video_dma_sink_ready;
endmodule
