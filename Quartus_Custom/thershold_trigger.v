/*****************************************************************************
 * Threshold Trigger
 * IN  PCM
 * IN  RESET
 * OUT Trigger
 * PARAM Threshold
 *****************************************************************************/

module threshold_trigger(reset, pcm, pcm_clk, triggered);

	input               reset;

	input signed [15:0] pcm;
	input					  pcm_clk;

	output reg			  triggered;

	parameter THRESHOLD = 600;

	always @(posedge pcm_clk)
	begin

		if (reset)
		begin

			triggered <= 1'b0;

		end

		else if( pcm > THRESHOLD )
		begin

			triggered      <= 1'b1;

		end

	end

endmodule

module threshold_trigger_testbench();


	reg reset, pcm_clk;

	reg signed [15:0] pcm;

	wire triggered;

	parameter stim_delay = 10;

	threshold_trigger DUT(reset, pcm, pcm_clk, triggered);

	initial
	begin

		// Start with module in reset
		reset = 1; pcm = 0; pcm_clk = 0;

		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) reset = 0;
		#(stim_delay) pcm = 300;
		#(stim_delay) pcm = 400;
		#(stim_delay) pcm = 500;
		#(stim_delay) pcm = 600;
		#(stim_delay) pcm = 700;
		#(stim_delay) pcm = 600;
		#(stim_delay) pcm = 500;
		#(stim_delay) pcm = 400;
		#(stim_delay) reset = 1;
		#(stim_delay) ;
		#(stim_delay) ;
		
	end

	// Setup clock toggles
	always 
	begin
		#5  pcm_clk =  !pcm_clk; 
	end


endmodule