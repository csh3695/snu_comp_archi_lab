#ifndef RISCV_ASSEMBLER_H
#define RISCV_ASSEMBLER_H

#include <fstream>
#include <regex>
#include <string>
#include <array>



class riscv_asm
{
public:
	riscv_asm() = delete;
	riscv_asm(std::ifstream *ifp);
	~riscv_asm();

	static const int opcode_mask = 0x7F;

	bool assemble();

	enum class rtype_inst
	{
		r_add,
		r_sub,
		r_xor,
		r_or,
		r_and
	};
	using r_pair = std::pair<std::string, rtype_inst>;
	std::array<r_pair, 5> rtype_inst_name = {	r_pair{"add", rtype_inst::r_add},
							r_pair{"sub", rtype_inst::r_sub},
							r_pair{"xor", rtype_inst::r_xor},
							r_pair{"or", rtype_inst::r_or},
							r_pair{"and", rtype_inst::r_and}};
	bool assemble_rtype(const rtype_inst &inst);	//add, sub, xor, or, and

	enum class itype_inst
	{
		i_addi,
		i_xori,
		i_ori,
		i_andi,
	};
	using i_pair = std::pair<std::string, itype_inst>;
	std::array<i_pair, 4> itype_inst_name = {	i_pair{"addi", itype_inst::i_addi},
							i_pair{"xori", itype_inst::i_xori},
							i_pair{"ori", itype_inst::i_ori},
							i_pair{"andi", itype_inst::i_andi}};
	bool assemble_itype(const itype_inst &inst);	//addi, xori, ori, andi

	bool assemble_beq();	//BNE
	bool assemble_ld();	//LD
	bool assemble_sd();	//SD

private:

	bool assemble_error;
	size_t n_insts;
	std::ifstream *ifp;

	std::regex regex_r, regex_i, regex_b, regex_m;
};

#endif
