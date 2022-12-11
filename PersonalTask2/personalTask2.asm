%include "io.inc"

section .data
letter dd 'l'

section .bss
string resb 32

section .text
global CMAIN
global runTask
global subroutine
global clearGeneralPurposeRegisters

CMAIN:

    mov ebp, esp; for correct debugging
    call clearGeneralPurposeRegisters
    lea edi, [string]
    lea ebx, [string]
    mov ecx, 32
    GET_STRING string, ecx
    NEWLINE
search:
    mov esi, letter
    cmpsb
    je equal
    dec ecx
    jnz search

    ret

equal:
    mov esi, edi
    sub esi, ebx
    PRINT_UDEC 4, esi
    NEWLINE
    jmp search

clearGeneralPurposeRegisters:
    mov eax, 0
    mov ebx, 0
    mov ecx, 0
    mov edx, 0
    mov esi, 0
    mov edi, 0
    ret
