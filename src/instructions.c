#include <stdio.h>
#include <string.h>
#include "register.h"
#include "instructions.h"
#include "binary.h"

void processInstructionAndVerifyType(char *lineValues, Register *registers) {
    char firstSixBits[7];
    strncpy(firstSixBits, lineValues, 6);
    firstSixBits[6] = '\0';

    if (strcmp(firstSixBits, "000000") == 0) {
        printf("Instruction Type: R\n");
        processRTypeInstruction(lineValues, registers);
    } else {
        printf("Instruction Type: I\n");
        processITypeInstruction(lineValues, registers);
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
    char rs[6], rt[6], rd[6];

    if (strcmp(lastSixBits, "100000") == 0) {
        extractRTypeComponents(lineValues, rs, rt, rd);
        if (strcmp(rs, "$zero") == 0) {
            char immediate[6];
            getIntervalChars(lineValues, immediate, 11, 16);
            int decimal = convertBinaryToDecimal(immediate);
            printf("Instruction: addi %s, %s, %d\n", rd, rs, decimal);
            calculateValueOnRegister(registers, rd, rs, immediate, "add");
            printf("addi %s = %d\n", rd, registers[getRegisterIndex(registers, rd)].value);
        } else {
            printf("Instruction: add %s, %s, %s\n", rd, rs, rt);
            calculateValueOnRegister(registers, rd, rs, rt, "add");
            printf("add %s = %d\n", rd, registers[getRegisterIndex(registers, rd)].value);
        }
    } else if (strcmp(lastSixBits, "100010") == 0) {
        extractRTypeComponents(lineValues, rs, rt, rd);
        printf("Instruction: sub %s, %s, %s\n", rd, rs, rt);
        calculateValueOnRegister(registers, rd, rs, rt, "sub");
        printf("sub %s = %d\n", rd, registers[getRegisterIndex(registers, rd)].value);  
    } else {
        printf("R-type instruction not found\n");
    }
}

void extractITypeComponents(char *lineValues, char *rs, char *rt, char *immediate) {
    getIntervalChars(lineValues, rs, 6, 11);
    getIntervalChars(lineValues, rt, 11, 16);
    getIntervalChars(lineValues, immediate, 16, 32);
    getRegisterInstruction(rs, rs);
    getRegisterInstruction(rt, rt);
}

void processITypeInstruction(char *lineValues, Register *registers) {
    char firstSixBits[7];
    strncpy(firstSixBits, lineValues, 6);
    firstSixBits[6] = '\0';
    char rs[6], rt[6], immediate[17];

    if (strcmp(firstSixBits, "001000") == 0) {
        extractITypeComponents(lineValues, rs, rt, immediate);
        int decimal = convertBinaryToDecimal(immediate);
        printf("Instruction: addi %s, %s, %d\n", rt, rs, decimal);
        calculateValueOnRegister(registers, rt, rs, immediate, "add");
        printf("addi %s = %d\n", rt, registers[getRegisterIndex(registers, rt)].value);
    } else if (strcmp(firstSixBits, "000100") == 0) {
        extractITypeComponents(lineValues, rs, rt, immediate);
        int decimal = convertBinaryToDecimal(immediate);
        printf("Instruction: beq %s, %s, %d\n", rs, rt, decimal);
    } else if (strcmp(firstSixBits, "100011") == 0) {
        extractITypeComponents(lineValues, rs, rt, immediate);
        int decimal = convertBinaryToDecimal(immediate);
        printf("Instruction: lw %s, %d(%s)\n", rt, decimal, rs);
    } else if (strcmp(firstSixBits, "101011") == 0) {
        extractITypeComponents(lineValues, rs, rt, immediate);
        int decimal = convertBinaryToDecimal(immediate);
        printf("Instruction: sw %s, %d(%s)\n", rt, decimal, rs);
        int valueVector = decimal / 4;
        printf("%s[%d] = %s", rs, valueVector, rt);
    } else {
        printf("I-type instruction not found\n");
    }
}
