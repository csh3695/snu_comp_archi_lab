#!/bin/bash

echo $RISCV
sleep 1

if [ ! $NUM_THREADS ]
then
	NUM_THREADS=8	#Set this as the number of logical cores of your CPU.
fi

sudo apt-get install -y autoconf automake autotools-dev curl libmpc-dev \
	libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf \
	libtool patchutils bc zlib1g-dev libexpat-dev device-tree-compiler

#Build Compiler
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
cd riscv-gnu-toolchain
./configure --prefix=$RISCV #--with-arch=rv32gc --with-abi=ilp32d
make -j $NUM_THREADS
cd ../

#Build Proxy Kernel
git clone https://github.com/riscv/riscv-pk
cd riscv-pk
mkdir build
cd build
../configure --prefix=$RISCV --host=riscv64-unknown-elf #--with-abi=ilp32d
make -j $NUM_THREADS
sudo make install
cp ./pk $RISCV/bin/pk
cd ../../

#Build simulator
git clone https://github.com/riscv/riscv-isa-sim
cd riscv-isa-sim
mkdir build
cd build
../configure --prefix=$RISCV
make -j $NUM_THREADS
sudo make install
cd ../../
