module Uptime(

    input clk,
    output reg [31:0] uptime

);

	reg [9:0] cnt;

	initial
	begin
		uptime <= 0;
		cnt <= 0;
	end

	always @(posedge clk)
	begin

		if(cnt >= 1000)
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