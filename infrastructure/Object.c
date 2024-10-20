#include "Object.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* const _toString_Object(Object* const obj);
int _eq_Object(Object* const left, Object* const right);
void _destroy_Object(Object* const obj);

char* const _toString_Object(Object* const obj) {
    char template[] = "[\"%s\" object at 0x%016" PRIxPTR "]";
    char* out = malloc(sizeof(template) + strlen(obj->__type) + lenptrstr(obj) + 1);

    if (out == NULL) {
        free(out);
        return NULL;
    }

    sprintf(out, template, obj->__type, (uintptr_t) obj);
    return out;
}

int _eq_Object(Object* const left, Object* const right) {
    if (left == right) {
        return 1;
    }
    
    return 0;
}

void _destroy_Object(Object* const obj) {

}

void new_Object(Object* const obj) {
    obj->__toString = _toString_Object;
    obj->__eq = _eq_Object;
    obj->__destroy = _destroy_Object;

    obj->__type = _objectType;
}

const char* _getType(Object* const obj) {
    return obj->__type;
}

char* const _toString(Object* const obj) {
    return obj->__toString(obj);
}

int _eq(Object* const left, Object* const right) {
    return left->__eq(left, right);
}

void _destroy(Object* const obj) {
    obj->__destroy(obj);
}