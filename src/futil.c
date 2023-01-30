#include <stdio.h>
#include <stdlib.h>

#include "futil.h"

char *alloc_from_file(const char *filepath){
    FILE *file = fopen(filepath, "r");

    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *result = malloc(filesize + 1);
    fread(result, 1, filesize, file);
    result[filesize] = 0;

    return result;
}