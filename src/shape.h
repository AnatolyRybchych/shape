#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include "glutil.h"
#include "bezier.h"

typedef struct Shape Shape;

void shape_init(Shape *shape, float from_x, float from_y);
void shape_free(Shape *shape);

void shape_get_nearest_to(const Shape *shape, const float target[2], float result[2]);

/// @brief returns opengl texture
/// @param shape 
/// @param width result texture width
/// @param height result texture height
/// @return opengl texture:
/// MAG_FILTER is LINEAR;
/// MIN_FILTER is LINEAR;
/// internal format is GL_R32F
/// each pixel of this texture contains distance to nearest point on shape contour
GLuint shape_create_contour_nearestdst_texture(const Shape *shape, size_t width, size_t height);

/// @brief returns opengl texture
/// @param shape 
/// @param width result texture width
/// @param height result texture height
/// @return opengl texture:
/// MAG_FILTER is LINEAR;
/// MIN_FILTER is LINEAR;
/// internal format is GL_RG32F
/// each pixel of this texture contains nearest point on shape contour
GLuint shape_create_contour_nearest_texture(const Shape *shape, size_t width, size_t height);

void shape_bezier(Shape *shape, const Bezier *bezier);

struct Shape{
    float curve_start[2];
    size_t curves_cnt;
    Bezier *curves;
};

#endif //SHAPE_H_
