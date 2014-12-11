#include "assembler.h"

int main(int argc, char* argv[]) {

    if (argv[1] == 0) return 0;

    FILE* Source = fopen(argv[1], "rb");

    int point = 0;
    while (argv[1][point] != '.') point++;

    if ((argv[1][point + 1] != 'a') || (argv[1][point + 2] != 's') || (argv[1][point + 3] != 'm') || (argv[1][point + 4] != 0)) {
        printf("INVALID INPUT FILE FORMAT\n");
        system("pause");
        return INV_INPUT_FILE;
    }

    char* BinFileName = (char*) calloc (point + 6, sizeof(char));
    ASSERT_MEM(BinFileName != NULL);
    strcpy(BinFileName, argv[1]);

    BinFileName[point + 1] = 'b';
    BinFileName[point + 2] = 'i';
    BinFileName[point + 3] = 'n';

    FILE* Bin = fopen(BinFileName, "wb");

    Command* CommandTable = CommandTableCreator();
    ASSERT_MEM(CommandTable != NULL);

    Lable* LabelTable = LabelTableCreator();
    ASSERT_MEM(LabelTable != NULL);

    if (Assemble(Source, Bin, CommandTable, LabelTable) == OK) {

        printf("SUCCESSFUL COMPILATION\n");
        system("pause");

    }

    fclose(Source);
    fclose(Bin);

    return 0;
}
