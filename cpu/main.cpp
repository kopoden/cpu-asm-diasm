#include "cpu.h"

//=======================================================
#define make_log( err_number )                                              \
    do {                                                                    \
        switch (err_number) {                                               \
                                                                            \
            case CPU_OK:                                                    \
                                                                            \
                fprintf(logs,"OK\n");                                       \
                break;                                                      \
                                                                            \
            case CPU_ERR_MEM:                                               \
                                                                            \
                fprintf(logs,"NOT ENOUGH MEMORY TO ALLOCATE\n");            \
                CPU_dump(&CPU1);                                            \
                return CPU_ERR_MEM;                                         \
                                                                            \
            case CPU_NOT_INITIALIZED:                                       \
                                                                            \
                fprintf(logs,"CPU HASN'T BEEN INITIALIZED\n");              \
                CPU_dump(&CPU1);                                            \
                return CPU_NOT_INITIALIZED;                                 \
                                                                            \
            case INCORRECT_MAX_COUNTER:                                     \
                                                                            \
                fprintf(logs,"INCORRECT MAX COUNTER\n");                    \
                CPU_dump(&CPU1);                                            \
                return INCORRECT_MAX_COUNTER;                               \
                                                                            \
            case INCORRECT_PROGRAM_COUNTER:                                 \
                                                                            \
                fprintf(logs,"INCORRECT PROGRAM COUNTER\n");                \
                CPU_dump(&CPU1);                                            \
                return INCORRECT_PROGRAM_COUNTER;                           \
                                                                            \
            case NULL_PM_POINTER:                                           \
                                                                            \
                fprintf(logs,"POINTER TO PROGRAM MEMORY IS NULL\n");        \
                CPU_dump(&CPU1);                                            \
                return NULL_PM_POINTER;                                     \
                                                                            \
            case NUMBER_OF_COMMAND_EXPECTED:                                \
                                                                            \
                fprintf(logs,"A NUMBER OF COMMAND EXPECTED\n");             \
                CPU_dump(&CPU1);                                            \
                return NUMBER_OF_COMMAND_EXPECTED;                          \
                                                                            \
            case STACK_ERROR:                                               \
                                                                            \
                fprintf(logs,"STACK IS INVALID\n");                         \
                CPU_dump(&CPU1);                                           \
                return STACK_ERROR;                                         \
                                                                            \
            case READING_BINARY_ERROR:                                      \
                                                                            \
                fprintf(logs,"AN ERROR OCCURED DURING READING BINARY FILE\n");\
                CPU_dump(&CPU1);                                            \
                return READING_BINARY_ERROR;                                \
                                                                            \
            case FULL_STACK:                                                \
                                                                            \
                fprintf(logs,"STACK IS FULL. CAN'T PUSH.\n");               \
                CPU_dump(&CPU1);                                            \
                return FULL_STACK;                                          \
                                                                            \
            case EMPTY_STACK:                                               \
                                                                            \
                fprintf(logs,"STACK IS EMPTY. CAN'T POP.\n");               \
                CPU_dump(&CPU1);                                            \
                return EMPTY_STACK;                                         \
                                                                            \
            case DIVISION_BY_0:                                             \
                                                                            \
                fprintf(logs,"DIVISION BY ZERO IS FORBIDDEN.\n");           \
                CPU_dump(&CPU1);                                            \
                return DIVISION_BY_0;                                       \
                                                                            \
                                                                            \
            case NEGATIVE_RADICAL:                                          \
                                                                            \
                fprintf(logs,"RADICAL EXPRESSION MUST BE BIGGER THEN 0.\n");\
                CPU_dump(&CPU1);                                            \
                return NEGATIVE_RADICAL;                                     \
                                                                            \
            default:                                                        \
                fprintf(logs,"UNKNOWN ERROR\n");                            \
                CPU_dump(&CPU1);                                            \
                return 0;                                                   \
        }                                                                   \
    } while(0);                                                             \
//===========================================================================
FILE* logs = NULL; //Global
//===========================================================================
int main(int argc, char* argv[]) {

    logs = fopen("logs.txt", "w");

    if (logs == NULL) {

        printf("CAN'T CREATE LOG FILE\n");

        system("pause");

        return 0;
    }

    if (argv[1] == NULL) {

        printf("INPUT BINARY FILE\n");
        fprintf(logs, "INPUT BINARY FILE\n");

        return 0;
    }

    FILE* BinFile = fopen(argv[1], "rb");

    cpu_t CPU1 = {};

    fprintf(logs, "CPU_CTOR == ");
    make_log(CPU_ctor(BinFile, &CPU1));

    make_log(CPU_start(&CPU1));

    fprintf(logs, "CPU_dtor == ");
    make_log(CPU_dtor(&CPU1));

    fclose(BinFile);
    fclose(logs);

    system("pause");

    return 0;
}
