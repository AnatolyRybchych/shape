#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include "glutil.h"
#include "bezier.h"

typedef struct Shape Shape;

void shape_init(Shape *shape, float from_x, float from_y);
void shape_free(Shape *shape);

//returns true if target is inside of shape
bool shape_get_nearest_to(Shape *shape, const float target[2], float result[2]);

void shape_bezier(Shape *shape, const Bezier *bezier);

struct Shape{
    float curve_start[2];
    size_t curves_cnt;
    Bezier *curves;
};

#endif //SHAPE_H_
