module PDM_to_PCM (

	// Inputs
	pdm_clk,
	pdm,

	// Outputs
	pcm_clk,
	pcm

);


	input											pdm_clk;
	input											pdm;

	output reg									pcm_clk;
	output reg signed [15:0]				pcm;

	reg					[6:0]					decimation_counter;

	reg signed			[15:0]				average;
	reg signed			[15:0]				sample_sum;

	reg 					[FILTER_LEN-1:0]	filter_bank;

	localparam FILTER_LEN  = 256;
	localparam FILTER_HALF = -128;
	localparam DECIMATION  = 64;

	initial
	begin

		filter_bank <= 0;
		average <= FILTER_HALF;

	end
	
	always @(posedge pdm_clk)
	begin

		// Shift in new sample
		filter_bank <= (filter_bank << 1 ) | pdm;

		// Adjust counter
		//average <= average + pdm - filter_bank[FILTER_LEN-1];
		
		if(pdm)
		begin
			if(filter_bank[FILTER_LEN-1])
			begin
				average <= average;
			end
			else
			begin
				average <= average + 1;

			end
		end
		else
		begin
			if(filter_bank[FILTER_LEN-1])
			begin
				average <= average - 1;
			end
			else
			begin
				average <= average;

			end
		end

		if(decimation_counter == (DECIMATION - 1))
		begin

			pcm_clk <= 0;
		
			pcm <= (sample_sum + average);// >> 6;

			decimation_counter <= 0;
			sample_sum <= 0;

		end
		else
		begin

			if(decimation_counter == 32)
			begin
				pcm_clk <= 1;
			end

			decimation_counter <= decimation_counter + 1;
			sample_sum <= sample_sum + average;
			
		end
	
	end

endmodule