
module CameraRGBScan(
		pclk,
		href,
		vsync,
		cam_data,
		data_valid,
		image_start,
		count,
		r1,
		r2,
		g1,
		g2,
		b1,
		b2
	);

	input 					pclk;
	input 					href;
	input 					vsync;
	input			[7:0] 	cam_data;

	output reg	[7:0]		r1, r2,
								g1, g2,
								b1, b2;

	output reg           data_valid;

	output reg	[7:0]		count;
	
	output reg				image_start;
	
	reg 						last_href;
	reg 			[10:0] 	line_counter;

	reg			[7:0]		y1, y2,
								u, v;

//	reg		 	[7:0]		rgb332_1,
//								rgb332_2;

	reg signed 	[15:0]	r1_s, r2_s,
								g1_s, g2_s,
								b1_s, b2_s;
								
	reg 			[2:0] 	state;

	localparam Y1 = 0, U = 1, Y2 = 2, V = 3, SKIP = 4;

	initial
	begin

		last_href    = 1'b0;
		line_counter = 11'b00000000000;

		state = Y1;
		
		image_start = 1'b0;
		

	end

	//assign wren = 1'b0; // DONT WRITE, TODO change later
	//assign wrclock = pclk;

	always @(posedge pclk)
	begin

		if(vsync)
		begin
			// Start of image
			image_start <= 1'b1;
			count <= 0;
		end
		else if(last_href != href & href == 0)
		begin

			// Start of line
			line_counter <= 0;
			state <= Y1;

		end
		else if(href == 1)
		begin

			// in line
			line_counter <= line_counter + 1;

			// y1 u y2 v

			case (state)
				Y1: begin
					y1 <= cam_data;
					state <= U;
					data_valid <= 1'b1;
				end
				U: begin
					u  <= cam_data;
					state <= Y2;
					data_valid <= 1'b0;
				end
				Y2: begin
					y2 <= cam_data;
					state <= V;
					data_valid <= 1'b0;
				end
				V: begin

					v  <= cam_data;

					r1_s <= (y1 - 16) + (v - 128) + ((v - 128) >> 2);
					g1_s <= (y1 - 16) - (v - 128) - ((u - 128) >> 2);
					b1_s <= (y1 - 16) + ((u - 128) << 2);

					r2_s <= (y2 - 16) + (v - 128) + ((v - 128) >> 2);
					g2_s <= (y2 - 16) - (v - 128) - ((u - 128) >> 2);
					b2_s <= (y2 - 16) + ((u - 128) << 2);

					if(r1_s > 0)
					begin
						r1 <= r1_s[7:0];
					end
					else
					begin
						r1 <= 0;
					end

					if(r1_s > 0)
					begin
						r2 <= r1_s[7:0];
					end
					else
					begin
						r2 <= 0;
					end

					if(g1_s > 0)
					begin
						g1 <= g1_s[7:0];
					end
					else
					begin
						g1 <= 0;
					end

					if(g1_s > 0)
					begin
						g2 <= g1_s[7:0];
					end
					else
					begin
						g2 <= 0;
					end

					if(b1_s > 0)
					begin
						b1 <= b1_s[7:0];
					end
					else
					begin
						b1 <= 0;
					end

					if(b1_s > 0)
					begin
						b2 <= b1_s[7:0];
					end
					else
					begin
						b2 <= 0;
					end

					//rgb332_1 <= {r1[7:5], g1[7:5], b1[7:6]};
					//rgb332_2 <= {r2[7:5], g2[7:5], b2[7:6]};

					//data <= rgb332_1;

					count <= count + 1;
					
					data_valid <= 1'b1;
					
					image_start <= 1'b0;

					state <= Y1;

					end
			endcase 

		end

		last_href <= href;

	end

endmodule