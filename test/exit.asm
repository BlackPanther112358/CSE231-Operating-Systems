segment .data
x dq 0
s times 64 db 0
msg1 db "Please enter an integer: ", 0
msg2 db "Please enter a string: ", 0
integer_format db "%d", 0
string_format db "%s", 0
msg_format db "%s", 0
output_format db 0x0a, "Input String: %s", 0x0a, "Input Integer: %d", 0x0a, 0

segment .text
global main
extern scanf
extern printf

main:

    push rbp
    mov rbp, rsp

    lea rdi, [msg_format]
    lea rsi, [msg1]
    mov rax, 0
    call printf

    lea rdi, [integer_format]
    lea rsi, [x]
    mov rax, 0
    call scanf

    lea rdi, [msg_format]
    lea rsi, [msg2]
    mov rax, 0
    call printf

    lea rdi, [output_format]
    lea rsi, [s]
    mov edx, [x]
    mov rax, 0
    call printf

    lea rdi, [string_format]
    lea rsi, [s]
    mov rax, 0
    call scanf

    pop rbp
    ret

