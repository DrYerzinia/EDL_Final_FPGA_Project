/******************************************************************************
 * Circular data buffer
 * IN  Audio data
 * IN  Stop trigger
 * PARAM length (window_size + max_deviation * 2)
 *   clock in data until stop trigger
 *****************************************************************************/
 
module circular_data_buffer(clk_1, clk_2, pcm, stop, offset, data);

	parameter LENGTH = 240;

	input						clk_1, clk_2;
	input signed [15:0]	pcm;
	input						stop;

	input  [7:0]			offset;
	output [15:0]			data;
	
	reg [7:0] 				write_position;

	wire [7:0]				read_address;
	wire						wren;
	
	assign wren = !stop;

	assign read_address = ( write_position + offset + 1 ) % LENGTH;
	
	ram buffer_memory (
		.wr_clk			(clk_1),
		.rd_clk			(clk_2),
		.d					(pcm),
		.rdaddress		(read_address),
		.wraddress		(write_position),
		.wren				(wren),
		.q					(data)
	);

	initial
	begin
		write_position <= 0;
	end
	
	always @(posedge clk_1)
	begin

		if(!stop)
		begin

			if(write_position == LENGTH)
			begin
				write_position <= 0;
			end
			else
			begin
				write_position <= write_position + 1;
			end

		end

	end

endmodule

module ram(wr_clk, rd_clk, d, rdaddress, wraddress, wren, q);

	output reg [15:0] q;
	input [15:0] d;
	input [7:0] wraddress, rdaddress;
	input wren, wr_clk, rd_clk;

	reg [15:0] mem [0:255];
	integer i;

	always @ (posedge wr_clk) begin

		if (wren)
		begin
			mem[wraddress] <= d;
		end

	end

	always @ (posedge rd_clk) begin

		q <= mem[rdaddress];

	end
	
endmodule
 
module circular_data_buffer_testbench();

	reg			clk;
	reg [15:0]	pcm;
	reg			stop;
	reg [7:0]   offset;

	wire [15:0] data;
	
	circular_data_buffer DUT(clk, clk, pcm, stop, offset, data);
 
	initial
	begin
		clk = 0; pcm = 0; stop = 0; offset = 0;
	end
 
	always @(posedge clk)
	begin

		pcm <= pcm + 1;

		if(pcm == 300)
		begin
			stop <= 1;
		end
		else if(pcm > 300)
		begin

			offset <= offset + 1;

		end
		
		if(pcm == 400)
		begin
			$finish;
		end
	
	end

	always
	begin
		#5   clk = ~clk;
	end

endmodule