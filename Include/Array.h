#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>

struct array_s;

typedef struct array_s Array;

Array *array_init();
void array_dealloc(Array *array);

size_t array_count(Array *array);

#endif /* __ARRAY_H__ */
