/*-----------------------------------------------------------------------------

4190.308-002 Computer Architecture

Instructor: Prof. Jae W. Lee (jaewlee@snu.ac.kr)

Homework #3: RISC-V Pipeline in Verilog

Description:
	rom64 module is simple 64-bit ROM for instruction memory.
	Output bit width is 32-bit for convinience.
	
	mem64 module is a simple memory module for data load/store

-----------------------------------------------------------------------------*/


module rom64
(
	input	[63:0] address,
	output	[31:0] data_out
);
	parameter FILE = "inst.dat";
	parameter ROM64_BITMASK = 64'h1fc;

	reg	[31:0] data[127:0];	//Address 8:2 is offset. Align: 32bit

	initial
	begin
		//Read inst memory file.
		$readmemh(rom64.FILE, data);
	end

	assign data_out = (address & (~(ROM64_BITMASK))) ? 32'h0 : data[address[8:2]];


endmodule

module mem64
(
	input	clk,
	input	write_enable,
	input	halt,

	input	[63:0] address,
	input	[63:0] write_data,
	output	[63:0] read_data
);
	parameter FILE = "data.dat";
	parameter MEM64_BITMASK = 64'hf8;

	reg	[64:0] data[31:0];

	initial
	begin
		//Read data memory file
		$readmemh(mem64.FILE, data);
	end

	always @(halt) if(halt) $finish;

	always @(posedge clk)
	begin
		if(write_enable && (!(address & (~MEM64_BITMASK))))
		begin
			$display("M[%d] = 0x%x", address[7:3], write_data);
			data[address[7:3]] = write_data;
		end
	end

	assign read_data = ((address & (~MEM64_BITMASK)) || write_enable) ? 64'h0 : data[address[7:3]];

endmodule
