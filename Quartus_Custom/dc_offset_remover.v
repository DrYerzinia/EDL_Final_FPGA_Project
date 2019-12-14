/******************************************************************************
 * DC Offset Remover
 * IN  PCM data clock
 * IN  PCM data
 * OUT PCM data with DC offset removed
 *****************************************************************************/
 
module dc_offset_remover(clk, pcm_in, pcm_out);

	input								clk;
	input signed [15:0]			pcm_in;
	output signed [15:0]	pcm_out;

	reg signed [15:0]				last_sample;
	reg signed [23:0]				last_filtered;

	wire signed [23:0]			n, n2;
	
	// pcm_out is last filtered value
	
	// Using binary shifts to multiply by 0.966
	assign n = pcm_out + pcm_in - last_sample;
	assign n2 = ( ( n <<< 8 ) - n ) >>> 8;
	assign pcm_out[15:0] = last_filtered[15:0];
	
	initial
	begin

		last_sample <= 0;
		last_filtered <= 0;

	end
	
	always @(posedge clk)
	begin

		last_sample <= pcm_in;

		// To divide correctly by 2 if we are negative we need to add one
		if(n2 >= 0)
		begin
			last_filtered <= n2;
		end
		else
		begin
			last_filtered <= n2 + 1;
		end

	end

endmodule
 
module dc_offset_remover_testbench();

	integer data_file;

	reg					clk;

	reg signed [15:0] test_data;
	reg signed [15:0] pcm_in;

	wire signed [15:0] pcm_out;

	parameter stim_time = 10;

	dc_offset_remover DUT(clk, pcm_in, pcm_out);

	initial
	begin
		data_file = $fopen("test_waveforms/test3.dat", "r");
		if (data_file == 0)
		begin
			$display("data_file handle was NULL");
			$finish;
		end
	end
	
	initial
	begin

		clk = 0;
		pcm_in = 0;

	end

	always @(posedge clk)
	begin

		$fscanf(data_file, "%d\n", test_data);
		if (!$feof(data_file))
		begin

			pcm_in <= test_data;

		end
		else
		begin

			$finish;

		end
	
	end

	always
	begin
		#5   clk = !clk;
	end

endmodule