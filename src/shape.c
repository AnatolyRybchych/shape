#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <memory.h>

#include "shape.h"

ShapeErr shape_read_hdr(ShapeHdr *hdr, FILE *stream){
    if(hdr == NULL){
        return SHAPEE_NULL;
    }

    memset(hdr, 0, sizeof(*hdr));
    if(fread(hdr->magic, 1, sizeof(hdr->magic), stream)
    != sizeof(hdr->magic)){
        return SHAPEE_STREAM;
    }

    if(strncmp(hdr->magic, SHAPE_MAGIC, sizeof(SHAPE_MAGIC)) != 0){
        return SHAPEE_MAGIC;
    }

    if(fread(&hdr->width, sizeof(hdr->width), 1, stream) != 1){
        return SHAPEE_STREAM;
    }
    if(hdr->width == 0){
        return SHAPEE_SIZE;
    }

    if(fread(&hdr->height, sizeof(hdr->height), 1, stream) != 1){
        return SHAPEE_STREAM;
    }
    if(hdr->height == 0){
        return SHAPEE_SIZE;
    }

    return SHAPEE_SUCCESS;
}