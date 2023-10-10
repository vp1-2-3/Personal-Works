;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
;
;Author information
;  Author name: Victor Prieto
;  Author email: victorprie@csu.fullerton.edu
;
;Program information
;  Program name: Random Products Program
;  Programming languages: 3 modules in C, 4 modules in X86
;  Date program began: 2023, Mar 5
;  Date of last update: 2023, Mar 13
;  Files in this program: main.c, executive.asm, run.sh, fill_random_array, show_array, quick_sort.c, compar.c
;  Status: Finished.
;
;Purpose
;  This module is the manager for all other files
;
;This file
;  File name: executive.asm
;  Language: X86 with Intel syntax.
;  Assemble: nasm -f elf64 -l executive.lis -o executive.o executive.asm

extern scanf
extern printf
extern show_array
extern fill_random_array
extern stdin
extern strlen
extern fgets
extern qsort
extern compar

input_length equ 256 ;Max bytes of full name, and title

global executive

segment .data

	name           db "Please Enter your name: ", 0
    inputted_title db "Please enter your title(Mr, Ms, Sargent, Chief, Project Leader, etc): ", 0
    combo          db "Nice to meet you ", 0
    space          db " ", 0
    newLine        db " ", 10, 0

    intro          db "This program will generate 64-bit IEEE float numbers. ", 10, 0
    get_size       db "How many numbers do you want. Today's limit is 100 per customer. ", 0
    arr_size       db "%d", 0
    stored         db "Your numbers have been stored in an array. Here is that array.", 10, 0


    to_sort        db "The array is now being sorted. ", 10, 0
    to_update      db "Here is the updated array. ", 10, 0

	goodbye1       db "Good bye ", 0
    goodbye2       db ". You are welcome any time.", 10, 0

segment .bss

	my_array   resq 100
	input_name resb input_length
    title      resb input_length


segment .text
executive:
;========================= Backup GPRs =================

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

;========= start the program =============

push qword 0   ;Check on the boundary

;Message that displays to prompt user to input name
push qword 0       
mov rax, 0
mov rdi, name  ;"Please Enter your name: ", 0
call printf
pop rax

;Block for name input
push qword 0
mov rax, 0 
mov rdi, input_name         ;move input_name into argument register rdi
mov rsi, input_length       ;provide fgets with second argument, the size of the bytes reserved
mov rdx, [stdin]            ;move the contents at address stdin into 3rd register 
call fgets
pop rax

push qword 0
mov rax, 0
mov rdi, input_name               ;Move input_name into the first argument register
call strlen                     ;Call external function strlen, which returns the length of the string leading up to '\0'
sub rax, 1                      ;The length is stored in rax. Here we subtract 1 from rax to obtain the location of '\n'
mov byte [input_name + rax], 0    ; Replace the byte where '\n' exits with '\0'
pop rax

;Block for title input
push qword 0
mov rax, 0
mov rdi, inputted_title     ;"Please enter your title(Mr, Ms, Sargent, Chief, Project Leader, etc): "
call printf
pop rax
    
;Block to store title
push qword 0
mov rax, 0 
mov rdi, title              ;move input_name into argument register rdi
mov rsi, input_length;      provide fgets with second argument, the size of the bytes reserved
mov rdx, [stdin]            ;move the contents at address stdin into 3rd register 
call fgets
pop rax

push qword 0
mov rax, 0
mov rdi, title                  ;Move title into the first argument register
call strlen                     ;Call external function strlen, which returns the length of the string leading up to '\0'
sub rax, 1                      ;The length is stored in rax. Here we subtract 1 from rax to obtain the location of '\n'
mov byte [title + rax], 0       ;Replace the byte where '\n' exits with '\0'
pop rax

;Block with combination of name and title
push qword 0
mov rax, 0
mov rdi, combo  ;"Nice to meet you "
call printf
pop rax

;Block to display title
push qword 0
mov rax, 0
mov rdi, title
call printf
pop rax

;Block for empty space
push qword 0
mov rax, 0
mov rdi, space
call printf
pop rax

;Block for full name
push qword 0
mov rax, 0 
mov rdi, input_name  
call printf
pop rax

;Block for newline
push qword 0
mov rax, 0
mov rdi, newLine  ;" "
call printf
pop rax

;Block for purpose
push qword 0
mov rax, 0
mov rdi, intro  
call printf
pop rax

;Block to get array size message
push qword 0
mov rax, 0
mov rdi, get_size        
call printf
pop rax

;Block for input of size
push qword 0
mov rax, 0
mov rdi, arr_size
mov rsi, rsp
call scanf
mov r15, [rsp]
pop rax

;Block for newline
push qword 0
mov rax, 0
mov rdi, newLine
call printf
pop rax

;Block for stored message
push qword 0
mov rax, 0
mov rdi, stored
call printf
pop rax

;Block for newline
push qword 0
mov rax, 0
mov rdi, newLine
call printf
pop rax

;Block to call fill_random_array
push qword 0
mov rax, 0 
mov rdi, my_array
mov rsi, r15
call fill_random_array      
mov r14, rax
pop rax

;Block to call show_array without sorting
push qword 0
mov rax, 0
mov rdi, my_array
mov rsi, r14
call show_array
pop rax

;A new line will be shown
push qword 0
mov rax, 0
mov rdi, newLine
call printf
pop rax

;Block to sort first array
push qword 0
mov rdi, my_array
mov rsi, r14
mov rdx, 8
mov rcx, compar
call qsort
pop rax

;message it is being sorted
push qword 0
mov rax, 0
mov rdi, to_sort
call printf
pop rax

;A new line will be shown
push qword 0
mov rax, 0
mov rdi, newLine    ;"  "
call printf
pop rax

;message about updated array
push qword 0
mov rax, 0
mov rdi, to_update     ;"Here is the updated array. "
call printf
pop rax

;A new line will be shown
push qword 0
mov rax, 0
mov rdi, newLine    ;"  "
call printf
pop rax

;New sorted array displayed here
push qword 0
mov rax, 0
mov rdi, my_array       ;The array is copied to the first argument register rdi
mov rsi, r14        ;The number of elements is copied to rsi
call show_array
pop rax

;A new line will be shown
push qword 0
mov rax, 0
mov rdi, newLine    ;"  "
call printf
pop rax

;Goodbye message is displayed
push qword 0
mov rax, 0
mov rdi, goodbye1    ;"Good bye ",
call printf
pop rax

;Title is shown in between Good bye message
push qword 0
mov rax, 0
mov rdi, title   ;Ex: Mr
call printf
pop rax

;Part of the exit message is shown
push qword 0
mov rax, 0
mov rdi, goodbye2  ;". You are welcome any time.", 10, 0
call printf
pop rax

;New line is displayed 
push qword 0
mov rax, 0
mov rdi, newLine   ;" "
call printf
pop rax

;=========================END OF EXECUTIVE MODULE=================================

pop rax

mov rax, input_name

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