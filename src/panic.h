#ifndef PANIC_H_
#define PANIC_H_

#include <stdio.h>
#include <stdlib.h>

#define PANIC_LTZ(EXPRESSION) do{\
    if(EXPRESSION < 0){\
        fprintf(stderr, "PANIC in %s:%i %s\n%s < 0\n\n", __FILE__, __LINE__, __func__, __STRING(EXPRESSION));\
    }\
} while(0)

#define PANIC_NULL(EXPRESSION) do{\
    if(EXPRESSION == NULL){\
        fprintf(stderr, "PANIC in %s:%i %s\n%s == NULL\n\n", __FILE__, __LINE__, __func__, __STRING(EXPRESSION));\
    }\
} while(0)

#endif //PANIC_H_
