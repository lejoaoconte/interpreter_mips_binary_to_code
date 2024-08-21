#include "binary.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int verifyIfAllValuesAreBinary(char *lineValues) {
    for (int i = 0; lineValues[i] != '\0'; i++) {
        if (lineValues[i] != '0' && lineValues[i] != '1') {
            printf("Value in line %s is not binary\n", lineValues);
            return false;
        }
    }
    return true;
}

void getLastNChars(char *str, char *result, int n) {
    int length = strlen(str);
    char *startPos = length >= n ? str + (length - n) : str;
    strncpy(result, startPos, n);
    result[n] = '\0';
}

void getIntervalChars(char *str, char *result, int start, int end) {
    int length = strlen(str);
    if (start >= length) {
        result[0] = '\0';
        return;
    }

    int copyLength = end - start;
    strncpy(result, str + start, copyLength);
    result[copyLength] = '\0';
}

int convertBinaryToDecimal(char *binary) {
    int decimal = 0;
    for (int i = 0; binary[i] != '\0'; i++) {
        decimal = (decimal << 1) | (binary[i] == '1' ? 1 : 0);
    }
    return decimal;
}
