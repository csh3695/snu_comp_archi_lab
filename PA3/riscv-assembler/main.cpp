#include "riscv-assembler.h"

#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " [input file]\n";
		return -1;
	}

	std::ifstream ifp(argv[1]);
	if(!ifp)
	{
		std::cerr << "Failed to open " << argv[1] << std::endl;
		return -1;
	}

	riscv_asm assembler(&ifp);
	assembler.assemble();

	ifp.close();
	return 0;
}
