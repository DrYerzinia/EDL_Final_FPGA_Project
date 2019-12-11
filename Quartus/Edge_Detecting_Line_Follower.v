module Edge_Detecting_Line_Follower (

	// Inputs
	camera_data,
	pixel_clock,
	href,
	vsync,

	// Outputs
	line_position,

	max
);

/*****************************************************************************
 *                             Port Declarations                             *
 *****************************************************************************/

// Inputs from camera
input [7:0]		camera_data;
input				pixel_clock;
input				href;
input				vsync;

// Outputs
output reg [3:0]    line_position;

reg [3:0]		biggest_bin_index;

// States for YUYV data from camera
localparam Y1 = 2'b00, U = 2'b01, Y2 = 2'b10, V = 2'b11;

// Which data is the camera output
reg 			[2:0]  	state;

reg						line_start;

// Y values
reg signed	[8:0]		y[6:0];

reg  			[15:0]   b[15:0];
output reg	[15:0]   max;

// track pixel position in line
reg			[9:0]    line_counter;

reg			[4:0] 	vsync_state;

initial
begin

	state = Y1;
	line_counter = 10'b0;

end

//integer index;

// Handle pixel clock domain logic
always @(posedge pixel_clock)
begin

	// VSYNC indicates start of image setup start_of_packet
	if(vsync)
	begin

		case (vsync_state)

			0: begin
				max <= b[0];
				biggest_bin_index <= 0;
				vsync_state <= 1;
			end
			1: begin
				max <= max > b[1] ? max : b[1];
				biggest_bin_index <= max > b[1] ? biggest_bin_index : 1;
				vsync_state <= 2;
			end
			2: begin
				max <= max > b[2] ? max : b[2];
				biggest_bin_index <= max > b[2] ? biggest_bin_index : 2;
				vsync_state <= 3;
			end
			3: begin
				max <= max > b[3] ? max : b[3];
				biggest_bin_index <= max > b[3] ? biggest_bin_index : 3;
				vsync_state <= 4;
			end
			4: begin
				max <= max > b[4] ? max : b[4];
				biggest_bin_index <= max > b[4] ? biggest_bin_index : 4;
				vsync_state <= 5;
			end
			5: begin
				max <= max > b[5] ? max : b[5];
				biggest_bin_index <= max > b[5] ? biggest_bin_index : 5;
				vsync_state <= 6;
			end
			6: begin
				max <= max > b[6] ? max : b[6];
				biggest_bin_index <= max > b[6] ? biggest_bin_index : 6;
				vsync_state <= 7;
			end
			7: begin
				max <= max > b[7] ? max : b[7];
				biggest_bin_index <= max > b[7] ? biggest_bin_index : 7;
				vsync_state <= 8;
			end
			8: begin
				max <= max > b[8] ? max : b[8];
				biggest_bin_index <= max > b[8] ? biggest_bin_index : 8;
				vsync_state <= 9;
			end
			9: begin
				max <= max > b[9] ? max : b[9];
				biggest_bin_index <= max > b[9] ? biggest_bin_index : 9;
				vsync_state <= 10;
			end
			10: begin
				max <= max > b[10] ? max : b[10];
				biggest_bin_index <= max > b[10] ? biggest_bin_index : 10;
				vsync_state <= 11;
			end
			11: begin
				max <= max > b[11] ? max : b[11];
				biggest_bin_index <= max > b[11] ? biggest_bin_index : 11;
				vsync_state <= 12;
			end
			12: begin
				max <= max > b[12] ? max : b[12];
				biggest_bin_index <= max > b[12] ? biggest_bin_index : 12;
				vsync_state <= 13;
			end
			13: begin
				max <= max > b[13] ? max : b[13];
				biggest_bin_index <= max > b[13] ? biggest_bin_index : 13;
				vsync_state <= 14;
			end
			14: begin
				max <= max > b[14] ? max : b[14];
				biggest_bin_index <= max > b[14] ? biggest_bin_index : 14;
				vsync_state <= 15;
			end
			15: begin
				max <= max > b[15] ? max : b[15];
				biggest_bin_index <= max > b[15] ? biggest_bin_index : 15;
				vsync_state <= 16;
			end
			16: begin

				line_position <= biggest_bin_index;

				/*for(index = 0; index < 16; index = index + 1)
				begin
					b[index]  <= 0;
				end*/
				b[0] <= 0;
				b[1] <= 0;
				b[2] <= 0;
				b[3] <= 0;
				b[4] <= 0;
				b[5] <= 0;
				b[6] <= 0;
				b[7] <= 0;
				b[8] <= 0;
				b[9] <= 0;
				b[10] <= 0;
				b[11] <= 0;
				b[12] <= 0;
				b[13] <= 0;
				b[14] <= 0;
				b[15] <= 0;

				vsync_state <= 17;

			end
			17:begin
				// DO nothing
			end
		endcase
	end

	// We are in the inter-line blanking period
	else if(href == 0)
	begin

		// Start of line
		line_counter <= 0;
		state <= Y1;

		vsync_state <= 0;
		
	end

	// We are in the line
	else if(href == 1)
	begin

		case (state)

			// First element is Y
			Y1: begin

				state <= U;
				
			end

			U: begin
				state <= Y2;
			end
			
			Y2: begin
				state <= V;
			end

			V: begin
			
				state <= Y1;

				// Cascade Y values
				/*
				for(index = 0; index < 6; index = index + 1)
				begin
					y[index] <= y[index + 1];
				end*/
				y[0] <= y[1];
				y[1] <= y[2];
				y[2] <= y[3];
				y[3] <= y[4];
				y[4] <= y[5];
				y[5] <= y[6];
				y[6] <= camera_data;

				line_counter <= line_counter + 10'b1;
	
				// When we have 6 pixels start checking values
				if(line_counter > 6)
				begin

					if((y[0] - y[6]) > 10 || (y[0] - y[6]) < -10) // Handle abs val
					begin

						// If the delta is greater than 10 add to the bin
						if(line_counter < 20)
						begin
							b[0] <= b[0] + 16'b1;
						end
						else if(line_counter < 40)
						begin
							b[1] <= b[1] + 16'b1;
						end
						else if(line_counter < 60)
						begin
							b[2] <= b[2] + 16'b1;
						end
						else if(line_counter < 80)
						begin
							b[3] <= b[3] + 16'b1;
						end
						else if(line_counter < 100)
						begin
							b[4] <= b[4] + 16'b1;
						end
						else if(line_counter < 120)
						begin
							b[5] <= b[5] + 16'b1;
						end
						else if(line_counter < 140)
						begin
							b[6] <= b[6] + 16'b1;
						end
						else if(line_counter < 160)
						begin
							b[7] <= b[7] + 16'b1;
						end
						else if(line_counter < 180)
						begin
							b[8] <= b[8] + 16'b1;
						end
						else if(line_counter < 200)
						begin
							b[9] <= b[9] + 16'b1;
						end
						else if(line_counter < 220)
						begin
							b[10] <= b[10] + 16'b1;
						end
						else if(line_counter < 240)
						begin
							b[11] <= b[11] + 16'b1;
						end
						else if(line_counter < 260)
						begin
							b[12] <= b[12] + 16'b1;
						end
						else if(line_counter < 280)
						begin
							b[13] <= b[13] + 16'b1;
						end
						else if(line_counter < 300)
						begin
							b[14] <= b[14] + 16'b1;
						end
						else
						begin
							b[15] <= b[15] + 16'b1;
						end

					end

				end
				
	
			end

		endcase 

	end

end

endmodule