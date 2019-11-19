module CameraStreamer (

	// Inputs
	clk,
	reset,
	ready,
	
	camera_data,
	pixel_clock,
	href,
	vsync,

	// Outputs
	data,
	startofpacket,
	endofpacket,
	empty,
	valid,
	
);

/*****************************************************************************
 *                           Parameter Declarations                          *
 *****************************************************************************/

localparam  DW							= 24;

localparam  WIDTH						= 640;
localparam  HEIGHT					= 480;


/*****************************************************************************
 *                             Port Declarations                             *
 *****************************************************************************/

// Inputs from streaming interface
input				clk;
input				reset;
input				ready;

// Inputs from camera
input [7:0]		camera_data;
input				pixel_clock;
input				href;
input				vsync;

// Outputs to streaming interface
output		[DW:0]	data;
output reg				startofpacket;
output reg				endofpacket;
output					empty;
output reg				valid;

// CLOCK CROSSING FIFO ////////////////////////////////////////////////////////////////

reg [31:0] FIFO_DATA_IN;
wire [31:0] FIFO_DATA_OUT;
reg FIFO_READ;
reg FIFO_WRITE;
wire FIFO_EMPTY;
wire FIFO_FULL;

/*
aFifo
  #(
		.DATA_WIDTH			(32),
      .ADDRESS_WIDTH		(4)
	)
	fifo
	(

		.Data_out			(FIFO_DATA_OUT),
		.Empty_out			(FIFO_EMPTY),
		.ReadEn_in			(FIFO_READ),
		.RClk					(clk),
 
		.Data_in				(FIFO_DATA_IN),
		.Full_out			(),
		.WriteEn_in			(FIFO_WRITE),
		.WClk					(pixel_clock),
	 
		.Clear_in			()

	);
*/

Pixel_FIFO (

	.rdclk		(clk),
	.rdreq		(FIFO_READ),
	.rdempty		(FIFO_EMPTY),
	.q				(FIFO_DATA_OUT),
	
	.wrclk		(pixel_clock),
	.wrreq		(FIFO_WRITE),
	.wrfull		(FIFO_FULL),
	.data			(FIFO_DATA_IN)

);


// STREAM SIDE ////////////////////////////////////////////////////////////////////////

always @(negedge clk)
begin

	if (reset)
	begin

		valid			  <= 1'b0;
		startofpacket <= 1'b0;
		endofpacket   <= 1'b0;

	end
	else if (ready && !FIFO_EMPTY && !FIFO_READ)
	begin

		// If streaming sink is ready
		// and if our FIFO is not empty
		// set read a color from the FIFO
		// set the data output to that color
		// set valid high
		FIFO_READ <= 1'b1;

	end
	else if (ready && FIFO_READ)
	begin

			FIFO_READ <= 1'b0;
	
			valid 	 <= 1'b1;

			// Is start
			if (FIFO_DATA_OUT[24])
			begin
				startofpacket  <= 1'b1;
			end
			// is end
			else if (FIFO_DATA_OUT[25])
			begin
				endofpacket 	<= 1'b1;
			end
			
	
	end
	else
	begin

		valid <= 1'b0;

		startofpacket  <= 1'b0;
		endofpacket 	<= 1'b0;

		
	end
end

/*****************************************************************************
 *                            Combinational Logic                            *
 *****************************************************************************/

assign data				= FIFO_DATA_OUT[23:0];	// Pixel data is mapped directy to FIFO
assign empty			= 1'b0;

// CAMERA SIDE //////////////////////////////////////////////////////////////////

// States for YUYV data from camera
localparam Y1 = 0, U = 1, Y2 = 2, V = 3;

// Keep track of if we have pixels to send or not
reg		   [1:0] HAVE_PIXELS;

// Which data is the camera output
reg 			[2:0] 	state;

// Got vsync waiting for image data
reg						image_start;

reg						line_start;

// Intermediate YUV values
reg			[7:0]		y1, y2,
							u, v;

// Signed registers to handle YUV to RGB conversion
reg signed 	[15:0]	r1_s, r2_s,
							g1_s, g2_s,
							b1_s, b2_s;

// Hold RGB pixel values until we send to FIFO
reg		 	[7:0]		r1, r2,
							g1, g2,
							b1, b2;

reg [19:0]				pixel_counter;
							
reg						first_pixel;

initial
begin

	state = Y1;
	image_start = 1'b0;

end

// Handle pixel clock domain logic

always @(posedge pixel_clock)
begin

	// VSYNC indicates start of image setup start_of_packet
	if(vsync)
	begin

		// Start of image
		image_start <= 1'b1;
		first_pixel <= 1'b1;

		state <= Y1;
		
		FIFO_WRITE  <= 1'b0;
		HAVE_PIXELS <= 2'b00;

		pixel_counter <= 20'b00000000000000000000;

	end

	// We are in the inter-line blanking period
	else if(href == 0)
	begin

		// Start of line
		line_start <= 1;
		state <= Y1;

		// If we have pixels left over to send to FIFO do it here
		if(HAVE_PIXELS > 0)
		begin

			FIFO_WRITE   <= 1'b1;
			if(HAVE_PIXELS > 1)
			begin
				FIFO_DATA_IN <= {8'b00000000, r1, g1, b1};
				HAVE_PIXELS <= 2'b01;
			end
			else
			begin

				HAVE_PIXELS <= 2'b00;
			
				if (pixel_counter == 307200)
				begin
					FIFO_DATA_IN <= {8'b00000010, r1, g1, b1};
				end
				else
				begin
					FIFO_DATA_IN <= {8'b00000000, r1, g1, b1};				
				end

			end
			
		end
		else
		begin
			FIFO_WRITE   <= 1'b0;
		end
		
	end

	// We are in the line
	else if(href == 1)
	begin

		// The format form the camera is YUYV so each set of pixels is
		// the combination of 4 bytes from the camera so in the line we
		// use a state machine to track which element we are at
		// Y1 U Y2 V
		
		case (state)

			// First element is Y
			Y1: begin

				y1 <= camera_data;
				state <= U;

				if (!line_start)
				begin
					if (first_pixel)
					begin
						first_pixel <= 1'b0;
						FIFO_DATA_IN <= {8'b00000001, r1, g1, b1};
					end
					else
					begin
						FIFO_DATA_IN <= {8'b00000000, r1, g1, b1};				
					end
					FIFO_WRITE   <= 1'b1;
				end
				else
				begin
					FIFO_WRITE   <= 1'b0;
				end

			end

			// Second element is U
			U: begin

				u <= camera_data;
				state <= Y2;

				if (!line_start)
				begin
					FIFO_DATA_IN <= {8'b00000000, r2, g2, b2};
					FIFO_WRITE   <= 1'b1;
				end
				else
				begin
					FIFO_WRITE   <= 1'b0;
				end

			end

			// Third element is another Y
			Y2: begin
			
				y2 <= camera_data;
				state <= V;

				FIFO_WRITE   <= 1'b0;

			end

			// Forth and final element is V
			V: begin

				v  <= camera_data;

				// We do a conversion from YUV to RGB color space

				r1_s <= (y1 - 16) + (v - 128) + ((v - 128) >> 2);
				g1_s <= (y1 - 16) - (v - 128) - ((u - 128) >> 2);
				b1_s <= (y1 - 16) + ((u - 128) << 2);

				r2_s <= (y2 - 16) + (v - 128) + ((v - 128) >> 2);
				g2_s <= (y2 - 16) - (v - 128) - ((u - 128) >> 2);
				b2_s <= (y2 - 16) + ((u - 128) << 2);

				// Truncate signed results so no negative values
				if(r1_s > 255)
				begin
					r1 <= 255;
				end
				else if(r1_s > 0)
				begin
					r1 <= r1_s[7:0];
				end
				else
				begin
					r1 <= 0;
				end

				if(r2_s > 255)
				begin
					r2 <= 255;
				end
				else if(r2_s > 0)
				begin
					r2 <= r2_s[7:0];
				end
				else
				begin
					r2 <= 0;
				end

				if(g1_s > 255)
				begin
					g1 <= 255;
				end
				else if(g1_s > 0)
				begin
					g1 <= g1_s[7:0];
				end
				else
				begin
					g1 <= 0;
				end

				if(g2_s > 255)
				begin
					g2 <= 255;
				end
				else if(g2_s > 0)
				begin
					g2 <= g2_s[7:0];
				end
				else
				begin
					g2 <= 0;
				end

				if(b1_s > 255)
				begin
					b1 <= 255;
				end
				else if(b1_s > 0)
				begin
					b1 <= b1_s[7:0];
				end
				else
				begin
					b1 <= 0;
				end

			   if(b2_s > 255)
				begin
					b2 <= 255;
				end
				else if(b2_s > 0)
				begin
					b2 <= b2_s[7:0];
				end
				else
				begin
					b2 <= 0;
				end

				// TODO
				// If image start was a 1 make a note that we need SOP active
				// We will leave EOP for the counter on the other side of the FIFO

				FIFO_WRITE   <= 1'b0;
				HAVE_PIXELS  <= 2'b10;
				
				// The images has started
				image_start <= 1'b0;

				line_start <= 0;
				
				// Back to Y values
				state <= Y1;

				pixel_counter <= pixel_counter + 2;
				
				end
		endcase 

	end

end

endmodule