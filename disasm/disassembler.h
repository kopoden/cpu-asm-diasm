#ifndef _DISASSEMBLER_H_INCL_
#define _DISASSEMBLER_H_INCL_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define NUM_OF_COMMANDS 21
#define MAX_NUM_OF_LABLES 1000
#define NUM_OF_REGISTERS 32

const char AVAILABLE_FILE_FORMAT[4] = "bin";

enum errors {
    OK,
    ERR_MEM,
    ADDRESS_ERR,
    INV_INPUT_FILE,
    UNKNOWN_CMD,
    UNKNOWN_ERR,
    READ_FILE_ERR
};
//========================================================================
enum commands {
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    RET,
    OUT,
    END,
    JAE,
    JB,
    JBE,
    JE,
    JNE,
    JMP,
    JA,
    CALL,
    MOV,
    IN,
    SQRT,
    PUSH_DOUBLE
};
//=====================================================================
typedef struct {

    const char* Name;
    int Arg;

} Command;
//=====================================================================
int CommandTableCreator (Command** CommandTable);
//=====================================================================
int disassembly (FILE* BinFile, FILE* Asm);
//=====================================================================
#define check( err_number )                                                 \
    do {                                                                    \
        switch (err_number) {                                               \
                                                                            \
            case OK:                                                        \
                break;                                                      \
                                                                            \
            case ERR_MEM:                                                   \
                                                                            \
                printf("NOT ENOUGH MEMORY TO ALLOCATE\n");                  \
                return ERR_MEM;                                             \
                                                                            \
            case ADDRESS_ERR:                                               \
                                                                            \
                printf("INVALID ADDRESS\n");                                \
                return ADDRESS_ERR;                                         \
                                                                            \
            case INV_INPUT_FILE:                                            \
                                                                            \
                printf("INCOMPATIBLE OR EMPTY INPUT FILE\n");               \
                return INV_INPUT_FILE;                                      \
                                                                            \
            case READ_FILE_ERR:                                             \
                                                                            \
                printf("READING FILE ERROR\n");                             \
                return READ_FILE_ERR;                                       \
                                                                            \
            case UNKNOWN_CMD:                                               \
                                                                            \
                printf("UNKNOWN COMMAND\n");                                \
                return UNKNOWN_CMD;                                         \
                                                                            \
            default:                                                        \
                                                                            \
                printf("UNKNOWN ERROR\n");                                  \
                return UNKNOWN_ERR;                                         \
        }                                                                   \
    } while(0);                                                             \
//=====================================================================
#endif // _DISASSEMBLER_H_INCL_
