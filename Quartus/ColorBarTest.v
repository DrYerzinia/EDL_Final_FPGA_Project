module ColorBarTest (

	// Inputs
	clk,
	reset,
	ready,
	
	// Bidirectional

	// Outputs
	data,
	startofpacket,
	endofpacket,
	empty,
	valid
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

// Inputs
input				clk;
input				reset;
input						ready;

// Bidirectional

// Outputs
output		[DW:0]	data;
output					startofpacket;
output					endofpacket;
output					empty;
output					valid;

/*****************************************************************************
 *                 Internal Wires and Registers Declarations                 *
 *****************************************************************************/

reg			[ 7:0]	red;
reg			[ 7:0]	green;
reg			[ 7:0]	blue;

// Internal Registers
reg			[9:0]		x;
reg			[9:0]		y;


// Internal Registers

// X position counter
always @(posedge clk)
begin

	if (reset)

		x <= 'h0;					// On reset we start a x: 0, y: 0

	else if (ready)				// We only shift a pixel if downstream is ready for it
	begin
		if (x == (WIDTH - 1))
			x <= 'h0;
		else
			x <= x + 1'b1;
	end
end

// Y position counter
always @(posedge clk)
begin

	if (reset)

		y <= 'h0;					// On reset we start a x: 0, y: 0

	// We only shift a pixel if downstream is ready for it
	// We only shift a row if we are at the end of the line
	else if (ready && (x == (WIDTH - 1)))
	begin
		if (y == (HEIGHT - 1))
			y <= 'h0;
		else
			y <= y + 1'b1;
	end
end

// Color selector
always @(posedge clk)
begin

	if (reset)
	begin
		red 	<= 8'h0;
		green <= 8'h0;
		blue 	<= 8'h0;
	end
	else if (ready)
	begin

		// Simple 3 color bars
	
		if ((x >= 0) && (x < 214))
		begin
			red 	<= 8'hFF;
			green <= 8'h00;
			blue 	<= 8'h00;
		end
		else if ((x >= 214) && (x < 428))
		begin
			red 	<= 8'h00;
			green <= 8'hFF;
			blue 	<= 8'h00;
		end
		else
		begin
			red 	<= 8'h00;
			green <= 8'h00;
			blue 	<= 8'hFF;
		end


	end
end

/*****************************************************************************
 *                            Combinational Logic                            *
 *****************************************************************************/

assign data				= {red, green, blue};
assign startofpacket	= (x == 0) & (y == 0);
assign endofpacket	= (x == (WIDTH - 1)) & (y == (HEIGHT - 1));
assign empty			= 1'b0;
assign valid			= 1'b1;

endmodule