#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "../infrastructure/Object.h"

typedef struct Calculation Calculation;
typedef struct CalculationResult CalculationResult;

static const char _calculationType[] = "Calculation";

enum CalcOperation {
    CALC_ADD = 1,
    CALC_SUBTRACT,
    CALC_MULTIPLY
} typedef CalcOperation;

struct Calculation {
    Object __parent;

    void* values;
    int valuesLength; // Might implement a vector and use it here
    CalcOperation operation;
};

struct CalculationResult {
    int error;
    double result;
};

void new_Calculation(Calculation* const calc, double* const values, int valuesLength, CalcOperation operation);
CalculationResult execute_Calculation(const Calculation* const calc);

const char* _toString_Calculation(Calculation* const calc);
int _eq_Calculation(Calculation* const left, Calculation* const right);


#endif