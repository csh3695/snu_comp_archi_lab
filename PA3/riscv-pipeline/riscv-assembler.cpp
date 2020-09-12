#include "riscv-assembler.h"
#include <iostream>
#include <fstream>
#include <regex>

#include <cstdio>

using std::cout;
using std::cerr;
using std::endl;

using std::regex;
using std::ifstream;

riscv_asm::riscv_asm(ifstream *ifp)
{
	this -> assemble_error = false;
	this -> n_insts = 0;
	this -> ifp = ifp;

	//Regular expression compilation
	this -> regex_r = regex("x([0-9]+)([, ]+x)([0-9]+)([, ]+x)([0-9]+)");
	this -> regex_i = regex("x([0-9]+)([, ]+x)([0-9]+)([, ]+)([-]?[0-9]+)");
	this -> regex_b = regex("x([0-9]+)([, ]+x)([0-9]+)([, ]+)([-]?[0-9]+)");
	this -> regex_m = regex("x([0-9]+)([, ]+)([-]?[0-9]+)([(])x([0-9]+)");
}

riscv_asm::~riscv_asm()
{

}

bool riscv_asm::assemble()
{
	char inst[64];
	
	while(!(this -> ifp -> eof()) && !(this -> assemble_error))
	{
		if(++(this -> n_insts) > 128)
		{
			cerr << "Can't support program longer than 128 instructions!\n";
		}

		this -> assemble_error = 1;
		(*ifp) >> inst;
		
		//R-type
		for(auto it = this -> rtype_inst_name.begin() ; it != this -> rtype_inst_name.end() ; it++)
		{
			if(it -> first == inst)
			{
				this -> assemble_error = this -> assemble_rtype(it -> second);
				break;
			}
		}

		//I-type
		for(auto it = this -> itype_inst_name.begin() ; it != this -> itype_inst_name.end() ; it++)
		{
			if(it -> first == inst)
			{
				this -> assemble_error = this -> assemble_itype(it -> second);
				break;
			}
		}

		if(std::string("beq") == inst)
		{
			this -> assemble_error = this -> assemble_beq();
			continue;
		}

		if(std::string("ld") == inst)
		{
			this -> assemble_error = this -> assemble_ld();
			continue;
		}

		if(std::string("sd") == inst)
		{
			this -> assemble_error = this -> assemble_sd();
			continue;
		}

		if(std::string("halt") == inst)
		{
			this -> assemble_error = 0;
			cout << "00000005\n";
			break;
		}

		if(std::string("nop") == inst)
		{
			this -> assemble_error = 0;
			cout << "00000000\n";
			continue;
		}

		if(this -> assemble_error)
		{
			cerr << "Error assembling " << inst << endl;
		}
	}

	for( ; ++(this -> n_insts) <= 128 ; cout << "00000000\n");

	return 0;	//Success
}

bool riscv_asm::assemble_rtype(const rtype_inst &inst)
{
	uint32_t rd, rs1, rs2, funct3, funct7;
	uint32_t result = 0x00000033;	//Opcode

	std::string ipt;
	std::smatch m;

	std::getline(*(this -> ifp), ipt, '\n');
	regex_search(ipt, m, this -> regex_r);

	if(m.size() < 6)
	{
		goto assemble_rtype_error;
	}

	rd = (atoi(m[1].str().c_str()) & 0x0000001F) << 7;
	rs1 = (atoi(m[3].str().c_str()) & 0x0000001F) << 15;
	rs2 = (atoi(m[5].str().c_str()) & 0x00000FFF) << 20;
	funct7 = 0x00000000;

	switch(inst)
	{
		case rtype_inst::r_add:
			funct3 = 0x00000000;
		 	break;

		case rtype_inst::r_sub:
			funct3 = 0x00000000;
			funct7 = 0x00000020;
		 	break;

		case rtype_inst::r_xor:
			funct3 = 0x00000004;
		 	break;

		case rtype_inst::r_or:
			funct3 = 0x00000006;
		 	break;

		case rtype_inst::r_and:
			funct3 = 0x00000007;
			break;
		default:;
	}

	funct3 <<= 12;
	funct7 <<= 25;

	result |= rd | rs1 | rs2 | funct7 | funct3;
	printf("%08x\n", result);

	return 0;

assemble_rtype_error:
	cerr << "Error assembling ";

	switch(inst)
	{
		case rtype_inst::r_add:
		       cerr << "add";
		       break;
		case rtype_inst::r_sub:
		       cerr << "sub";
		       break;
		case rtype_inst::r_xor:
		       cerr << "xor";
		       break;
		case rtype_inst::r_or:
		       cerr << "or";
		       break;
		case rtype_inst::r_and:
			cerr << "and";
			break;
	}

	cerr << ipt << endl;
	return 1;
}

bool riscv_asm::assemble_itype(const itype_inst &inst)
{
	uint32_t rd, rs1, funct3, imm12;
	uint32_t result = 0x00000013;	//Opcode

	std::string ipt;
	std::smatch m;

	std::getline(*(this -> ifp), ipt, '\n');
	regex_search(ipt, m, this -> regex_i);

	if(m.size() < 6)
	{
		goto assemble_itype_error;
	}

	rd = (atoi(m[1].str().c_str()) & 0x0000001F) << 7;
	rs1 = (atoi(m[3].str().c_str()) & 0x0000001F) << 15;
	imm12 = (atoi(m[5].str().c_str()) & 0x00000FFF) << 20;
	switch(inst)
	{
		case itype_inst::i_addi:
			funct3 = 0x00000000;
		 	break;

		case itype_inst::i_xori:
			funct3 = 0x00000004;
		 	break;

		case itype_inst::i_ori:
			funct3 = 0x00000006;
		 	break;

		case itype_inst::i_andi:
			funct3 = 0x00000007;
			break;
		default:;
	}
	funct3 <<= 12;

	result |= rd | rs1 | funct3 | imm12;
	printf("%08x\n", result);

	return 0;

assemble_itype_error:

	cerr << "Error assembling ";

	switch(inst)
	{
		case itype_inst::i_addi:
			cerr << "addi";
			break;
		case itype_inst::i_xori:
			cerr << "xori";
			break;
		case itype_inst::i_ori:
			cerr << "ori";
			break;
		case itype_inst::i_andi:
			cerr << "andi";
			break;
	}

	cerr << ipt << endl;
	return 1;
}

bool riscv_asm::assemble_beq()
{
	uint32_t rs1, rs2, imm12, imm_extended;
	uint32_t result = 0x00000063;	//Opcode, funct3(0)

	std::string ipt;
	std::smatch m;

	std::getline(*(this -> ifp), ipt, '\n');
	regex_search(ipt, m, this -> regex_b);

	if(m.size() < 6)
	{
		cerr << "Error assembling beq" << ipt << endl;
		return 1;
	}

	rs1 = (atoi(m[1].str().c_str()) & 0x0000001F) << 15;
	rs2 = (atoi(m[3].str().c_str()) & 0x0000001F) << 20;

	/*
	imm12 = (atoi(m[5].str().c_str()) & 0x00003FFC) >> 1;
	imm_extended = 	((imm12 & 0x00001000) << 19) |
			((imm12 & 0x00000800) >> 4) |
			((imm12 & 0x000007E0) << 20) |
			((imm12 & 0x0000001E) << 7);
	*/
	imm12 = (atoi(m[5].str().c_str()) & 0x00001FFE);
	imm_extended = 	((imm12 & 0x00001000) << 19) |
			((imm12 & 0x00000800) >> 4) |
			((imm12 & 0x000007E0) << 20) |
			((imm12 & 0x0000001E) << 7);

	result |= rs1 | rs2 | imm_extended;
	printf("%08x\n", result);

	return 0;
}

bool riscv_asm::assemble_ld()
{
	uint32_t rd, rs1, imm12;
	uint32_t result = 0x00003003;	//Opcode, funct3(011)

	std::string ipt;
	std::smatch m;

	std::getline(*(this -> ifp), ipt, '\n');
	regex_search(ipt, m, this -> regex_m);

	if(m.size() < 6)
	{
		cerr << "Error assembling ld" << ipt << endl;
		return 1;
	}
	
	rd = (atoi(m[1].str().c_str()) & 0x0000001F) << 7;
	imm12 = (atoi(m[3].str().c_str()) & 0x00000FFF) << 20;
	rs1 = (atoi(m[5].str().c_str()) & 0x0000001F) << 15;

	result |= rd | imm12 | rs1;
	printf("%08x\n", result);

	return 0;
}

bool riscv_asm::assemble_sd()
{
	uint32_t rs1, rs2, imm12;
	uint32_t result = 0x00003023;	//Opcode, funct3(011)

	std::string ipt;
	std::smatch m;

	std::getline(*(this -> ifp), ipt, '\n');
	regex_search(ipt, m, this -> regex_m);

	if(m.size() < 6)
	{
		cerr << "Error assembling sd" << ipt << endl;
		return 1;
	}

	rs2 = (atoi(m[1].str().c_str()) & 0x0000001F) << 20;
	imm12 = (atoi(m[3].str().c_str()) & 0x00000FFF);
	rs1 = (atoi(m[5].str().c_str()) & 0x0000001F) << 15;

	result |= rs1 | rs2 | ((imm12 & 0x00000FE0) << 20) | ((imm12 & 0x0000001F) << 7);
	printf("%08x\n", result);

	return 0;

}

