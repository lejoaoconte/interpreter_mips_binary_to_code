
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
    ControlSignals controlSignals[CONTROL_SIGNAL_COUNT];
    initializeControlSignals(controlSignals);
    char opcode[7];
    getIntervalChars(lineValues, opcode, 0, 6);
    opcode[6] = '\0';

    if (strcmp(opcode, "000000") == 0 || strcmp(opcode, "001000") == 0) {
        setRTypeControlSignals(controlSignals);
    } else if (strcmp(opcode, "100011") == 0) {
        setLWTypeControlSignals(controlSignals);
    } else if (strcmp(opcode, "101011") == 0) {
        setSWTypeControlSignals(controlSignals);
    } else if (strcmp(opcode, "000100") == 0) {
        setBEQTypeControlSignals(controlSignals);
    } else {
        printf("Opcode Instructions Not Found\n");
    }

    printControlSignals(controlSignals);
}

void printControlSignals(ControlSignals *controlSignals) {
    for (int i = 0; i < CONTROL_SIGNAL_COUNT; i++) {
        printf("%s: %s", controlSignals[i].name, controlSignals[i].value);
        if (i < CONTROL_SIGNAL_COUNT - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void setRTypeControlSignals(ControlSignals *controlSignals) {
    controlSignals[REG_DST].value = "1";
    controlSignals[REG_WRITE].value = "1";
    controlSignals[ALU_OP].value = "10";
}

void setLWTypeControlSignals(ControlSignals *controlSignals) {
    controlSignals[ALU_SRC].value = "1";
    controlSignals[MEM_TO_REG].value = "1";
    controlSignals[REG_WRITE].value = "1";
    controlSignals[MEM_READ].value = "1";
}

void setSWTypeControlSignals(ControlSignals *controlSignals) {
    controlSignals[ALU_SRC].value = "1";
    controlSignals[MEM_WRITE].value = "1";
}

void setBEQTypeControlSignals(ControlSignals *controlSignals) {
    controlSignals[BRANCH].value = "1";
    controlSignals[ALU_OP].value = "01";
}

void initializeControlSignals(ControlSignals *controlSignals) {
    controlSignals[REG_DST].name = "RegDst";
    controlSignals[BRANCH].name = "Branch";
    controlSignals[MEM_READ].name = "MemRead";
    controlSignals[MEM_TO_REG].name = "MemtoReg";
    controlSignals[ALU_OP].name = "ALUOp";
    controlSignals[MEM_WRITE].name = "MemWrite";
    controlSignals[ALU_SRC].name = "ALUSrc";
    controlSignals[REG_WRITE].name = "RegWrite";

    for (int i = 0; i < CONTROL_SIGNAL_COUNT; i++) {
        controlSignals[i].value = "0";
    }
}

void verifyBeqPCValue(Register *registers, char *rs, char *rt,
                      char *immediate) {
    int indexRs = getRegisterIndex(registers, rs);
    int indexRt = getRegisterIndex(registers, rt);
    int decimalImmediate = convertBinaryToDecimal(immediate);
    int offset = decimalImmediate << 2;

    if (registers[indexRs].value == registers[indexRt].value) {
        printf("PC = PC + 4 + %d\n", offset);
    } else {
        printf("PC = PC + 4\n");
    }
}