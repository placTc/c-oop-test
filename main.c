#include "infrastructure/Object.h"
#include "objects/Calculation.h"
#include "objects/ArrayList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    ArrayList* testVector = malloc(sizeof(ArrayList));
    new_ArrayList(testVector, sizeof(uint64_t));

    ArrayList* testVector2 = malloc(sizeof(ArrayList));
    new_ArrayList(testVector2, sizeof(uint64_t));

    for (long long int i = 0; i < 10; i++) {
        addElement_ArrayList(testVector, &i);
    }

    for (long long int i = 0; i < 10; i++) {
        addElement_ArrayList(testVector2, &i);
    }

    extend_ArrayList(testVector, testVector2);

    for (int i = 0; i < getLength_ArrayList(testVector); i++) {
        printf("%llu", *(uint64_t*)getElement_ArrayList(testVector, i));
    }

    char* tostr = Object_toString(testVector);
    printf("\n%s\n", tostr);

    free(tostr);
    Object_destroy(testVector2);
    free(testVector2);
    Object_destroy(testVector);
    free(testVector);
    return 0;
}