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
;Purpose: This file was made to check for NAN's when calling rdrand.

;This file
;   File name: isnan.asm
;   Language: X86 with Intel syntax.
;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**

global isnan

segment .data
;Empty
segment .bss
;Empty
segment .text

isnan:
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

;block to check if NAN
mov r15, rdi
shl r15, 1
shr r15, 53
cmp r15, 2047
je have
mov rax,0
jmp restore

have:
mov rax, 1

;
restore:
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