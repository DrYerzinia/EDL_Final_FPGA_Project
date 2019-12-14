/******************************************************************************
 * TDOA correlator
 *****************************************************************************/
 
module tdoa_correlator(clk_1, clk_2, reset, pcm_1, pcm_2, pcm_3, done, offset_1, offset_2);

	input					reset;
	input					clk_1, clk_2;
	input	[15:0]		pcm_1, pcm_2, pcm_3;

	output				done;
	
	output [7:0]	 	offset_1, offset_2;
	
	wire [15:0]			pcm_1_no_dc, pcm_2_no_dc, pcm_3_no_dc,
							buffer_data_1, buffer_data_2, buffer_data_3;

	wire [7:0]			offset, offset_other;

	wire 					trigger, th_trigger, th_trigger_1, th_trigger_2, th_trigger_3;

	assign th_trigger = th_trigger_1 & th_trigger_2 & th_trigger_3;

	dc_offset_remover dcr1(
		.clk			(clk_1),
		.pcm_in		(pcm_1),
		.pcm_out		(pcm_1_no_dc)
	);

	dc_offset_remover dcr2(
		.clk			(clk_1),
		.pcm_in		(pcm_2),
		.pcm_out		(pcm_2_no_dc)
	);

	dc_offset_remover dcr3(
		.clk			(clk_1),
		.pcm_in		(pcm_3),
		.pcm_out		(pcm_3_no_dc)
	);
	
	threshold_trigger th1(
		.reset		(reset),
		.pcm			(pcm_1_no_dc),
		.pcm_clk		(clk_1),
		.triggered	(th_trigger_1)
	);

	threshold_trigger th2(
		.reset		(reset),
		.pcm			(pcm_2_no_dc),
		.pcm_clk		(clk_1),
		.triggered	(th_trigger_2)
	);

	threshold_trigger th3(
		.reset		(reset),
		.pcm			(pcm_3_no_dc),
		.pcm_clk		(clk_1),
		.triggered	(th_trigger_3)
	);
	
	trigger_delay td(
		.clk				(clk_1),
		.reset			(reset),
		.trigger_in		(th_trigger),
		.trigger_out	(trigger)
	);

	circular_data_buffer db1(
		.clk_1	(clk_1),
		.clk_2	(clk_2),
		.pcm		(pcm_1_no_dc),
		.stop		(trigger),
		.offset	(offset),
		.data		(buffer_data_1)
	);

	circular_data_buffer db2(
		.clk_1	(clk_1),
		.clk_2	(clk_2),
		.pcm		(pcm_2_no_dc),
		.stop		(trigger),
		.offset	(offset_other),
		.data		(buffer_data_2)
	);

	circular_data_buffer db3(
		.clk_1	(clk_1),
		.clk_2	(clk_2),
		.pcm		(pcm_3_no_dc),
		.stop		(trigger),
		.offset	(offset_other),
		.data		(buffer_data_3)
	);
	
	correlator core(
		.clk							(clk_2),
		.reset						(reset),
		.trigger						(trigger),
		.done							(done),
		.buffer_data_1				(buffer_data_1),
		.buffer_data_2				(buffer_data_2),
		.buffer_data_3				(buffer_data_3),
		.buffer_offset				(offset),
		.buffer_offset_other		(offset_other),
		.offset_1					(offset_1),
		.offset_2					(offset_2)
	);

endmodule

module toda_correlator_tb();

	reg					clk_1, clk_2;

	reg					reset;

	reg signed [15:0]	pcm_1, pcm_2, pcm_3;
	reg signed [15:0] test_data_1, test_data_2, test_data_3;
	
	reg [31:0]			counter;
	
	reg [7:0]			clk_counter;
	
	wire		 			done;
	wire [7:0]			offset_1, offset_2;
	
	integer data_file_1, data_file_2, data_file_3;
	
	tdoa_correlator DUT(
		.clk_1		(clk_1),
		.clk_2		(clk_2),
		.reset		(reset),
		.pcm_1		(pcm_1),
		.pcm_2		(pcm_2),
		.pcm_3		(pcm_3),
		.done			(done),
		.offset_1	(offset_1),
		.offset_2	(offset_2)
	);

	initial
	begin

		clk_1 = 0;
		clk_2 = 0;
		reset = 1;
		counter = 0;

		clk_counter = 0;
		
		pcm_1 = 0;
		pcm_2 = 0;
		pcm_3 = 0;
		
		data_file_1 = $fopen("test_waveforms/wrong_3_1.dat", "r");
		if (data_file_1 == 0)
		begin
			$display("data_file_1 handle was NULL");
			$finish;
		end

		data_file_2 = $fopen("test_waveforms/wrong_3_2.dat", "r");
		if (data_file_2 == 0)
		begin
			$display("data_file_2 handle was NULL");
			$finish;
		end

		data_file_3 = $fopen("test_waveforms/wrong_3_3.dat", "r");
		if (data_file_3 == 0)
		begin
			$display("data_file_3 handle was NULL");
			$finish;
		end
		
	end

	always @(posedge clk_2)
	begin
	
		if(clk_counter == 32)
		begin
			clk_counter <= 0;
			clk_1 <= !clk_1;
		end
		else
		begin
			clk_counter <= clk_counter + 1;
		end

	end
	
	always @(posedge clk_1)
	begin

		$fscanf(data_file_1, "%d\n", test_data_1);
		if (!$feof(data_file_1))
		begin
			pcm_1 <= test_data_1;
		end
		else
		begin
			//$finish;
		end

		$fscanf(data_file_2, "%d\n", test_data_2);
		if (!$feof(data_file_2))
		begin
			pcm_2 <= test_data_2;
		end
		else
		begin
			//$finish;
		end

		$fscanf(data_file_3, "%d\n", test_data_3);
		if (!$feof(data_file_3))
		begin
			pcm_3 <= test_data_3;
		end
		else
		begin
			//$finish;
		end

		if(counter == 3)
		begin
			reset <= 0;
		end
		
		counter <= counter + 1;
	
	end
	
	always
	begin
		#5   clk_2 = !clk_2;
	end
	
endmodule
