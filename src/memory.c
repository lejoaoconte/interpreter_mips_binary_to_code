
#include "memory.h"

#include <stdio.h>
#include <string.h>

#include "binary.h"
#include "register.h"

void initializeMemory(int *memory) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = -1;
    }
}

void verifyControlSignalsInProcessor(char *lineValues) {
    ControlSignals controlSignals[8];
    initializeControlSignals(controlSignals);
    char firstSixBits[7];
    getIntervalChars(lineValues, firstSixBits, 0, 6);
    printf("firstSixBits: %s\n", firstSixBits);

    if (strcmp(firstSixBits, "000000") == 0 ||
        strcmp(firstSixBits, "001000") == 0) {
        controlSignals[0].value = "1";
        controlSignals[1].value = "0";
        controlSignals[2].value = "0";
        controlSignals[3].value = "0";
        controlSignals[4].value = "10";
        controlSignals[5].value = "0";
        controlSignals[6].value = "0";
        controlSignals[7].value = "1";
    } else {
        if (strcmp(firstSixBits, "100011") == 0) {
            controlSignals[0].value = "0";
            controlSignals[1].value = "0";
            controlSignals[2].value = "1";
            controlSignals[3].value = "1";
            controlSignals[4].value = "00";
            controlSignals[5].value = "0";
            controlSignals[6].value = "1";
            controlSignals[7].value = "1";
        } else if (strcmp(firstSixBits, "101011") == 0) {
            controlSignals[0].value = "x";
            controlSignals[1].value = "0";
            controlSignals[2].value = "0";
            controlSignals[3].value = "x";
            controlSignals[4].value = "00";
            controlSignals[5].value = "1";
            controlSignals[6].value = "1";
            controlSignals[7].value = "0";
        } else if (strcmp(firstSixBits, "000100") == 0) {
            controlSignals[0].value = "x";
            controlSignals[1].value = "1";
            controlSignals[2].value = "0";
            controlSignals[3].value = "x";
            controlSignals[4].value = "01";
            controlSignals[5].value = "0";
            controlSignals[6].value = "0";
            controlSignals[7].value = "0";
        } else {
            printf("I-type instruction not found\n");
        }
    }

    for (int i = 0; i < 7; i++) {
        printf("%s: %s", controlSignals[i].name, controlSignals[i].value);
        if (i < 6) {
            printf(", ");
        }
    }

    printf("\n");
}

void initializeControlSignals(ControlSignals *controlSignals) {
    controlSignals[0].name = "RegDst";
    controlSignals[0].value = "0";
    controlSignals[1].name = "Branch";
    controlSignals[1].value = "0";
    controlSignals[2].name = "MemRead";
    controlSignals[2].value = "0";
    controlSignals[3].name = "MemtoReg";
    controlSignals[3].value = "0";
    controlSignals[4].name = "ALUOp";
    controlSignals[4].value = "00";
    controlSignals[5].name = "MemWrite";
    controlSignals[5].value = "0";
    controlSignals[6].name = "ALUSrc";
    controlSignals[6].value = "0";
    controlSignals[7].name = "RegWrite";
    controlSignals[7].value = "0";
}