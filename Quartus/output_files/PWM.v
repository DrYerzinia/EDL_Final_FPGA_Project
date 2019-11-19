module PWM(

    input clk,
    input [7:0] PWM_in,
    output PWM_out

);

	reg [7:0] cnt;

	always @(posedge clk)
	begin
		cnt <= cnt + 1'b1;  // free-running counter
	end

	assign PWM_out = (PWM_in > cnt);  // comparator

endmodule