#include "assembler.h"

int main(int argc, char* argv[]) {

    if (argv[1] == NULL) {
		
		printf("PLEASE, INPUT FILE WITH CODE\n");
		
		return 0;
	}

    FILE* Source = fopen(argv[1], "rb");
    
    if (Source == NULL) {
		
		printf("CAN NOT OPEN SOURCE FILE\n");
		
		return INV_INPUT_FILE;
	}

    char* point = argv[1];
    
    while (*point != '.') point++;

    if 	(strcmp(point, ".asm") != 0) { 
		
        printf("INVALID INPUT FILE FORMAT\n");
        
        return INV_INPUT_FILE;
    }
    
    strcpy(point, ".bin");

    FILE* Bin = fopen(argv[1], "wb");
    
    if (Bin == NULL) {
		
		printf("CAN NOT CREATE BINARY FILE\n");
		
		return 0;
	}

    if (Assemble(Source, Bin) == OK)
        printf("SUCCESSFUL COMPILATION\n");

    fclose(Source);
    fclose(Bin);

    return 0;
}
