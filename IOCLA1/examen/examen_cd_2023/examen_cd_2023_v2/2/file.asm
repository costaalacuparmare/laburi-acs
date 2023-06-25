%include "../../utils/printf32.asm"
extern printf

section .data

int_fmt_newline db "%d ", 10, 0
int_fmt db "%d ", 0
newline_fmt db 10, 0

N dd 12349
arr dd 12341, 2, 3123, 1914, 99995, 6666, 7, 88, 129, 10000
len equ 10

section .bss

;TODO b: Reserve memory for an array named `res` storing  `len` integers
;Hint: `len` is the number of elements. Compute the correct memory size to be reserved.

section .text
global main

; TODO a: Implement `int get_last_digit(unsigned int n)` function that returns the last digit of number `n`

; NOTE: div instruction
; dividend EDX:EAX, divisor register or memory 32 => Results: Quotient in EAX, Remainder in EDX

; Hint:  to find the last digit we divide the given number by 10 and look at the reminder
get_last_digit:
    push ebp
    mov ebp, esp

    leave
    ret

;TODO c: Implement `int compute_sum_digits(unsigned int n)` function that computes the sum of digits found in `n`
compute_sum_digits:
    push ebp
    mov ebp, esp


    leave
    ret

main:
    push ebp
    mov ebp, esp

    ; TODO a: Call `get_last_digit(N)`. Use N from `.data` section.
    ; Print the result using `printf` function. You may use `int_fmt_newline` defined in `.data` section


    ; TODO b: Compute the last digit for all `len` elements of `arr` array and store the results in `res` array.
    ; Thus res[i] = get_last_digit(arr[i])


    ; TODO c: Print all the elements of `res` array with `len` elements on the same line separated by space.
    ; You must add a newline at the end. Use `newline_fmt` string defined in `.data` section.
    ; You must call`printf` function for printing. You may use `int_fmt` defined in `.data` section


    ; TODO d: Compute and print the sum of digits of number `N`.
    ; Use printf for printing. You may use `int_fmt_newline` defined in `.data` section.


    ; Return 0.
    xor eax, eax
    leave
    ret
