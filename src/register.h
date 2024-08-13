void getRegisterInstruction(char *lineValues, char *result);
typedef struct {
    char name[6];
    int value;
} Register;
int getRegisterIndex(Register *registers, char *registerName);
void calculateValueOnRegister(Register *registers, char *registerToRegistreValue, char *firstValue, char *secondValue, char *operation);
void initializeRegisters(Register *registers);