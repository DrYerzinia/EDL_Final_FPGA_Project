
module EDL_Final (
	button_external_connection_export,
	clk_clk,
	led_external_connection_export,
	pixel_clk_clk,
	pixel_reset_reset,
	reset_reset,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	reset_bridge_reset,
	sysclk_clk,
	video_dma_sink_data,
	video_dma_sink_startofpacket,
	video_dma_sink_endofpacket,
	video_dma_sink_valid,
	video_dma_sink_ready,
	sdram_clk_clk);	

	input	[1:0]	button_external_connection_export;
	input		clk_clk;
	output	[9:0]	led_external_connection_export;
	input		pixel_clk_clk;
	input		pixel_reset_reset;
	input		reset_reset;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output		reset_bridge_reset;
	output		sysclk_clk;
	input	[23:0]	video_dma_sink_data;
	input		video_dma_sink_startofpacket;
	input		video_dma_sink_endofpacket;
	input		video_dma_sink_valid;
	output		video_dma_sink_ready;
	output		sdram_clk_clk;
endmodule
