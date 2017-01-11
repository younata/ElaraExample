#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>

struct array_s;

typedef struct array_s Array;

Array *array_init();
void array_dealloc(Array *array, void (^dealloc_block)(void *, size_t));

size_t array_count(Array *array);

void array_append(Array *array, void *obj);
void *array_get(Array *array, size_t index);

#endif /* __ARRAY_H__ */
