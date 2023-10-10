#!/bin/bash

#Author: Daniel C
#Title: BASH compile for C++

rm *.o
rm *.lis
rm *.out

echo " " #Blank line

echo "This will compile the C++ and assemble the ASM file, then link the two."

echo " "

echo "Assemble the X86 file."
nasm -f elf64 -l executive.lis -o executive.o executive.asm -g -gdwarf
nasm -f elf64 -l fill_random_array.lis -o fill_random_array.o fill_random_array.asm -g -gdwarf
nasm -f elf64 -l isnan.lis -o isnan.o isnan.asm -g -gdwarf
nasm -f elf64 -l show_array.lis -o show_array.o show_array.asm -g -gdwarf

echo "Compile the C++ file."
g++ -c -m64 -Wall -std=c++14 -fno-pie -no-pie -o quick_sort.o quick_sort.cpp -g
g++ -c -m64 -Wall -std=c++14 -fno-pie -no-pie -o main.o main.cpp -g

echo "Link the 'O' files."
g++ -m64 -std=c++14 -fno-pie -no-pie -o array.out show_array.o quick_sort.o isnan.o fill_random_array.o main.o executive.o -g

echo "Run the program array.out"
echo " "
./array.out

echo " "

echo "This Bash script file will now terminate.  Bye."

rm *.o
rm *.lis
rm *.out