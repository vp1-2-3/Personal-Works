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
//  Fill an array with random numbers and sort them
//
//This file
//   File name: main.cpp
//   Language: Cpp
//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
#include <stdio.h>

extern  char * executive();

int main()
{
    printf("Welcome to Random Products, LLC.\n");
    printf("This software is maintained by Victor Prieto\n");

    char * name  = executive();

    printf("Oh, %s. We hope you enjoyed your arrays. Do come again.\n", name);
    printf("A zero will be returned to the operating system.");

    return 0;
}