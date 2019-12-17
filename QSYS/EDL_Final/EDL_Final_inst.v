	EDL_Final u0 (
		.ble_uart_rxd                      (<connected-to-ble_uart_rxd>),                      //                   ble_uart.rxd
		.ble_uart_txd                      (<connected-to-ble_uart_txd>),                      //                           .txd
		.button_external_connection_export (<connected-to-button_external_connection_export>), // button_external_connection.export
		.clk_clk                           (<connected-to-clk_clk>),                           //                        clk.clk
		.encoder_left_export               (<connected-to-encoder_left_export>),               //               encoder_left.export
		.encoder_right_export              (<connected-to-encoder_right_export>),              //              encoder_right.export
		.led_external_connection_export    (<connected-to-led_external_connection_export>),    //    led_external_connection.export
		.lidar_motor_en_export             (<connected-to-lidar_motor_en_export>),             //             lidar_motor_en.export
		.lidar_uart_rxd                    (<connected-to-lidar_uart_rxd>),                    //                 lidar_uart.rxd
		.lidar_uart_txd                    (<connected-to-lidar_uart_txd>),                    //                           .txd
		.line_detect_export                (<connected-to-line_detect_export>),                //                line_detect.export
		.motor_direction_export            (<connected-to-motor_direction_export>),            //            motor_direction.export
		.on_button_export                  (<connected-to-on_button_export>),                  //                  on_button.export
		.peak_1_export                     (<connected-to-peak_1_export>),                     //                     peak_1.export
		.peak_2_export                     (<connected-to-peak_2_export>),                     //                     peak_2.export
		.peak_3_export                     (<connected-to-peak_3_export>),                     //                     peak_3.export
		.peak_reset_export                 (<connected-to-peak_reset_export>),                 //                 peak_reset.export
		.pwm_export                        (<connected-to-pwm_export>),                        //                        pwm.export
		.reset_reset_n                     (<connected-to-reset_reset_n>),                     //                      reset.reset_n
		.sdram_wire_addr                   (<connected-to-sdram_wire_addr>),                   //                 sdram_wire.addr
		.sdram_wire_ba                     (<connected-to-sdram_wire_ba>),                     //                           .ba
		.sdram_wire_cas_n                  (<connected-to-sdram_wire_cas_n>),                  //                           .cas_n
		.sdram_wire_cke                    (<connected-to-sdram_wire_cke>),                    //                           .cke
		.sdram_wire_cs_n                   (<connected-to-sdram_wire_cs_n>),                   //                           .cs_n
		.sdram_wire_dq                     (<connected-to-sdram_wire_dq>),                     //                           .dq
		.sdram_wire_dqm                    (<connected-to-sdram_wire_dqm>),                    //                           .dqm
		.sdram_wire_ras_n                  (<connected-to-sdram_wire_ras_n>),                  //                           .ras_n
		.sdram_wire_we_n                   (<connected-to-sdram_wire_we_n>),                   //                           .we_n
		.uptime_export                     (<connected-to-uptime_export>),                     //                     uptime.export
		.video_dma_sink_data               (<connected-to-video_dma_sink_data>),               //             video_dma_sink.data
		.video_dma_sink_startofpacket      (<connected-to-video_dma_sink_startofpacket>),      //                           .startofpacket
		.video_dma_sink_endofpacket        (<connected-to-video_dma_sink_endofpacket>),        //                           .endofpacket
		.video_dma_sink_valid              (<connected-to-video_dma_sink_valid>),              //                           .valid
		.video_dma_sink_ready              (<connected-to-video_dma_sink_ready>)               //                           .ready
	);

