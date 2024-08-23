
#include "register.h"

#include <stdio.h>
#include <string.h>

#include "binary.h"

// Vetor com os nomes dos registradores
static char *registerNames[] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0",   "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0",   "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8",   "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

// Obtém o nome do registrador
void getRegisterInstruction(char *lineValues, char *result) {
    int decimal = convertBinaryToDecimal(lineValues);

    if (decimal >= 0 && decimal <= 31) {
        strcpy(result, registerNames[decimal]);
    } else {
        strcpy(result, "Register not found");
    }
}

// Obtém o índice do registrador
int getRegisterIndex(Register *registers, char *registerName) {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        if (strcmp(registers[i].name, registerName) == 0) {
            return i;
        }
    }
    return -1;
}

// Calcula o valor do registrador, para add, sub e addi e atualiza o registrador
void calculateValueOnRegister(Register *registers,
                              char *registerToRegistreValue, char *firstValue,
                              char *secondValue, char *operation) {
    int index = getRegisterIndex(registers, registerToRegistreValue);
    int indexFirstValue = getRegisterIndex(registers, firstValue);
    int indexSecondValue = getRegisterIndex(registers, secondValue);

    if (strcmp(firstValue, "$zero") == 0) {
        int decimal = convertBinaryToDecimal(secondValue);
        registers[index].value = decimal;
    } else {
        if (strcmp(operation, "add") == 0) {
            registers[index].value = registers[indexFirstValue].value +
                                     registers[indexSecondValue].value;
        } else if (strcmp(operation, "sub") == 0) {
            registers[index].value = registers[indexFirstValue].value -
                                     registers[indexSecondValue].value;
        }
    }
}

// Inicializa os registradores
void initializeRegisters(Register *registers) {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        strcpy(registers[i].name, registerNames[i]);
        registers[i].value = 0;
    }
}