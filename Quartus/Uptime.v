module Uptime(

    input clk,
    output reg [31:0] uptime

);

	reg [6:0] cnt;

	initial
	begin
		uptime <= 0;
		cnt <= 0;
	end

	always @(posedge clk)
	begin

		if(cnt >= 125)
		begin

			uptime <= uptime + 1;

			cnt <= 0;

		end
		else
		begin
		
			cnt <= cnt + 1;

		end
	end


endmodule