#include "ArrayList.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>


int new_ArrayList(ArrayList* const list, unsigned int dataSize) {
    new_Object((Object*)list);
    ((Object*)list)->__destroy = (destroy_fptr)_destroy_ArrayList;
    ((Object*)list)->__type = _arrayListType;

    list->__dataSize = dataSize;
    list->__capacity = 1;
    list->__length = 0;
    list->__values = malloc(list->__capacity * sizeof(void*));
    if (list->__values == NULL) {
        return -1;
    }

    return 0;
}

int addElement_ArrayList(ArrayList* const list, const void* const valueRef) {
    if (list == NULL || list->__capacity == 0) {
        return -1;
    }
    
    if (list->__capacity == list->__length) {
        list->__capacity *= 2;
        void* new = realloc(list->__values, list->__capacity * sizeof(void*));
        if (new == NULL) {
            return -1;
        }

        list->__values = new;
    }

    list->__values[list->__length] = malloc(list->__dataSize);
    if (list->__values[list->__length] == NULL) {
        return -1;
    }

    memcpy(list->__values[list->__length], valueRef, list->__dataSize);
    (list->__length)++;
    return 0;
}

void* getElement_ArrayList(const ArrayList* const list, unsigned int index) {
    if (list == NULL || list->__capacity == 0 || index >= list->__length) {
        return NULL;
    }

    return list->__values[index];
}

int setElement_ArrayList(ArrayList* const list, unsigned int index, void* valueRef) {
    if (list == NULL || list->__capacity == 0 || (index >= list->__length && list->__length > 0)) {
        return -1;
    }

    memcpy(list->__values[list->__length], valueRef, list->__dataSize);
    return 0;
}

int extend_ArrayList(ArrayList* const target, const ArrayList* const source) {
    if (target == NULL || target->__capacity == 0 || source == NULL || target->__capacity == 0 || source->__dataSize != target->__dataSize) {
        return -1;
    } 

    while (target->__capacity < (target->__length + source->__length)) {
        target->__capacity *= 2;
    }

    void* new = realloc(target->__values, target->__capacity * sizeof(void*));
    if (new == NULL) {
        return -1;
    }

    target->__values = new;
    for (
        int i = target->__length;
        i < target->__length + source->__length;
        i++
    ) {
        target->__values[i] = malloc(target->__dataSize);
        if (target->__values[i] == NULL) {
            return -1;
        }

        memcpy(target->__values[i], source->__values[i - target->__length], source->__dataSize);
    }

    target->__length += source->__length;
    return 0;
}

int getLength_ArrayList(const ArrayList* const list) {
    return list->__length;
}

int getCapacity_ArrayList(const ArrayList* const list) {
    return list->__capacity;
}

void _destroy_ArrayList(ArrayList* const list) {
    assert(list != NULL);
    assert(list->__capacity != 0);
    for (int i = 0; i < list->__length; i++) {
        free(list->__values[i]);
    }

    free(list->__values);
    list->__capacity = 0;
    list->__length = 0;
    list->__dataSize = 0;
    list->__values = NULL;
}
