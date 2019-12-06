module PDM_to_PCM (

	// Inputs
	pdm_clk,
	pdm,

	// Outputs
	pcm_clk,
	pcm

);


	input pdm_clk;
	input pdm;

	output reg 			pcm_clk;
	output reg [15:0] pcm;

	localparam FILTER_LEN = 64;
	localparam DECIMATION = 64;

	reg [6:0] 					decimation_counter;

	reg [15:0]					average;
	reg [31:0] 		 			sample_sum;

	reg [FILTER_LEN-1:0]		filter_bank;

	
	initial
	begin

		filter_bank <= 0;
		average <= 0;

	end
	
	always @(posedge pdm_clk)
	begin

		// Shift in new sample
		filter_bank <= (filter_bank << 1 ) | pdm;

		// Adjust counter
		average <= average + pdm - filter_bank[FILTER_LEN-1];

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