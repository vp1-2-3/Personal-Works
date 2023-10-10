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
;Purpose: This file was made to display the contents of the array

;This file
;   File name: show_array.asm
;   Language: X86 with Intel syntax.
;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**

extern printf
global show_array

segment .data

id     db "IEEE754			Scientific Decimal", 10, 0
format db "0x%016lx      %18.13e", 10, 0

segment .bss

segment .text

show_array:

push rbp
mov  rbp,rsp
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

push qword 0

mov r15, rdi; copy array into r15
mov r14, rsi; copy array size into r14
mov r13, 0

push qword 0
mov rax, 0
mov rdi, id
call printf
pop rax

beginLoop:

cmp r13,r14
je exitloop

push qword 0
mov rax, 1
mov rdi, format
mov rsi, [r15 + 8 * r13]
movsd xmm0, [r15 + 8 * r13]
call printf
pop rax

inc r13
jmp beginLoop

exitloop:

pop rax


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