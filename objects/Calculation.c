#include "Calculation.h"
#include "../utils/String.h"
#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

CalculationResult __iterationWrapper(
    const void* const values, 
    int valuesLength, 
    CalculationResult (*operation)(double, double)
);

CalculationResult __addition(double l, double r);
CalculationResult __multiplication(double l, double r);
CalculationResult __subtraction(double l, double r);

const char* _toString_Calculation(Calculation* const calc) {
    switch(calc->operation) {
        case CALC_ADD:
            return sprintf_automalloc("[\"%s\" object, Addition of %d parameters, 0x%016" PRIxPTR "]", 
                                      Object_getType(calc), calc->valuesLength, calc);
        case CALC_SUBTRACT:
            return sprintf_automalloc("[\"%s\" object, Subtraction of %d parameters, 0x%016" PRIxPTR "]", 
                                      Object_getType(calc), calc->valuesLength, calc);
        case CALC_MULTIPLY:
            return sprintf_automalloc("[\"%s\" object, Multiplication of %d parameters, 0x%016" PRIxPTR "]",
                                      Object_getType(calc), calc->valuesLength, calc);
        default:
            return Object_toString((Object*)calc);
    }
}

int _eq_Calculation(Calculation* const left, Calculation* const right) {
    if (left == right) {
        return 1;
    } else if (strcmp(Object_getType(left), Object_getType(right)) != 0) {
        return 0;
    } else if (left->operation != right->operation) {
        return 0;
    } else if (left->valuesLength != right->valuesLength) {
        return 0;
    } else if (left->values == right->values) {
        return 1;
    }

    for (int i = 0; i < left->valuesLength; i++) {
        if (((double*)(left->values))[i] != ((double*)(right->values))[i]) {
            return 0;
        }
    }

    return 1;
}

void _destroy_Calculation(Calculation* const calc) {
    free(calc->values);
}

void new_Calculation(Calculation* const calc, double* const values, int valuesLength, CalcOperation operation) {
    new_Object((Object*)calc);
    
    ((Object*)calc)->__toString = (toString_fptr)_toString_Calculation;
    ((Object*)calc)->__eq = (eq_fptr)_eq_Calculation;
    ((Object*)calc)->__destroy = (destroy_fptr)_destroy_Calculation;

    ((Object*)calc)->__type = _calculationType;

    calc->operation = operation;
    calc->valuesLength = valuesLength;
    calc->values = calloc(valuesLength, sizeof(double));
    for (int i = 0; i < valuesLength; i++) {
        ((double*)(calc->values))[i] = values[valuesLength - i - 1];
    }
}

CalculationResult execute_Calculation(const Calculation* const calc) {
    switch(calc->operation) {
        case CALC_ADD:
            return __iterationWrapper(calc->values, calc->valuesLength, __addition);
        case CALC_SUBTRACT:
            return __iterationWrapper(calc->values, calc->valuesLength, __subtraction);
        case CALC_MULTIPLY:
            return __iterationWrapper(calc->values, calc->valuesLength, __multiplication);
        default:
            return (CalculationResult){ 1, 0 };
    }
}

CalculationResult __addition(double l, double r) {
    return (CalculationResult){ 0, (l + r) };
}

CalculationResult __multiplication(double l, double r) {
    return (CalculationResult){ 0, (l * r) };
}

CalculationResult __subtraction(double l, double r) {
    return (CalculationResult){ 0, (l - r) };
}

CalculationResult
__iterationWrapper(
    const void* const values, 
    int valuesLength, 
    CalculationResult (*operation)(double, double)
    ) 
{
    const double* const castValues = (double*)values;
    CalculationResult result = { .error = 0, .result = 0 };
    if (valuesLength <= 0) {
        result.error = 1;
        return result;
    } else if (valuesLength == 1) {
        result.result = *castValues;
        return result;
    }

    result = __iterationWrapper(castValues + 1, valuesLength - 1, operation);
    if (result.error) {
        return (CalculationResult){ 1, 0 };
    }
    return operation(result.result, *castValues);
}
