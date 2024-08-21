#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "memory.h"
#include "register.h"

void processInstructionAndVerifyType(char *lineValues, Register *registers,
                                     int *memory);
void processRTypeInstruction(char *lineValues, Register *registers);
void processITypeInstruction(char *lineValues, Register *registers,
                             int *memory);

#endif