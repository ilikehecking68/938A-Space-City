#ifndef UTIL_H
#define UTIL_H

#include "easy_types.h"
#include <stdlib.h>
#include <stdio.h>

typedef ui64 memory_bytes;

extern unkown_size_pointer safe_malloc(memory_bytes bytes);
extern void safe_realloc(unkown_size_pointer* memory, memory_bytes new_bytes);
extern void safe_free(unkown_size_pointer memory);

#define invert(x, max)(max - x)

#define num_check_reset(var_name, limit_val, reset_val, not_triggered_val) \
    if (var_name <= limit_val){ \
        var_name = not_triggered_val; \
    } \
    if (var_name > limit_val){ \
        var_name = reset_val; \
    }

#define alloc_NULL_check(val) \
    if (val == NULL){ \
        perror("heap function returned a NULL pointer"); \
        exit(1); \
    }

#define free_NULL_check(val) \
    if (val == NULL){ \
        perror("heap free function tried to free a NULL pointer"); \
        exit(1); \
    }

#define xor_swap(a, b) \
    (a) = (b) ^ (a); \
    (b) = (a) ^ (b); \
    (a) = (b) ^ (a);

#define swap(a, b){ \
        typeof(a) swap = a; \
        a = b; \
        b = swap; \
    }

#define I64LIZE(a)((i64)(a))
#define UI64LIZE(a)((ui64)(a))
#define I32LIZE(a)((i32)(a))
#define UI32LIZE(a)((ui32)(a))
#define MIN(a, b)(a < b ? a : b)
#define MAX(a, b)(a > b ? a : b)
#define RANGE(a, l, h)(MAX(MIN(a, h), l))
#define LIMITED_ADDITION(x, offset, limit)(MAX(x + offset, limit))
#define LIMITED_SUBTRACTION(x, offset, limit)(MAX(x - offset, limit))
#define LIMITED_MULTIPLICATION(x, offset, limit)(MAX(x * offset, limit))
#define LIMITED_DIVISION(x, offset, limit)(MAX(x / offset, limit))


#endif