#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include "glutil.h"

typedef struct ShapeFragment ShapeFragment;
typedef struct Shape Shape;

void shape_init(Shape *shape, uint32_t width, uint32_t height);
void shape_free(Shape *shape);

void shape_draw_circle(Shape *shape, float cx, float cy, float r);

GLuint shape_create_texture(Shape *shape);

struct ShapeFragment{
    float x;
    float y;
};

struct Shape{
    uint32_t width;
    uint32_t height;

    ShapeFragment *fragments;
};

#endif //SHAPE_H_
