#include "assembler.h"

//=================================================================
Command* CommandTableCreator () {

    Command* CommandTable = (Command*) calloc (NUM_OF_COMMANDS, sizeof(Command));

    if (CommandTable == NULL)
        return NULL;

    for (int i = 0; i < NUM_OF_COMMANDS; i++) {
		
        CommandTable[i].Name = (char*) calloc (MAX_COMMAND_LENGTH, sizeof(char));
        
        if (CommandTable[i].Name == NULL)
            return NULL;
    }

    CommandTable[0].Name = "push";    CommandTable[0].Arg = 2;
    CommandTable[1].Name = "pop";     CommandTable[1].Arg = 2;
    CommandTable[2].Name = "add";     CommandTable[2].Arg = 1;
    CommandTable[3].Name = "sub";     CommandTable[3].Arg = 1;
    CommandTable[4].Name = "mul";     CommandTable[4].Arg = 1;
    CommandTable[5].Name = "div";     CommandTable[5].Arg = 1;
    CommandTable[6].Name = "ret";     CommandTable[6].Arg = 1;
    CommandTable[7].Name = "out";     CommandTable[7].Arg = 1;
    CommandTable[8].Name = "end";     CommandTable[8].Arg = 1;
    CommandTable[9].Name = "jae";     CommandTable[9].Arg = 2;
    CommandTable[10].Name = "jb";     CommandTable[10].Arg = 2;
    CommandTable[11].Name = "jbe";    CommandTable[11].Arg = 2;
    CommandTable[12].Name = "je";     CommandTable[12].Arg = 2;
    CommandTable[13].Name = "jne";    CommandTable[13].Arg = 2;
    CommandTable[14].Name = "jmp";    CommandTable[14].Arg = 2;
    CommandTable[15].Name = "ja";     CommandTable[15].Arg = 2;
    CommandTable[16].Name = "call";   CommandTable[16].Arg = 2;
    CommandTable[17].Name = "mov";    CommandTable[17].Arg = 3;
    CommandTable[18].Name = "in";     CommandTable[18].Arg = 1;
    CommandTable[19].Name = "sqrt";   CommandTable[19].Arg = 1;
    CommandTable[20].Name = "push";   CommandTable[20].Arg = 2;

    return CommandTable;
}
//=================================================================
Label* LabelTableCreator () {

    Label* LabelTable = (Label*) calloc (MAX_NUM_OF_LABLES, sizeof(Label));
    if (LabelTable == NULL)
        return NULL;

    for (int i = 0; i < MAX_NUM_OF_LABLES; i++)
        LabelTable[i] = -1;

    return LabelTable;
}
//=================================================================
int Assemble (FILE* Source, FILE* Asm, Command* CommandTable, Label* LabelTable) {

    long int length_of_file = 0;
    
    fseek(Source, 0, SEEK_END);
	
	length_of_file = ftell(Source); 
 
	fseek (Source, 0, SEEK_SET);  

    char* buffer = (char*) calloc (length_of_file + 1, sizeof(*buffer));

    if (buffer == NULL)
        return ERR_MEM;

    fread(buffer, sizeof(*buffer), length_of_file, Source);

    long int num_of_lines = count_lines(buffer, length_of_file);

    char** text = (char**) calloc (num_of_lines + 1, sizeof(*text));

    if (text == NULL)
        return ERR_MEM;

    ASSERT_ACCESS(divide_into_lines(buffer, length_of_file, text) != ACCSS_ERR);
//---------------------------------------------------------------------------------

    int adress = 0;

    char* line = (char*) calloc (MAX_COMMAND_LENGTH, sizeof(char));

    ASSERT_MEM(line != NULL);

    char* cmd = (char*) calloc (MAX_COMMAND_LENGTH, sizeof(char));

    ASSERT_MEM(cmd != NULL);
//first pass
    for (int LineNum = 0; LineNum < num_of_lines; LineNum++) {

        ASSERT_ACCESS(LineNum >= 0 && LineNum < num_of_lines);
        ASSERT_SYNTAX(strlen(text[LineNum]) <= (unsigned int) MAX_COMMAND_LENGTH);

        strcpy(line, text[LineNum]);

        if (check_empty(line) == OK)
            continue;

        //label
        if (line[0] == ':') {

            int label = -1;

            sscanf(line, ":%d", &label);

            ASSERT_ARG(label >= 0 && label <= MAX_NUM_OF_LABLES - 1);
            ASSERT_LABEL(LabelTable[label] == -1);

            LabelTable[label] = adress;
        }
        //non-label
        else {

            sscanf(line, "%s", cmd);

            line = DeleteWord (&line);

            int CurCmd = 0;
            int match = NOPE;

            for (CurCmd = 0; CurCmd < NUM_OF_COMMANDS; CurCmd++)
                if (strcmp((const char*) cmd, CommandTable[CurCmd].Name) == 0) {

                    match = OK;

                    if (CurCmd == PUSH) {

                        int reg = -1;
                        double value = 0;

                        if (sscanf(line, "%lg", &value) != 0)
                            break;

                        sscanf(line, "reg%d", &reg);

                        ASSERT_ARG((reg >= 0) && (reg <= NUM_OF_RIGESTERS - 1));

                        break;
                    }

                    if (CurCmd == POP) {
                        int reg = -1;

                        sscanf(line, "reg%d", &reg);

                        ASSERT_ARG((reg >= 0) && (reg <= NUM_OF_RIGESTERS - 1));

                        break;
                    }

                    if (((CurCmd > POP) && (CurCmd < JAE)) || (CurCmd == IN) || (CurCmd == SQRT))
                        ASSERT_ARG(check_empty(line) == OK);

                    if (CurCmd >= JAE && CurCmd < MOV) {

                        int label = -1;
                        sscanf(line, "%d", &label);

                        ASSERT_ARG((label >= 0) && (label <= MAX_NUM_OF_LABLES - 1));

                        break;
                    }

                    if (CurCmd == MOV) {

                        int reg = -1;
                        double num = 0;

                        sscanf(line, "reg%d", &reg);

                        ASSERT_ARG(reg >= 0 && reg <= NUM_OF_RIGESTERS - 1);

                        line = DeleteWord(&line);

                        ASSERT_SYNTAX(sscanf(line, "%lg", &num) != -1);

                    }

                    break;
                }

                ASSERT_SYNTAX(match == OK);
                adress = adress + CommandTable[CurCmd].Arg;
        }

        for (int i = 0; i < MAX_COMMAND_LENGTH; i++) {
            line[i] = 0;
            cmd[i] = 0;
        }
    }
//Second
    double adress1 = (double) adress;
    
    fwrite(&adress1, sizeof(double), 1, Asm);

    for (int LineNum = 0; LineNum < num_of_lines; LineNum++) {

        if (check_empty(text[LineNum]) == OK)
            continue;

        strcpy(line, text[LineNum]);

        if (line[0] != ':') {

            sscanf(line, "%s", cmd);

            line = DeleteWord(&line);

            int CurCmd = 0;

            for (CurCmd = 0; CurCmd < NUM_OF_COMMANDS; CurCmd++)
                if (strcmp((const char*) cmd, CommandTable[CurCmd].Name) == 0) {

                    if (CurCmd == PUSH) {

                        int reg = -1;
                        
                        double value = 0;

                        if (sscanf(line, "%lg", &value) != 0) {

                            double CurCmd1 = (double) PUSH_DOUBLE;

                            fwrite(&CurCmd1, sizeof(double), 1, Asm);
                            
                            fwrite(&value, sizeof(double), 1, Asm);
                            
                            continue;
                        }

                        sscanf(line, "reg%d", &reg);

                        if ((reg >= 0) && (reg <= NUM_OF_RIGESTERS - 1)) {

                            double CurCmd1 = (double) CurCmd;
                            fwrite(&CurCmd1, sizeof(double), 1, Asm);

                            double reg1 = (double) reg;
                            fwrite(&reg1, sizeof(double), 1, Asm);

                            continue;
                        }
                    }

                    if (CurCmd == POP) {

                        int reg = -1;
                        sscanf(line, "reg%d", &reg);

                        if ((reg >= 0) && (reg <= NUM_OF_RIGESTERS - 1)) {

                            double CurCmd1 = (double) CurCmd;
                            fwrite(&CurCmd1, sizeof(double), 1, Asm);

                            double reg1 = (double) reg;
                            fwrite(&reg1, sizeof(double), 1, Asm);

                            continue;
                        }
                    }

                    if (((CurCmd > POP) && (CurCmd < JAE)) || (CurCmd == IN) || (CurCmd == SQRT)) {

                        double CurCmd1 = (double) CurCmd;
                        fwrite(&CurCmd1, sizeof(double), 1, Asm);

                        continue;
                    }

                    if (CurCmd >= JAE && CurCmd < MOV) {

                        int label = -1;

                        sscanf(line, "%d", &label);

                        ASSERT_ARG((label >= 0) && (label <= MAX_NUM_OF_LABLES - 1));
                        ASSERT_LABEL2(LabelTable[label] != -1);

                        double CurCmd1 = (double) CurCmd;
                        fwrite(&CurCmd1, sizeof(double), 1, Asm);

                        double LT1 = (double) LabelTable[label];
                        fwrite(&LT1, sizeof(double), 1, Asm);

                        break;
                    }

                    if (CurCmd == MOV) {
                        int reg = -1;
                        double num = 0;

                        sscanf(line, "reg%d", &reg);

                        line = DeleteWord(&line);

                        sscanf(line, "%lg", &num);

                        double CurCmd1 = (double) CurCmd;
                        fwrite(&CurCmd1, sizeof(double), 1, Asm);

                        double reg1 = (double) reg;
                        fwrite(&reg1, sizeof(double), 1, Asm);
                        fwrite(&num, sizeof(double), 1, Asm);

                    }

                    break;
                }
        }

        for (int i = 0; i < MAX_COMMAND_LENGTH; i++) {

            line[i] = 0;
            cmd[i] = 0;

        }
    }
	
	free(line);
	line = NULL;
	
	free(cmd);
	cmd = NULL;
	
	free(buffer);
	buffer = NULL;
	
	free(text);
	text = NULL;
	
    return OK;
}
//=================================================================
//=================================================================
int divide_into_lines (char* buf, int length, char** text) {

    int line = 0;
    text[0] = buf;

    for (int i = 0; i < length; i++) {
		
        if ((i < 0) && (i >= length))
            return ACCSS_ERR;
            
        if (buf[i] == '\n') {
			
            line++;
            
            buf[i] = 0;
            
            if  (i + 1 < length) {
                text[line] = &buf[i + 1];
            }
        }
    }
    return OK;
}
//=================================================================
int count_lines (const char* buf, int length) {

    int am_of_lines = 0;

    for (int i = 0; i < length; i++) {
        if (buf[i] == '\n')
            am_of_lines++;
    }

    return am_of_lines;

}
//=================================================================
int check_empty (char* str) {

    int res = OK;

    for (int i = 0; i < MAX_COMMAND_LENGTH; i++)
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z'))
            res = NOPE;

    return res;
}
//=================================================================
char* DeleteWord(char** str) {
	
    int i = 0;
    
    while ((*str)[i] == ' ' && i < MAX_COMMAND_LENGTH) i++;
    
    while ((*str)[i] != ' ' && i < MAX_COMMAND_LENGTH) {
		
        
        (*str)[i] = ' ';
        i++;
        
    }
    while ((*str)[i] == ' ' && i < MAX_COMMAND_LENGTH) i++;

    char* buf = (char*) calloc (MAX_COMMAND_LENGTH, sizeof(char));
    
    int start = i;
    
    while ((*str)[i] != 0 && i < MAX_COMMAND_LENGTH) {
		
        buf[i - start] = (*str)[i];
        
        i++;
        
    }
    
    free(*str);
    
    return buf;
}
//=================================================================
