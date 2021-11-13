#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

Array* array_init() {
    Array* array = malloc(sizeof(Array));
    array->data = malloc(0);
    array->length = 0;
    return array;
}

size_t array_length(Array* array) {
    return array->length;
}

void array_push(Array* array, void* item) {
    size_t index = array->length;
    void** pointer = realloc(array->data, (index + 1) * sizeof(void*));
    if (pointer) {
      array->data = pointer;
      array->data[index] = item;
      ++array->length;
    } else {
      puts("array_push: failed to allocate memory.");
    }
}

int array_index(Array* array, int index) {
    if (index < 0) index = array->length + index;
    if (index < 0 ||  array->length <= index) {
        printf("array_index: index error %i [%zu]\n", index, array->length);
        return -1;
    }
    return index;
}

void* array_get(Array* array, int index) {
    index = array_index(array, index);
    if (index == -1) {
        puts("Error at array_get.");
        return NULL;
    }
    return array->data[index];
}

void* array_pop(Array* array, int index) {
    index = array_index(array, index);
    if (index == -1) {
        puts("Error at array_pop.");
        return NULL;
    }
    void* result = array->data[index];
    memcpy(
        &array->data[index],
        &array->data[index+1],
        (array->length - (index + 1)) * sizeof(void*)
    );
    --array->length;
    return result;
}


void array_free(Array* array) {
    free(array->data);
    free(array);
}
