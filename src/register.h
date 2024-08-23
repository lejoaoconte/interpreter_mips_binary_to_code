#ifndef REGISTER_H
#define REGISTER_H

#define REGISTER_COUNT 32

// Estrutura de registrador
typedef struct {
    char name[6];
    int value;
} Register;

void getRegisterInstruction(char *lineValues, char *result);
int getRegisterIndex(Register *registers, char *registerName);
void calculateValueOnRegister(Register *registers,
                              char *registerToRegistreValue, char *firstValue,
                              char *secondValue, char *operation);
void initializeRegisters(Register *registers);

#endif