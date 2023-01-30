#ifndef PANIC_H_
#define PANIC_H_

#include <stdio.h>
#include <stdlib.h>

#define PANIC(MESSAGE_FMT, ...)do{\
    fprintf(stderr, "PANIC in %s:%i %s\n"MESSAGE_FMT"\n\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__);\
    exit(1);\
} while(0)

#define PANIC_LTZ(EXPRESSION) if(EXPRESSION < 0)PANIC("%s < 0", __STRING(EXPRESSION))

#define PANIC_NULL(EXPRESSION) if(EXPRESSION == NULL)PANIC("%s == NULL", __STRING(EXPRESSION))

#define PANIC_FALSE(EXPRESSION) if(EXPRESSION)PANIC("%s was false", __STRING(EXPRESSION))



#endif //PANIC_H_
