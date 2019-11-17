	EDL_Final u0 (
		.clk_clk                           (<connected-to-clk_clk>),                           //                        clk.clk
		.reset_reset                       (<connected-to-reset_reset>),                       //                      reset.reset
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
		.button_external_connection_export (<connected-to-button_external_connection_export>), // button_external_connection.export
		.led_external_connection_export    (<connected-to-led_external_connection_export>)     //    led_external_connection.export
	);

