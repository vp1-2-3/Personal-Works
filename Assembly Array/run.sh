#!/bin/bash

#Author: Victor Prieto
#Title: BASH compile for Random Arrays

rm *.o
rm *.lis
rm *.out

echo " " #Blank line

echo "This will compile the C++ and assemble the ASM file, then link the two."

echo " "

echo "Assemble the X86 file."
nasm -f elf64 -l executive.lis -o executive.o executive.asm
nasm -f elf64 -l fill_random_array.lis -o fill_random_array.o fill_random_array.asm
nasm -f elf64 -l isnan.lis -o isnan.o isnan.asm
nasm -f elf64 -l show_array.lis -o show_array.o show_array.asm

echo "Compile the C++ file."
gcc -c -m64 -Wall -std=c11 -fno-pie -no-pie -o compar.o compar.c
gcc -c -m64 -Wall -std=c11 -fno-pie -no-pie -o main.o main.c

echo "Link the 'O' files."
g++ -m64 -std=c++14 -fno-pie -no-pie -o array.out show_array.o compar.o isnan.o fill_random_array.o main.o executive.o

echo "Run the program array.out"
echo " "
./array.out

echo " "

echo "This Bash script file will now terminate.  Bye."

rm *.o
rm *.lis
rm *.out
