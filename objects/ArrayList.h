#ifndef _POLY_LIST_H
#define _POLY_LIST_H

#include "../infrastructure/Object.h"

typedef struct ArrayList ArrayList;

static const char _arrayListType[] = "ArrayList";

struct ArrayList {
    Object __parent;

    void** __values;
    int __length;
    int __capacity;
    int __dataSize;
};

int new_ArrayList(ArrayList* const list, unsigned int dataSize);
int addElement_ArrayList(ArrayList* const list, const void* valueRef);
void* getElement_ArrayList(const ArrayList* const list, unsigned int index);
int setElement_ArrayList(ArrayList* const list, unsigned int index, void* valueRef);
int extend_ArrayList(ArrayList* const target, const ArrayList* const source);

int getLength_ArrayList(const ArrayList* const list);
int getCapacity_ArrayList(const ArrayList* const list);

void _destroy_ArrayList(ArrayList* const list);

#endif