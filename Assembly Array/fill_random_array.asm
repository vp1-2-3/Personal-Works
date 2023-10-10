;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
;
;Author information
;  Author name: Victor Prieto
;  Author email: victorprie@csu.fullerton.edu
;
;Program information
;  Program name: Random Arrays
;  Programming languages: C++, C, x86
;  Date program began: 2023 Mar 6
;  Date of last update: 2023 Mar 12
;  Files in this program: executive.asm, main.cpp, show_array.asm, compar.c, run.sh, isnan.asm, fill_random_array.asm
;
;Purpose: This file was made to fill an array with random numbers using rdrand.
;
;This file
;   File name: show_array.asm
;   Language: X86 with Intel syntax.
;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**

global fill_random_array
extern isnan
segment .data

segment .bss

segment .text

fill_random_array:
;Back-up Registers
push rbp 
mov rbp, rsp
push rdi 
push rsi 
push rdx 
push rcx 
push r8 
push r9 
push r10 
push r11 
push r12 
push r13 
push r14 
push r15 
push rbx 
pushf

mov r15, rdi ;actual array
mov r14, rsi ;size of array
mov r13, 0   ;index

beginLoop:
    cmp r13, r14
    je done

    ;Generate random number
    rdrand r12

    ;Check if number is NAN

    mov rax, 0
    mov rdi, r12
    call isnan
    cmp rax, 0
    jne beginLoop

    ;Store number in array
    mov [r15 + 8*r13], r12

    inc r13
    jmp beginLoop

done:

mov rax, r13

;Restore Registers
popf 
pop rbx 
pop r15 
pop r14 
pop r13 
pop r12 
pop r11 
pop r10 
pop r9 
pop r8 
pop rcx 
pop rdx 
pop rsi 
pop rdi 


pop rbp 

ret