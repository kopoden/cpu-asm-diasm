#ifndef _DISASSEMBLER_H_INCL_
#define _DISASSEMBLER_H_INCL_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MAX_COMMAND_LENGTH = 100;
const int NUM_OF_COMMANDS = 21;
const int MAX_NUM_OF_LABLES = 1000;
const int NUM_OF_REGISTERS = 32;
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
int disassembly (FILE* BinFile, FILE* Asm, Command* CmdTable);
//=====================================================================
//=====================================================================
#endif // _DISASSEMBLER_H_INCL_
