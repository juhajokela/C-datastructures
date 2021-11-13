#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
    void** data;
    size_t length;
} Array;

Array* array_init();
size_t array_length(Array* array);
void array_push(Array* array, void* item);
void* array_get(Array* array, int index);
void* array_pop(Array* array, int index);

#endif
