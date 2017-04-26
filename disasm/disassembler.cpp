#include "disassembler.h"

//============================================================================
int CommandTableCreator (Command** CommandTable) {

    *CommandTable = (Command*) calloc (NUM_OF_COMMANDS, sizeof(Command));

    if (*CommandTable == NULL)
        return ERR_MEM;

    (*CommandTable)[0].Name = "push";    (*CommandTable)[0].Arg = 2;
    (*CommandTable)[1].Name = "pop";     (*CommandTable)[1].Arg = 2;
    (*CommandTable)[2].Name = "add";     (*CommandTable)[2].Arg = 1;
    (*CommandTable)[3].Name = "sub";     (*CommandTable)[3].Arg = 1;
    (*CommandTable)[4].Name = "mul";     (*CommandTable)[4].Arg = 1;
    (*CommandTable)[5].Name = "div";     (*CommandTable)[5].Arg = 1;
    (*CommandTable)[6].Name = "ret";     (*CommandTable)[6].Arg = 1;
    (*CommandTable)[7].Name = "out";     (*CommandTable)[7].Arg = 1;
    (*CommandTable)[8].Name = "end";     (*CommandTable)[8].Arg = 1;
    (*CommandTable)[9].Name = "jae";     (*CommandTable)[9].Arg = 2;
    (*CommandTable)[10].Name = "jb";     (*CommandTable)[10].Arg = 2;
    (*CommandTable)[11].Name = "jbe";    (*CommandTable)[11].Arg = 2;
    (*CommandTable)[12].Name = "je";     (*CommandTable)[12].Arg = 2;
    (*CommandTable)[13].Name = "jne";    (*CommandTable)[13].Arg = 2;
    (*CommandTable)[14].Name = "jmp";    (*CommandTable)[14].Arg = 2;
    (*CommandTable)[15].Name = "ja";     (*CommandTable)[15].Arg = 2;
    (*CommandTable)[16].Name = "call";   (*CommandTable)[16].Arg = 2;
    (*CommandTable)[17].Name = "mov";    (*CommandTable)[17].Arg = 3;
    (*CommandTable)[18].Name = "in";     (*CommandTable)[18].Arg = 1;
    (*CommandTable)[19].Name = "sqrt";   (*CommandTable)[19].Arg = 1;
    (*CommandTable)[20].Name = "push";   (*CommandTable)[20].Arg = 2;

    return OK;
}
//============================================================================
int add_label (int address) {
	
	
	
	return OK;
}
//============================================================================
int disassembly (FILE* BinFile, FILE* Asm) {
	
	Command* CmdTable = NULL;
	
	CommandTableCreator(&CmdTable);
	
    if (CmdTable == NULL)
        return ERR_MEM;

    if (BinFile == NULL || Asm == NULL)
        return READ_FILE_ERR;

    double Size = 0;

    if (fread(&Size, sizeof(double), 1, BinFile) == 0)
        return INV_INPUT_FILE;

    int max_counter = (int) Size;

    double Cmd = -1;
    
    double Arg = 0;
    
    double Arg2 = 0;
    
    int i = 0;

    while (i < max_counter) {

        Cmd = -1;
        Arg = 0;
        Arg2 = 0;

        if (fread(&Cmd, sizeof(double), 1, BinFile) == 0)
            return ADDRESS_ERR;

        i++;

        if (Cmd == -1)
            return ADDRESS_ERR;

        switch (CmdTable[(int) Cmd].Arg) {

            case 1:

                fprintf(Asm, "%s\n", CmdTable[(int) Cmd].Name);

                break;

            case 2:

                if (fread(&Arg, sizeof(double), 1, BinFile) == 0)
                    return ADDRESS_ERR;

                i++;

                if (Cmd == PUSH || Cmd == POP)
                    fprintf(Asm, "%s reg%d\n", CmdTable[(int) Cmd].Name, (int) Arg);

                else

                    if (Cmd >= 0 && Cmd <= NUM_OF_COMMANDS - 1)
                        fprintf(Asm, "%s %d\n", CmdTable[(int) Cmd].Name, (int) Arg);

                break;

            case 3:

                if (fread(&Arg, sizeof(double), 1, BinFile) == 0)
                    return ADDRESS_ERR;

                if (fread(&Arg2, sizeof(double), 1, BinFile) == 0)
                    return ADDRESS_ERR;

                i += 2;

                fprintf(Asm, "%s reg%d %d\n", CmdTable[(int) Cmd].Name, (int) Arg, (int) Arg2);

                break;

            default:

                return UNKNOWN_CMD;

        }
    }
	
	free(CmdTable);
	
    return OK;
}
