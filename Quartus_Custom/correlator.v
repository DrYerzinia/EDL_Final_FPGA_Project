/******************************************************************************
 * Correlator
 *****************************************************************************/
 
module correlator(clk, reset, trigger, done, buffer_data_1, buffer_data_2, buffer_data_3, buffer_offset, buffer_offset_other, offset_1, offset_2);

	parameter OTHERS = 2;

	parameter WINDOW_WIDTH = 180;
	parameter MAX_DEVIATION = 30;
	
	input						clk;
	input						reset;
	input						trigger;

	input signed [15:0]	buffer_data_1, buffer_data_2, buffer_data_3;
	
	output reg				done;
	
	output [7:0]			buffer_offset;
	output [7:0]			buffer_offset_other;

	output reg [7:0]		offset_1, offset_2;

	integer	 				idx;

	reg						internal_done;
	
	reg signed [31:0]		biggest_sum				[OTHERS-1:0];
	reg [7:0]				biggest_sum_offset	[OTHERS-1:0];
	
	reg signed [31:0]		correlation_sum		[OTHERS-1:0];

	reg [7:0]				deviation_counter;
	reg [7:0]				window_counter;

	assign buffer_offset = window_counter + MAX_DEVIATION;
	assign buffer_offset_other = window_counter + deviation_counter;
	
	always @(posedge clk)
	begin

		if(reset)
		begin

			deviation_counter <= 0;
			window_counter <= 0;

			for(idx = 0; idx < OTHERS; idx = idx + 1)
			begin
				correlation_sum[idx] <= 0;
				biggest_sum[idx] <= 0;
			end

			internal_done <= 0;

			done <= 0;

			offset_1 <= 0;
			offset_2 <= 0;

		end
		else if(internal_done)
		begin

			done <= 1;
		
			// Clock out biggest indexs
			offset_1 <= biggest_sum_offset[0];
			offset_2 <= biggest_sum_offset[1];
			
		end
		else if(trigger)
		begin

			// Multiply and SUM
			correlation_sum[0] <= correlation_sum[0] + ( buffer_data_1 * buffer_data_2 );
			correlation_sum[1] <= correlation_sum[1] + ( buffer_data_1 * buffer_data_3 );

			if( window_counter == WINDOW_WIDTH )
			begin

				// Check if current offset is biggest offset
				for(idx = 0; idx < OTHERS; idx = idx + 1)
				begin
					if(biggest_sum[idx] < correlation_sum[idx])
					begin
						biggest_sum[idx] <= correlation_sum[idx];
						biggest_sum_offset[idx] <= deviation_counter;
					end
					correlation_sum[idx] <= 0;
				end

				if(deviation_counter == MAX_DEVIATION * 2)
				begin

					// DONE
					internal_done <= 1;
		
				end

				window_counter <= 0;
				deviation_counter <= deviation_counter + 1;
				
			end

			window_counter <= window_counter + 1;
			
		end
	end

endmodule
