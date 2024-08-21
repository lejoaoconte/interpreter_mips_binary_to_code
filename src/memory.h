#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 1024

typedef struct {
    char *name;
    char *value;
} ControlSignals;

void initializeMemory(int *memory);
void verifyControlSignalsInProcessor(char *lineValues);
void initializeControlSignals(ControlSignals *controlSignals);

#endif