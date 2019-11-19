	EDL_Final u0 (
		.button_external_connection_export (<connected-to-button_external_connection_export>), // button_external_connection.export
		.clk_clk                           (<connected-to-clk_clk>),                           //                        clk.clk
		.led_external_connection_export    (<connected-to-led_external_connection_export>),    //    led_external_connection.export
		.pixel_clk_clk                     (<connected-to-pixel_clk_clk>),                     //                  pixel_clk.clk
		.pixel_reset_reset                 (<connected-to-pixel_reset_reset>),                 //                pixel_reset.reset
		.reset_reset                       (<connected-to-reset_reset>),                       //                      reset.reset
		.reset_bridge_reset                (<connected-to-reset_bridge_reset>),                //               reset_bridge.reset
		.sdram_clk_clk                     (<connected-to-sdram_clk_clk>),                     //                  sdram_clk.clk
		.sdram_wire_addr                   (<connected-to-sdram_wire_addr>),                   //                 sdram_wire.addr
		.sdram_wire_ba                     (<connected-to-sdram_wire_ba>),                     //                           .ba
		.sdram_wire_cas_n                  (<connected-to-sdram_wire_cas_n>),                  //                           .cas_n
		.sdram_wire_cke                    (<connected-to-sdram_wire_cke>),                    //                           .cke
		.sdram_wire_cs_n                   (<connected-to-sdram_wire_cs_n>),                   //                           .cs_n
		.sdram_wire_dq                     (<connected-to-sdram_wire_dq>),                     //                           .dq
		.sdram_wire_dqm                    (<connected-to-sdram_wire_dqm>),                    //                           .dqm
		.sdram_wire_ras_n                  (<connected-to-sdram_wire_ras_n>),                  //                           .ras_n
		.sdram_wire_we_n                   (<connected-to-sdram_wire_we_n>),                   //                           .we_n
		.sysclk_clk                        (<connected-to-sysclk_clk>),                        //                     sysclk.clk
		.video_dma_sink_data               (<connected-to-video_dma_sink_data>),               //             video_dma_sink.data
		.video_dma_sink_startofpacket      (<connected-to-video_dma_sink_startofpacket>),      //                           .startofpacket
		.video_dma_sink_endofpacket        (<connected-to-video_dma_sink_endofpacket>),        //                           .endofpacket
		.video_dma_sink_valid              (<connected-to-video_dma_sink_valid>),              //                           .valid
		.video_dma_sink_ready              (<connected-to-video_dma_sink_ready>),              //                           .ready
		.pwm_export                        (<connected-to-pwm_export>)                         //                        pwm.export
	);

