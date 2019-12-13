module PCM_peak_detector (

	// Inputs

	pcm_clk,
	pcm_data,

	reset,
	
	sample_counter,

	// Outputs

	triggered,

	triggered_time

);

	input 					pcm_clk;
	input signed [15:0]	pcm_data;

	input						reset;

	input [31:0]			sample_counter;

	
	output reg				triggered;
	output reg [31:0]		triggered_time;

	localparam  THRESHOLD = 150;

	reg signed [15:0]    max_amplitude;

	always @(posedge pcm_clk)
	begin

		if (reset)
		begin

			triggered <= 1'b0;

		end

		else if( ( pcm_data > THRESHOLD ) && !triggered)
		begin

			// Otherwise if we exceed the trigger threshold we lock in the time and mark as triggered

			max_amplitude  <= pcm_data;			
			triggered_time <= sample_counter;
			triggered      <= 1'b1;

		end
		else if(triggered && ( pcm_data > max_amplitude ) )
		begin

			max_amplitude  <= pcm_data;
			triggered_time <= sample_counter;

		end

	end

endmodule