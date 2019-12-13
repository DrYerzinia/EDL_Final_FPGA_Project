module TDoA (

	// Inputs

	reset,
	
	pcm_clk,

	pcm_data_1,
	pcm_data_2,
	pcm_data_3,

	// Outputs

	trigger_time_1,
	trigger_time_2,
	trigger_time_3,
	
);

	input						reset;

	input 					pcm_clk;

	input signed [15:0]	pcm_data_1, pcm_data_2, pcm_data_3;

	output reg [31:0] 	trigger_time_1, trigger_time_2, trigger_time_3;
	
	reg [31:0]				sample_counter;

	reg [7:0]				max_detect_counter;
	
	wire [31:0]				triggered_time_1, triggered_time_2, triggered_time_3;
	
	wire peak_1_triggered;
	wire peak_2_triggered;
	wire peak_3_triggered;

	wire all_triggered;
	wire any_triggered;

	assign all_triggered = peak_1_triggered & peak_2_triggered & peak_3_triggered;
	assign any_triggered = peak_1_triggered | peak_2_triggered | peak_3_triggered;
	
	// Create peak detectors for each microphone

	PCM_peak_detector peak_1 (
		.pcm_clk				(pcm_clk),
		.pcm_data			(pcm_data_1),
		.reset				(reset),
		.sample_counter	(sample_counter),
		.triggered			(peak_1_triggered),
		.triggered_time   (triggered_time_1)
	);

	PCM_peak_detector peak_2 (
		.pcm_clk				(pcm_clk),
		.pcm_data			(pcm_data_2),
		.reset				(reset),
		.sample_counter	(sample_counter),
		.triggered			(peak_2_triggered),
		.triggered_time   (triggered_time_2)
	);

	PCM_peak_detector peak_3 (
		.pcm_clk				(pcm_clk),
		.pcm_data			(pcm_data_3),
		.reset				(reset),
		.sample_counter	(sample_counter),
		.triggered			(peak_3_triggered),
		.triggered_time   (triggered_time_3)
	);

	always @(posedge pcm_clk)
	begin

		if(reset)
		begin

			sample_counter <= 0;
		
			trigger_time_1 <= 0;
			trigger_time_2 <= 0;
			trigger_time_3 <= 0;

			max_detect_counter <= 0;
			
		end
		else
		begin

					// Count samples for peak detector
			sample_counter <= sample_counter + 1;

			if(max_detect_counter == 200)
			begin

				trigger_time_1 <= triggered_time_1;
				trigger_time_2 <= triggered_time_2;
				trigger_time_3 <= triggered_time_3;

			end
			else if(all_triggered)
			begin

				// When everything is triggered we report back to CPU
				// We reset everythiing after the CPU has pulled the data

				max_detect_counter <= max_detect_counter + 1;
				
			end
			else
			begin

				trigger_time_1 <= 0;
				trigger_time_2 <= 0;
				trigger_time_3 <= 0;

			end

			// If any is triggered for to long we need to reset
		
		end

	end

endmodule