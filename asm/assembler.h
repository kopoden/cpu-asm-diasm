#ifndef _ASSEMBLER_H_INCL_
#define _ASSEMBLER_H_INCL_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//===================================================================
#define ASSERT_SYNTAX( cond )                                       \
    do {                                                            \
        if ( ! ( cond ) ) {                                         \
            printf ("SYNTAX ERROR ( line %d )\n", LineNum + 1);    \
            return SNTX_ERR;                                        \
        }                                                           \
    } while (0);                                                    \
//===================================================================
#define ASSERT_ARG( cond )                                          \
    do {                                                            \
        if ( ! ( cond ) ) {                                         \
            printf ("IVALID ARGUMENT ( line %d )\n", LineNum + 1); \
            return INV_ARG;                                         \
        }                                                           \
    } while (0);                                                    \
//===========================================================================
#define ASSERT_LABEL( cond )                                                \
    do {                                                                    \
        if ( ! ( cond ) ) {                                                 \
            printf ("LABEL IS ALREADY IN USE ( line %d )\n", LineNum + 1); \
            return LABEL_ERR;                                               \
        }                                                                   \
    } while (0);                                                            \
//===========================================================================
#define ASSERT_LABEL2( cond )                                               \
    do {                                                                    \
        if ( ! ( cond ) ) {                                                 \
            printf ("LABEL IS UNKNOWN ( line %d )\n", LineNum + 1);        \
            return LABEL_ERR;                                               \
        }                                                                   \
    } while (0);                                                            \
//===========================================================================
#define ASSERT_MEM( cond )                                                  \
    do {                                                                    \
        if ( ! ( cond ) ) {                                                 \
            printf ("MEMORY ALLOCATION ERROR\n( %s ) IN %s, %s ( %d )\n",  \
            #cond, __PRETTY_FUNCTION__,                                     \
            __FILE__, __LINE__ );                                           \
            return ERR_MEM;                                                 \
        }                                                                   \
    } while (0);                                                            \
//===========================================================================
#define ASSERT_ACCESS( cond )                                               \
    do {                                                                    \
        if ( ! ( cond ) ) {                                                 \
            printf ("ACCESS ERROR\n( %s ) IN %s, %s ( %d )\n",             \
            #cond, __PRETTY_FUNCTION__,                                     \
            __FILE__, __LINE__ );                                           \
            return ACCSS_ERR;                                               \
        }                                                                   \
    } while (0);                                                            \
//===========================================================================

//==========CONSTANTS========================================================
#define MAX_COMMAND_LENGTH 100
#define NUM_OF_COMMANDS 21
#define MAX_NUM_OF_LABLES 1000
#define NUM_OF_RIGESTERS 32
//===========================================================================
enum constants {
    OK,
    NOPE,
    ERR_MEM,
    SNTX_ERR,
    INV_ARG,
    ACCSS_ERR,
    LABEL_ERR,
    INV_INPUT_FILE
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

typedef int Label;
//=====================================================================
int check_empty(char* str);
//=====================================================================
char* DeleteWord(char** str);
//=====================================================================
Command* CommandTableCreator (void);
//=====================================================================
int CommandTableDestructor (Command* Table);
//=====================================================================
Label* LabelTableCreator(void);
//=====================================================================
int divide_into_lines(char* buf, int length, char** text);
//=====================================================================
int count_lines(const char* buf, int length);
//=====================================================================
int Assemble (FILE* Source, FILE* Asm);
//=====================================================================

#endif // _ASSEMBLER_H_INCL_
