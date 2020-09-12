/*-----------------------------------------------------------------------------

4190.308-002 Computer Architecture

Instructor: Prof. Jae W. Lee (jaewlee@snu.ac.kr)

Homework #3: RISC-V Pipeline in Verilog

Description:
	This module is your verilog pipeline.

-----------------------------------------------------------------------------*/

module riscv_pipeline
(
	input clk,
	input reset
);

	//IF stage
	reg [63:0] IF_pc;
	wire [31:0] IF_inst;
	
	//ID stage
	reg [31:0] ID_inst;

	wire [6:0] ID_opcode;
	wire [2:0] ID_funct3;
	wire [6:0] ID_funct7;
	wire [4:0] ID_rs1, ID_rs2, ID_rd;
	wire [63:0] ID_rf_data_rs1, ID_rf_data_rs2;
	wire [63:0] ID_rs1_data, ID_rs2_data;
	wire [63:0] ID_imm64;
	wire ID_alu_src;
	wire ID_mem_to_reg;
	wire ID_reg_write;
	wire ID_mem_read;
	wire ID_mem_write;
	wire [2:0] ID_alu_op;
	wire ID_halt;


	//EX stage
	reg [63:0] EX_rs1_data, EX_rs2_data;
	reg [63:0] EX_imm64;
	reg [4:0] EX_rd;
	reg EX_alu_src;
	reg EX_mem_to_reg;
	reg EX_reg_write;
	reg EX_mem_read;
	reg EX_mem_write;
	reg [2:0] EX_alu_op;
	reg EX_halt;

	wire [63:0] alu_lhs, alu_rhs, EX_alu_result;
	wire alu_zero, alu_sign;

	//Mem stage
	reg [63:0] MEM_rs2_data;
	reg [63:0] MEM_alu_result;
	reg MEM_zero, MEM_sign;
	reg [4:0] MEM_rd;
	reg MEM_mem_to_reg;
	reg MEM_reg_write;
	reg MEM_mem_read;
	reg MEM_mem_write;
	reg MEM_halt;

	wire [63:0] MEM_read_data;
	wire [63:0] MEM_fwd;

	//WB stage
	reg [63:0] WB_alu_result;
	reg [63:0] WB_mem_rddata;
	reg [4:0] WB_rd;
	reg WB_reg_write;
	reg WB_mem_to_reg;

	wire [63:0] WB_write_data;

	//Forwarding Signal
	wire [1:0] Forward_A;
	wire [1:0] Forward_B;

	//Forwarded Data
	wire [63:0] ID_fwd_data_rs1;
	wire [63:0] ID_fwd_data_rs2;
	
	//Stall
	//--------------------Forwarding Unit-----------------------
	assign Forward_A = ((EX_rd != 5'b0 && EX_reg_write && EX_rd == ID_rs1) ? 2'b01 :
								((MEM_rd != 5'b0 && MEM_reg_write && MEM_rd == ID_rs1) ? 2'b10 : 
								((WB_rd != 5'b0 && WB_reg_write && WB_rd == ID_rs1) ? 2'b11 : 2'b00)));
	assign Forward_B = ((EX_rd != 5'b0 && EX_reg_write && EX_rd == ID_rs2) ? 2'b01 :
								((MEM_rd != 5'b0 && MEM_reg_write && MEM_rd == ID_rs2) ? 2'b10 : 
								((WB_rd != 5'b0 && WB_reg_write && WB_rd == ID_rs2) ? 2'b11 : 2'b00)));

	//--------------------Stall Condition-----------------------
	wire Branch_Stall;
	wire RAW_Stall;
	assign Branch_Stall = (ID_opcode == 7'b1100011) ? 1 : 0;
	assign RAW_Stall = (EX_rd != 5'b0 && EX_reg_write && EX_mem_read && (EX_rd == ID_rs1 || EX_rd == ID_rs2));
	//--------------------IF stage-----------------------
	rom64 imem(IF_pc, IF_inst);
	always @(posedge clk)
	begin
/*		$display("ID_opcode = %h\t Branch_Stall = %d", ID_opcode, Branch_Stall);
		if(ID_opcode == 'h63) $display("BEQ");
		if(ID_opcode == 'h33) $display("Rtype");
		if(ID_opcode == 'h3) $display("Load");
		if(ID_opcode == 'h13) $display("Itype");
		if(ID_opcode == 'h23) $display("STORE");
*/
	end
	always @(posedge clk)
	begin
//		if(Branch_Stall //이전에 branch, 지금도 branch)
		if(Breq)
		begin
			//$display("Taken!! %d, rs1 = %d, rs2 = %d", (ID_imm64<<2), ID_fwd_data_rs1, ID_fwd_data_rs2);
			IF_pc <= reset ? 64'h0 : IF_pc + (ID_imm64<<2)-4;
			ID_inst <= 32'h0;
		end
		else if(Branch_Stall)
		begin
//			$display("NOTTaken!! %d, rs1 = %d, rs2 = %d", (ID_imm64)*4, ID_fwd_data_rs1, ID_fwd_data_rs2);
			IF_pc <= reset ? 64'h0 : IF_pc + 4;
			ID_inst <= reset ? 32'h0 : IF_inst;
		end
		else if(RAW_Stall)
		begin
			IF_pc <= reset ? 64'h0 : IF_pc;
			ID_inst <= reset ? 64'h0 : ID_inst;
		end
		else
		begin
			IF_pc <= reset ? 64'h0 : IF_pc + 4;
			ID_inst <= reset ? 32'h0 : IF_inst;
		end
	end
	
	//--------------------ID stage-----------------------

	inst_decoder id_unit(	.inst(ID_inst),
				.opcode(ID_opcode),
				.funct3(ID_funct3),
				.funct7(ID_funct7),
				.rs1(ID_rs1),
				.rs2(ID_rs2),
				.rd(ID_rd),
				.imm64(ID_imm64));

	pipeline_ctl id_ctl(	.opcode(ID_opcode),
				.funct3(ID_funct3),
				.funct7(ID_funct7),
				.alu_src(ID_alu_src),
				.mem_to_reg(ID_mem_to_reg),
				.reg_write(ID_reg_write),
				.mem_read(ID_mem_read),
				.mem_write(ID_mem_write),
				.alu_operation(ID_alu_op),
				.halt(ID_halt));

	reg_file id_regfile(	.clk(clk), .rs1(ID_rs1), .rs2(ID_rs2),
				.rs1_data(ID_rf_data_rs1),
				.rs2_data(ID_rf_data_rs2),
				.rd(WB_rd), .write(WB_reg_write),
				.write_data(WB_write_data));

	assign ID_fwd_data_rs1 = (Forward_A == 2'b0 ? ID_rf_data_rs1 :
										(Forward_A == 2'b01 ? EX_alu_result :
										(Forward_A == 2'b10 ? (MEM_mem_read ? MEM_read_data : MEM_alu_result) : WB_write_data)));
	assign ID_fwd_data_rs2 = (Forward_B == 2'b0 ? ID_rf_data_rs2 :
										(Forward_B == 2'b01 ? EX_alu_result :
										(Forward_B == 2'b10 ? (MEM_mem_read ? MEM_read_data : MEM_alu_result) : WB_write_data)));
	assign Breq = ((ID_fwd_data_rs1 == ID_fwd_data_rs2) && Branch_Stall) ? 1 : 0;
/*	always @(negedge clk)
	begin
		$display("STALL : %d, EX_rd %d, EX_reg_write %d, EX_mem_read %d, ID_rs1 %d, ID_rs2 %d", RAW_Stall, EX_rd, EX_reg_write, EX_mem_read, ID_rs1, ID_rs2);
		$display("FwdA = %d, FwdB = %d, RAW_STALL = %d, ID_fwdrs1 = %d, ID_fwdrs2 = %d", Forward_A, Forward_B, RAW_Stall, ID_fwd_data_rs1, ID_fwd_data_rs2);
	end*/
	//ID/EX pipeline registers
	always @(posedge clk)
	begin
		if(RAW_Stall || Branch_Stall == 1)
		begin
			EX_alu_src	<= 1'h0;
			EX_mem_to_reg	<= 1'h0;
			EX_reg_write	<= 1'h0;
			EX_mem_read	<= 1'h0;
			EX_mem_write <= 1'h0;
			EX_alu_op	<= 3'h0;
			EX_halt		<= 1'h0;

			EX_rs1_data	<= 64'h0;
			EX_rs2_data	<= 64'h0;
			EX_imm64	<= 64'h0;
			EX_rd		<= 5'h0;
		end
		else
		begin
			EX_alu_src	<= (reset) ? 1'h0 : ID_alu_src;
			EX_mem_to_reg	<= (reset) ? 1'h0 : ID_mem_to_reg;
			EX_reg_write	<= (reset) ? 1'h0 : ID_reg_write;
			EX_mem_read	<= (reset) ? 1'h0 : ID_mem_read;
			EX_mem_write	<= (reset) ? 1'h0 : ID_mem_write;
			EX_alu_op	<= (reset) ? 3'h0 : ID_alu_op;
			EX_halt		<= (reset) ? 1'h0 : ID_halt;

			EX_rs1_data	<= (reset) ? 64'h0 : ID_fwd_data_rs1;//ID_rf_data_rs1;
			EX_rs2_data	<= (reset) ? 64'h0 : ID_fwd_data_rs2;//ID_rf_data_rs2;
			EX_imm64	<= (reset) ? 64'h0 : ID_imm64;
			EX_rd		<= (reset) ? 5'h0 : ID_rd;
		end
	end

	//------------------EX stage-----------------------

	assign alu_lhs = EX_rs1_data;
	assign alu_rhs = EX_alu_src ? EX_imm64 : EX_rs2_data;

	//ALU
	alu EX_alu(	.op(EX_alu_op),
			.lhs(alu_lhs), .rhs(alu_rhs),
			.result(EX_alu_result),
			.zero(alu_zero), .sign(alu_sign));

	//EX/MEM pipeline registers
	always @(posedge clk)
	begin
		MEM_mem_to_reg	<= (reset) ? 1'h0 : EX_mem_to_reg;
		MEM_reg_write	<= (reset) ? 1'h0 : EX_reg_write;
		MEM_mem_read	<= (reset) ? 1'h0 : EX_mem_read;
		MEM_mem_write	<= (reset) ? 1'h0 : EX_mem_write;
		MEM_halt	<= (reset) ? 1'h0 : EX_halt;

		MEM_rs2_data	<= (reset) ? 64'h0 : EX_rs2_data;
		MEM_alu_result	<= (reset) ? 64'h0 : EX_alu_result;
		MEM_zero	<= (reset) ? 1'h0 : alu_zero;
		MEM_sign	<= (reset) ? 1'h0 : alu_sign;
		MEM_rd		<= (reset) ? 5'h0 : EX_rd;
		
	end

	//--------------------Mem stage------------------------

	mem64 MEM_dmem(	.clk(clk),
			.write_enable(MEM_mem_write),
			.halt(MEM_halt),
			.address(MEM_alu_result),
			.write_data(MEM_rs2_data),
			.read_data(MEM_read_data));

	//MEM/WB pipeline registers
	always @(posedge clk)
	begin
		WB_reg_write	<= (reset) ? 1'h0 : MEM_reg_write;
		WB_rd		<= (reset) ? 5'h0 : MEM_rd;
		WB_alu_result	<= (reset) ? 64'h0 : MEM_alu_result;
		WB_mem_rddata	<= (reset) ? 64'h0 : MEM_read_data;
		WB_mem_to_reg	<= (reset) ? 1'h0 : MEM_mem_to_reg;
	end

	//--------------------WB stage-----------------------
	assign WB_write_data = WB_mem_to_reg ? WB_mem_rddata : WB_alu_result;
	
endmodule