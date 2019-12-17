/******************************************************************************
 * Trigger Delay
 * IN  trigger
 * IN  clock
 * OUT delayed_trigger
 * PARAM TRIGGER_DELAY
 *****************************************************************************/
 
 
module trigger_delay(clk, reset, trigger_in, trigger_out);

	input               clk;

	input 				  reset;

	input					  trigger_in;
	output reg			  trigger_out;

	parameter TRIGGER_DELAY = 150;

	reg			triggered;
	reg [7:0]	counter;

	always @(posedge clk)
	begin

		if(reset)
		begin

			counter <= 0;
			triggered <= 0;
			trigger_out <= 0;
		
		end
		
		else if(triggered)
		begin

			// Subtract 1 to account for register delay
			if(counter == (TRIGGER_DELAY - 1))
			begin

				trigger_out <= 1;

			end
			else
			begin

				counter <= counter + 1;

			end

		end
		
		else if(trigger_in)
		begin

			triggered <= 1;

		end

	end

endmodule

module trigger_delay_testbench();


	reg clk, reset, trigger_in;
	wire trigger_out;

	parameter stim_delay = 10;

	
	trigger_delay #(.TRIGGER_DELAY(3)) DUT(clk, reset, trigger_in, trigger_out);

	initial
	begin

		// Start with module in reset
		reset = 1; trigger_in = 0; clk = 0;

		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) reset = 0;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) trigger_in = 1;
		#(stim_delay) ;
		#(stim_delay) trigger_in = 0;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) ;
		#(stim_delay) reset = 1;
		#(stim_delay) reset = 0;
		#(stim_delay) ;
		#(stim_delay) ;
		
	end

	// Setup clock toggles
	always 
	begin
		#5  clk =  !clk; 
	end


endmodule