#include "disassembler.h"

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
                system("pause");                                            \
                return ERR_MEM;                                             \
                                                                            \
            case ADDRESS_ERR:                                               \
                                                                            \
                printf("INVALID ADDRESS\n");                                \
                system("pause");                                            \
                return ADDRESS_ERR;                                         \
                                                                            \
            case INV_INPUT_FILE:                                            \
                                                                            \
                printf("INCOMPATIBLE OR EMPTY INPUT FILE\n");               \
                system("pause");                                            \
                return INV_INPUT_FILE;                                      \
                                                                            \
            case READ_FILE_ERR:                                             \
                                                                            \
                printf("READING FILE ERROR\n");                             \
                system("pause");                                            \
                return READ_FILE_ERR;                                       \
                                                                            \
            case UNKNOWN_CMD:                                               \
                                                                            \
                printf("UNKNOWN COMMAND\n");                                \
                system("pause");                                            \
                return UNKNOWN_CMD;                                         \
                                                                            \
            default:                                                        \
                                                                            \
                printf("UNKNOWN ERROR\n");                                  \
                system("pause");                                            \
                return UNKNOWN_ERR;                                         \
        }                                                                   \
    } while(0);                                                             \

int main(int argc, char* argv[]) {

    if (argv[1] == NULL) {

        printf("PLEASE, INPUT BINARY FILE\n");

        system("pause");

        return READ_FILE_ERR;
    }

    FILE* Bin = fopen(argv[1], "rb");

    if (Bin == NULL) {

        printf("FILE READING ERROR\n");

        system("pause");

        return READ_FILE_ERR;
    }

    FILE* Asm = fopen("res.asm", "w");

    Command* CommandTable = NULL;

    check(CommandTableCreator(&CommandTable));

    check(disassembly(Bin, Asm, CommandTable));

    printf("SUCCESS!\n");
    system("pause");

    fclose(Bin);
    fclose(Asm);

    return 0;
}

