#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "memory.h"
#include "register.h"

void processInstructionAndVerifyType(char *lineValues, Register *registers,
                                     int *memory);
void processRTypeInstruction(char *lineValues, Register *registers);
void processITypeInstruction(char *lineValues, Register *registers,
                             int *memory);

void handleAddInstruction(char *lineValues, Register *registers);
void handleSubInstruction(char *lineValues, Register *registers);
void handleLWInstruction(char *lineValues, Register *registers, int *memory);
void handleSWInstruction(char *lineValues, Register *registers, int *memory);
void handleAddiInstruction(char *lineValues, Register *registers);
void handleBeqInstruction(char *lineValues, Register *registers);

#endif