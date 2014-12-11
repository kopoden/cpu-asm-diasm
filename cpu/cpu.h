#ifndef _CPU_H_INCL_
#define _CPU_H_INCL_

#include <math.h>
#include <string.h>
#include "stack_functions.h"

//=============================================
extern FILE* logs;
//=============================================

enum CPU_ERRORS {
    CPU_OK = 8,
    CPU_ERR_MEM = 9,
    CPU_NOT_INITIALIZED = 10,
    INCORRECT_MAX_COUNTER = 11,
    INCORRECT_PROGRAM_COUNTER = 12,
    NULL_PM_POINTER = 13,
    NUMBER_OF_COMMAND_EXPECTED = 14,
    STACK_ERROR = 15,
    READING_BINARY_ERROR = 16,
    FULL_STACK = 17,
    EMPTY_STACK = 18,
    DIVISION_BY_0 = 19,
    NEGATIVE_RADICAL = 20
};

const int MAX_NUM_OF_REGISTERS = 32;
const int STACK_SIZE = 10000;
const int ADDRESS_STACK_SIZE = 1000;
const char AVAILABLE_FILE_FORMAT[4] = "bin";

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

typedef struct {

    double* PM;
    int prgm_counter;
    int max_counter;
    STACK_t Stack;
    STACK_t Address_stack;
    double reg[MAX_NUM_OF_REGISTERS];

} cpu_t;

//=============================================================================
int CPU_ctor (FILE* BinFile, cpu_t* cpu);
//=============================================================================
int ReadBinaryFile(FILE* BinFile, cpu_t* cpu);
//=============================================================================
int CPU_default(cpu_t* cpu);
//=============================================================================
int CPU_start (cpu_t* cpu);
//=============================================================================
int CPU_VALID (cpu_t* cpu);
//=============================================================================
int CPU_dtor (cpu_t* cpu);
//=============================================================================
void CPU_dump (cpu_t* cpu);
//=============================================================================

#endif // _CPU_H_INCL_
