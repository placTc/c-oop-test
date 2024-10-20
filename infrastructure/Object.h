#ifndef _OBJECT_H
#define _OBJECT_H

#include "../utils/Macros.h"

#define Object _Object
#define Object_vtable _ObjectVtable

#define Object_toString(obj) (_toString((Object*)(obj)))
#define Object_getType(obj) (_getType((Object*)(obj)))
#define Object_eq(objl, objr) (_eq((Object*)(objl), (Object*)(objr)))
#define Object_destroy(obj) (_destroy((Object*)(obj)))

typedef struct Object Object;
typedef struct Object_vtable Object_vtable;

typedef char* const (*toString_fptr)(Object* const);
typedef int (*eq_fptr)(Object* const, Object* const);
typedef void (*destroy_fptr)(Object* const);

static const char _objectType[] = "Object";


struct Object {
    const char* __type;
    toString_fptr __toString;
    eq_fptr __eq;
    destroy_fptr __destroy;
};

void new_Object(Object* const obj);

const char* _getType(Object* const obj);
char* const _toString(Object* const obj);
int _eq(Object* const left, Object* const right);
void _destroy(Object* const obj);

char* const _toString_Object(Object* const obj);
int _eq_Object(Object* const left, Object* const right);
void _destroy_Object(Object* const obj);

#endif