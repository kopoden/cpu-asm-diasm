#include "disassembler.h"

int main(int argc, char* argv[]) {

    if (argv[1] == NULL) {

        printf("PLEASE, INPUT BINARY FILE\n");

        return READ_FILE_ERR;
    }

    FILE* Bin = fopen(argv[1], "rb");

    if (Bin == NULL) {

        printf("FILE READING ERROR\n");

        return READ_FILE_ERR;
    }
	
	char* point = argv[1];
    
    while (*point != '.') point++;

    if 	(strcmp(point, ".bin") != 0) { 
		
        printf("INVALID INPUT FILE FORMAT\n");
        
        return INV_INPUT_FILE;
    }
    
    strcpy(point, ".asm");
	
    FILE* Asm = fopen(argv[1], "w");
    
    if (Asm == NULL) {
		
		printf("CAN'T CREATE FILE WITH DISASSEBLIED CODE\n");
		
		return 0;
	}

    check(disassembly(Bin, Asm));

    printf("SUCCESS!\n");

    fclose(Bin);
    fclose(Asm);

    return 0;
}

