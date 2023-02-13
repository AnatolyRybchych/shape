#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define SHAPE_MAGIC (char[8]){'S', 'H', 'A', 'P', 'E', ' ', '\n', '\0'}

typedef struct ShapeHdr ShapeHdr;
typedef uint32_t ShapeErr;
enum ShapeErr{
    SHAPEE_SUCCESS,
    SHAPEE_MAGIC,
    SHAPEE_STREAM,
    SHAPEE_OUT_OF_MEMORY,
    SHAPEE_SIZE,
    SHAPEE_NULL,
};

ShapeErr shape_read_hdr(ShapeHdr *hdr, FILE *stream);

struct ShapeHdr{
    char magic[8];
    uint32_t width;
    uint32_t height;
};

#endif //SHAPE_H_
