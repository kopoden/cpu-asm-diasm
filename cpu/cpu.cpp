#include "cpu.h"
//=================================================================================
//=======================DEBUG MODE================================================
//#define DEBUG
//=================================================================================
#ifndef DEBUG

#define CPU_dump( cpu ) ;

#endif // DEBUG
//=================================================================================
int CPU_ctor (FILE* BinFile, cpu_t* cpu) {

    if (cpu == NULL)
        return CPU_NOT_INITIALIZED;

    cpu->PM = NULL;
    cpu->max_counter = 0;
    cpu->prgm_counter = 0;

    for (int i = 0; i < MAX_NUM_OF_REGISTERS; i++)
        cpu->reg[i] = 0;

    stack_ctor(&cpu->Stack);
    stack_resize(&cpu->Stack, STACK_SIZE);

    stack_ctor(&cpu->Address_stack);
    stack_resize(&cpu->Address_stack, ADDRESS_STACK_SIZE);

    if (ReadBinaryFile(BinFile, cpu) != CPU_OK)
        return READING_BINARY_ERROR;

    int check = CPU_VALID(cpu);

    if (check != CPU_OK)
        return check;

    return CPU_OK;
}
//=================================================================================
int ReadBinaryFile (FILE* BinFile, cpu_t* cpu) {

    double Size = 0;

    fread(&Size, sizeof(double), 1, BinFile);
    cpu->max_counter = (int) Size;

    cpu->PM = (double*) calloc (cpu->max_counter, sizeof(double));

    CPU_dump(cpu); //if DEBUG

    if (cpu->PM == NULL)
        return CPU_ERR_MEM;

    for (int i = 0; i < cpu->max_counter; i++)
        fread(&cpu->PM[i], sizeof(double), 1, BinFile);

    return CPU_OK;
}
//=================================================================================
#define safe_push( Stack, number, message ) \
do {                                        \
                                                                            \
    int check_res = push(Stack, number);                                    \
                                                                            \
    switch (check_res) {                                                    \
                                                                            \
        case FULL_STACK:                                                        \
                                                                                \
            fprintf(logs, "%s (%d) == FULL_STACK\n", message, cpu->prgm_counter);\
                                                                                \
            return FULL_STACK;                                                  \
    }                                                                       \
} while (0);                                                                         \
//=================================================================================
#define safe_pop( Stack, number, message ) \
do {                                        \
                                                                            \
    int check_res = pop(Stack, number);                                    \
                                                                            \
    switch (check_res) {                                                    \
                                                                            \
        case EMPTY:                                                        \
                                                                                \
            fprintf(logs, "%s (%d) == EMPTY\n", message, cpu->prgm_counter);      \
                                                                                \
            return EMPTY;                                                  \
                                                                            \
    }                                                                       \
} while (0);                                                                           \
//=================================================================================
#define ok_op( message )                                            \
do {                                                                \
    fprintf(logs, "%s (%d) == OK\n", message, cpu->prgm_counter);   \
} while (0);                                                                  \
//=================================================================================
int CPU_start (cpu_t* cpu) {

    int check = CPU_VALID(cpu);

    if (check != CPU_OK) {
        return check;
    }

    CPU_default(cpu);

    CPU_dump(cpu); //if DEBUG

    while ((int) cpu->PM[cpu->prgm_counter] != END && cpu->prgm_counter < cpu->max_counter) {

        double e1 = 0, e2 = 0, buf = 0;

        switch ((int) cpu->PM[cpu->prgm_counter]) {

            case PUSH:

                safe_push(&cpu->Stack, cpu->reg[(int) cpu->PM[cpu->prgm_counter + 1]], "PUSH");

                ok_op("PUSH");

                cpu->prgm_counter += 2;

                break;

            case PUSH_DOUBLE:

                safe_push(&cpu->Stack, cpu->PM[cpu->prgm_counter + 1], "PUSH DOUBLE");

                ok_op("PUSH DOUBLE");

                cpu->prgm_counter += 2;

                break;

            case POP:

                safe_pop(&cpu->Stack, &cpu->reg[(int) cpu->PM[cpu->prgm_counter + 1]], "POP");

                ok_op("POP");

                cpu->prgm_counter += 2;

                break;

            case ADD:

                safe_pop(&cpu->Stack, &e1, "ADD");

                safe_pop(&cpu->Stack, &e2, "ADD");

                buf = e1 + e2;

                safe_push(&cpu->Stack, buf, "ADD");

                ok_op("ADD");

                cpu->prgm_counter++;

                break;

            case SUB:

                safe_pop(&cpu->Stack, &e1, "SUB");

                safe_pop(&cpu->Stack, &e2, "SUB");

                buf = e2 - e1;

                safe_push(&cpu->Stack, buf, "SUB");

                ok_op("SUB");

                cpu->prgm_counter++;

                break;

            case MUL:

                safe_pop(&cpu->Stack, &e1, "MUL");

                safe_pop(&cpu->Stack, &e2, "MUL");

                buf = e2 * e1;

                safe_push(&cpu->Stack, buf, "MUL");

                ok_op("MUL");

                cpu->prgm_counter++;

                break;

            case DIV:

                safe_pop(&cpu->Stack, &e1, "DIV");

                if (e1 == 0) {
                    fprintf(logs, "DIV (%d) == DIVISION BY ZERO\n", cpu->prgm_counter);

                    return DIVISION_BY_0;
                }

                safe_pop(&cpu->Stack, &e2, "DIV");

                buf = e2 / e1;

                safe_push(&cpu->Stack, buf, "DIV");

                ok_op("DIV");

                cpu->prgm_counter++;

                break;

            case SQRT:

                safe_pop(&cpu->Stack, &e1, "SQRT");

                if (e1 < 0) {

                    fprintf(logs, "SQRT (%d) == NEAGTIVE_RADICAL_EXPRESSION\n", cpu->prgm_counter);

                    return NEGATIVE_RADICAL;
                }

                buf = sqrt(e1);

                safe_push(&cpu->Stack, buf, "SQRT");

                ok_op("SQRT");

                cpu->prgm_counter++;

                break;

            case RET:

                safe_pop(&cpu->Address_stack, &e1, "RET");

                ok_op("RET");

                cpu->prgm_counter = (int) e1;

                break;

            case OUT:

                safe_pop(&cpu->Stack, &e1, "OUT");

                printf("%lg\n", e1);

                ok_op("OUT");

                cpu->prgm_counter++;

                break;

            case END:

                ok_op("END");

                return CPU_OK;

            case IN:

                scanf("%lg", &buf);

                safe_push(&cpu->Stack, buf, "IN");

                ok_op("IN");

                cpu->prgm_counter++;

                break;

            case JAE:

                safe_pop(&cpu->Stack, &e1, "JAE");

                safe_pop(&cpu->Stack, &e2, "JAE");

                if (e2 >= e1) {

                    cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                    ok_op("JAE");

                    break;
                }

                ok_op("JAE");

                cpu->prgm_counter += 2;

                break;

            case JB:

                safe_pop(&cpu->Stack, &e1, "JB");

                safe_pop(&cpu->Stack, &e2, "JB");

                if (e2 < e1) {

                    cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                    ok_op("JB");

                    break;
                }

                ok_op("JB");

                cpu->prgm_counter += 2;

                break;

            case JBE:

                safe_pop(&cpu->Stack, &e1, "JBE");

                safe_pop(&cpu->Stack, &e2, "JBE");

                if (e2 <= e1) {

                    cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                    ok_op("JBE");

                    break;
                }

                ok_op("JBE");

                cpu->prgm_counter += 2;

                break;

            case JE:

                safe_pop(&cpu->Stack, &e1, "JE");

                safe_pop(&cpu->Stack, &e2, "JE");

                if (e2 == e1) {

                    cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                    ok_op("JE");

                    break;
                }

                ok_op("JE");

                cpu->prgm_counter += 2;

                break;

            case JNE:

                safe_pop(&cpu->Stack, &e1, "JNE");

                safe_pop(&cpu->Stack, &e2, "JNE");

                if (e2 != e1) {

                    cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                    ok_op("JNE");

                    break;
                }

                ok_op("JNE");

                cpu->prgm_counter += 2;

                break;

            case JMP:

                ok_op("JMP");

                cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                break;

            case JA:

                safe_pop(&cpu->Stack, &e1, "JA");

                safe_pop(&cpu->Stack, &e2, "JA");

                if (e2 > e1) {

                    cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                    ok_op("JA");

                    break;
                }

                ok_op("JA");

                cpu->prgm_counter += 2;

                break;

            case CALL:

                safe_push(&cpu->Address_stack, cpu->prgm_counter + 2, "CALL");

                ok_op("CALL");

                cpu->prgm_counter = (int) cpu->PM[cpu->prgm_counter + 1];

                break;

            case MOV:

                cpu->reg[(int) cpu->PM[cpu->prgm_counter + 1]] = cpu->PM[cpu->prgm_counter + 2];

                ok_op("MOV");

                cpu->prgm_counter += 3;

                break;

            default:

                return NUMBER_OF_COMMAND_EXPECTED;
        }
    }

    return CPU_OK;
}
//=================================================================================
int CPU_VALID (cpu_t* cpu) {

    if (cpu == NULL)
        return CPU_NOT_INITIALIZED;

    if (cpu->max_counter < 0)
        return INCORRECT_MAX_COUNTER;

    if (cpu->PM == NULL)
        return NULL_PM_POINTER;

    if (cpu->prgm_counter < 0)
        return INCORRECT_PROGRAM_COUNTER;

    int check_stack = stack_ok(&cpu->Stack);

    if (check_stack != OK && check_stack != FULL && check_stack != EMPTY)
        return STACK_ERROR;

    check_stack = stack_ok(&cpu->Address_stack);

    if (check_stack != OK && check_stack != FULL && check_stack != EMPTY)
        return STACK_ERROR;

    return CPU_OK;
}
//=================================================================================
int CPU_default (cpu_t* cpu) {

    if (cpu == NULL)
        return CPU_NOT_INITIALIZED;

    cpu->prgm_counter = 0;

    for (int i = 0; i < MAX_NUM_OF_REGISTERS; i++)
        cpu->reg[i] = 0;

    while (stack_ok(&cpu->Address_stack) != EMPTY)
        pop(&cpu->Address_stack, NULL);

    while (stack_ok(&cpu->Stack) != EMPTY)
        pop(&cpu->Stack, NULL);

    return CPU_OK;
}
//=================================================================================
int CPU_dtor(cpu_t* cpu) {

    if (cpu == NULL)
        return CPU_NOT_INITIALIZED;

    cpu->prgm_counter = 0;

    free(cpu->PM);
    cpu->PM = NULL;

    stack_dtor(&cpu->Stack);

    stack_dtor(&cpu->Address_stack);

    return CPU_OK;
}
//=================================================================================
#undef CPU_dump
void CPU_dump (cpu_t* cpu) {

    FILE* dump = fopen("dump.txt", "a");

    if (cpu == NULL) {

        fprintf(dump, "CPU_DUMP IS IMPOSSIBLE. CPU_POINTER = NULL.\n");
        return;

    }

    stack_dump(&cpu->Stack, dump);

    stack_dump(&cpu->Address_stack, dump);

    fprintf(dump, "CPU DUMP:\nPROGRAM COUNTER: %d\nMAX COUNTER: %d\nREGISTERS:", \
           cpu->prgm_counter, cpu->max_counter);

    for (int i = 0; i < MAX_NUM_OF_REGISTERS; i++)
        fprintf(dump, " |%d (%lg)| ", i, cpu->reg[i]);

    fprintf(dump, "\nPM:");

    if (cpu->PM == NULL) {

        fprintf(dump, "UNKNOWN\n");
        return;

    }

    for (int i = 0; i < cpu->max_counter; i++)
        fprintf(dump, " %lg", cpu->PM[i]);

    fprintf(dump, "\n*************************************************************\n\n");

    fclose(dump);
}
//=================================================================================
