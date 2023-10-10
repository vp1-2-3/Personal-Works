//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
//
//  Author information
//  Author name: Victor Prieto
//  Author email: victorprie@csu.fullerton.edu
//
//Program information
//  Program name: Victor Prieto
//  Programming languages: C++, C, x86
//  Date program began: 2023 Mar 6
//  Date of last update: 2023 Mar 12
//  Files in this program: executive.asm, main.cpp, show_array.asm, compar.c, run.sh, isnan.asm, fill_random_array.asm
//  Status: Finished.
//
//Purpose
//  Use the compar function to sort the random array.
//
//This file
//   File name: compar.c
//   Language: Cpp
//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**

#include <stdbool.h>

extern int compar(const void * a, const void * b);

int compar(const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return 1;
    if (*(double*)a < *(double*)b) return -1;
    return 0;
}