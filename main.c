#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "register.h"
#include "binary.h"
#include "instructions.h"

#define LINE_MAX_CHARS 34
 

void processFile(char *filename) {
    Register registers[32];
    initializeRegisters(registers);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[LINE_MAX_CHARS];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; 

        if (verifyIfAllValuesAreBinary(line)) {
            printf("Line: %s\n", line);
            processInstructionAndVerifyType(line, registers);
            printf("\n");
        } else {
            printf("Invalid binary line: %s\n", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <instruction_file>.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    processFile(argv[1]);
    return EXIT_SUCCESS;
}
