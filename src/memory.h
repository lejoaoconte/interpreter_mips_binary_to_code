#ifndef MEMORY_H
#define MEMORY_H

#include "register.h"

// Tamanho da memória
#define MEMORY_SIZE 1024
// Quantidade de sinais de controle
#define CONTROL_SIGNAL_COUNT 8

// Sinais de controle
typedef enum {
    REG_DST,
    BRANCH,
    MEM_READ,
    MEM_TO_REG,
    ALU_OP,
    MEM_WRITE,
    ALU_SRC,
    REG_WRITE
} ControlSignalType;

// Estrutura de sinais de controle
typedef struct {
    char *name;
    char *value;
} ControlSignals;

void initializeMemory(int *memory);
void verifyControlSignalsInProcessor(char *lineValues);
void initializeControlSignals(ControlSignals *controlSignals);

void setRTypeControlSignals(ControlSignals *controlSignals);
void setLWTypeControlSignals(ControlSignals *controlSignals);
void setSWTypeControlSignals(ControlSignals *controlSignals);
void setBEQTypeControlSignals(ControlSignals *controlSignals);

void printControlSignals(ControlSignals *controlSignals);

void verifyBeqPCValue(Register *registers, char *rs, char *rt, char *immediate);

#endif