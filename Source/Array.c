#include "Array.h"

struct array_s {
    void **contents;
    size_t max_length;
    size_t count;
};

Array *array_init() {
    return calloc(1, sizeof(Array));
}

void array_dealloc(Array *array) {
    if (array != NULL) {
        free(array);
    }
}

size_t array_count(Array *array) {
    return 0;
}
