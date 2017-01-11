#include "Array.h"
#include <stdio.h>

struct array_s {
    void **contents;
    size_t max_length;
    size_t count;
};

void array_resize(Array *array, size_t desired_size);

Array *array_init() {
    Array *array = calloc(1, sizeof(Array));
    array_resize(array, 10);
    return array;
}

void array_dealloc(Array *array, void (^dealloc_block)(void *, size_t)) {
    if (dealloc_block != NULL) {
        for (size_t i = 0; i < array_count(array); i += 1) {
            void *obj = array_get(array, i);
            dealloc_block(obj, i);
        }
    }
    if (array != NULL) {
        free(array);
    }
}

size_t array_count(Array *array) {
    return array->count;
}

void array_append(Array *array, void *obj) {
    if (array->count >= array->max_length) {
        array_resize(array, 2 * array->max_length);
    }

    array->contents[array->count] = obj;
    array->count += 1;
}

void *array_get(Array *array, size_t index) {
    if (index >= array_count(array)) {
        return NULL;
    }

    return array->contents[index];
}

#pragma mark - Private

void array_resize(Array *array, size_t desired_size) {
    if (desired_size == 0) {
        fprintf(stderr, "Error: Attempting to resize array to 0\n");
        exit(-1);
    }
    array->contents = realloc(array->contents, sizeof(void *) * desired_size);
    array->max_length = desired_size;
}
