
#include "instructions.h"

#include <stdio.h>
#include <string.h>

#include "binary.h"

void processInstructionAndVerifyType(char *lineValues, Register *registers,
                                     int *memory) {
    char firstSixBits[7];
    strncpy(firstSixBits, lineValues, 6);
    firstSixBits[6] = '\0';

    if (strcmp(firstSixBits, "000000") == 0) {
        printf("Instruction Type: R\n");
        processRTypeInstruction(lineValues, registers);
    } else {
        printf("Instruction Type: I\n");
        processITypeInstruction(lineValues, registers, memory);
    }
}

void extractRTypeComponents(char *lineValues, char *rs, char *rt, char *rd) {
    getIntervalChars(lineValues, rs, 6, 11);
    getIntervalChars(lineValues, rt, 11, 16);
    getIntervalChars(lineValues, rd, 16, 21);
    getRegisterInstruction(rs, rs);
    getRegisterInstruction(rt, rt);
    getRegisterInstruction(rd, rd);
}

void processRTypeInstruction(char *lineValues, Register *registers) {
    char lastSixBits[7];
    getLastNChars(lineValues, lastSixBits, 6);

    switch (convertBinaryToDecimal(lastSixBits)) {
        case 32:
            handleAddInstruction(lineValues, registers);
            break;
        case 34:
            handleSubInstruction(lineValues, registers);
            break;
        default:
            printf("R-type instruction not found\n");
    }
}

void extractITypeComponents(char *lineValues, char *rs, char *rt,
                            char *immediate) {
    getIntervalChars(lineValues, rs, 6, 11);
    getIntervalChars(lineValues, rt, 11, 16);
    getIntervalChars(lineValues, immediate, 16, 32);
    getRegisterInstruction(rs, rs);
    getRegisterInstruction(rt, rt);
}

void processITypeInstruction(char *lineValues, Register *registers,
                             int *memory) {
    char firstSixBits[7];
    strncpy(firstSixBits, lineValues, 6);
    firstSixBits[6] = '\0';

    switch (convertBinaryToDecimal(firstSixBits)) {
        case 8:
            handleAddiInstruction(lineValues, registers);
            break;
        case 4:
            handleBeqInstruction(lineValues, registers);
            break;
        case 35:
            handleLWInstruction(lineValues, registers, memory);
            break;
        case 43:
            handleSWInstruction(lineValues, registers, memory);
            break;
        default:
            printf("I-type instruction not found\n");
    }
}

void handleAddInstruction(char *lineValues, Register *registers) {
    char rs[6], rt[6], rd[6];
    extractRTypeComponents(lineValues, rs, rt, rd);
    if (strcmp(rs, "$zero") == 0) {
        char immediate[6];
        getIntervalChars(lineValues, immediate, 11, 16);
        int decimal = convertBinaryToDecimal(immediate);
        printf("Instruction: add %s, %s, %d\n", rd, rs, decimal);
        calculateValueOnRegister(registers, rd, rs, immediate, "add");
        printf("addi %s = %d\n", rd,
               registers[getRegisterIndex(registers, rd)].value);
        printf("PC = PC + 4\n");
        verifyControlSignalsInProcessor(lineValues);
    } else {
        printf("Instruction: add %s, %s, %s\n", rd, rs, rt);
        calculateValueOnRegister(registers, rd, rs, rt, "add");
        printf("add %s = %d\n", rd,
               registers[getRegisterIndex(registers, rd)].value);
        printf("PC = PC + 4\n");
        verifyControlSignalsInProcessor(lineValues);
    }
}

void handleSubInstruction(char *lineValues, Register *registers) {
    char rs[6], rt[6], rd[6];
    extractRTypeComponents(lineValues, rs, rt, rd);
    printf("Instruction: sub %s, %s, %s\n", rd, rs, rt);
    calculateValueOnRegister(registers, rd, rs, rt, "sub");
    printf("sub %s = %d\n", rd,
           registers[getRegisterIndex(registers, rd)].value);
    printf("PC = PC + 4\n");
    verifyControlSignalsInProcessor(lineValues);
}

void handleAddiInstruction(char *lineValues, Register *registers) {
    char rs[6], rt[6], immediate[17];
    extractITypeComponents(lineValues, rs, rt, immediate);
    int decimal = convertBinaryToDecimal(immediate);
    printf("Instruction: addi %s, %s, %d\n", rt, rs, decimal);
    calculateValueOnRegister(registers, rt, rs, immediate, "add");
    printf("addi %s = %d\n", rt,
           registers[getRegisterIndex(registers, rt)].value);
    printf("PC = PC + 4\n");
    verifyControlSignalsInProcessor(lineValues);
}

void handleBeqInstruction(char *lineValues, Register *registers) {
    char rs[6], rt[6], immediate[17];
    extractITypeComponents(lineValues, rs, rt, immediate);
    int decimal = convertBinaryToDecimal(immediate);
    printf("Instruction: beq %s, %s, %d\n", rs, rt, decimal);
    verifyBeqPCValue(registers, rs, rt, immediate);
    verifyControlSignalsInProcessor(lineValues);
}

void handleLWInstruction(char *lineValues, Register *registers, int *memory) {
    char rs[6], rt[6], immediate[17];
    extractITypeComponents(lineValues, rs, rt, immediate);
    int decimal = convertBinaryToDecimal(immediate);
    int address = registers[getRegisterIndex(registers, rs)].value + decimal;
    if (address >= 0 && address < MEMORY_SIZE) {
        registers[getRegisterIndex(registers, rt)].value = memory[address / 4];
        printf("Instruction: lw %s, %d(%s)\n", rt, decimal, rs);
        printf("%s = %d\n", rt,
               registers[getRegisterIndex(registers, rt)].value);
    } else {
        printf("Memory access error: address out of bounds\n");
    }
    printf("PC = PC + 4\n");
    verifyControlSignalsInProcessor(lineValues);
}

void handleSWInstruction(char *lineValues, Register *registers, int *memory) {
    char rs[6], rt[6], immediate[17];
    extractITypeComponents(lineValues, rs, rt, immediate);
    int decimal = convertBinaryToDecimal(immediate);
    int address = registers[getRegisterIndex(registers, rs)].value + decimal;
    if (address >= 0 && address < MEMORY_SIZE) {
        memory[address / 4] = registers[getRegisterIndex(registers, rt)].value;
        printf("Instruction: sw %s, %d(%s)\n", rt, decimal, rs);
        printf("Memory[%d] = %d\n", address / 4, memory[address / 4]);
    } else {
        printf("Memory access error: address out of bounds\n");
    }
    printf("PC = PC + 4\n");
    verifyControlSignalsInProcessor(lineValues);
}