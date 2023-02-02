#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <memory.h>

#include "shape.h"
#include "panic.h"
#include "vec.h"


void shape_init(Shape *shape, float from_x, float from_y){
    PANIC_NULL(shape);

    memset(shape, 0, sizeof(*shape));
    *shape = (Shape){
        .curve_start = {from_x, from_y},
        .curves_cnt = 0,
        .curves = NULL
    };
}

void shape_free(Shape *shape){
    PANIC_NULL(shape);
    
    if(shape->curves){
        free(shape->curves);
    }

    memset(shape, 0, sizeof(*shape));
}

//currently is not optimized and is not enugh accurate 
void shape_get_nearest_to(const Shape *shape, const float target[2], float result[2]){
    //50 per curve, 
    //TODO: maybe tyhere is a way to do it in constant time
    //or it`s should be possible to avoid doing that mutch loops
    #define GET_NEAREST_ON_BEZIER_STEP 0.02
    PANIC_NULL(shape);
    PANIC_NULL(target);
    PANIC_NULL(result);

    result[0] = shape->curve_start[0];
    result[1] = shape->curve_start[1];
    float min_sqr_dst =  vec2_sqrdst(target, shape->curve_start);

    const float (*from)[2] = &shape->curve_start;
    Bezier *curr = shape->curves;
    Bezier *end = curr + shape->curves_cnt;

    while (curr != end){
        for(float progress = 0.0; progress <= 1.0; progress += GET_NEAREST_ON_BEZIER_STEP){
            float p[2];
            bezier_point(p, *from, curr, progress);

            float sqr_dst = vec2_sqrdst(p, target);
            if(sqr_dst < min_sqr_dst){
                min_sqr_dst = sqr_dst;
                result[0] = p[0];
                result[1] = p[1];
            }
        }

        from = (const float(*)[2])&curr->to;
        curr++;
    }

    if(shape->curves_cnt){
        const float (*p1)[2] = &shape->curve_start;
        float (*p2)[2] = &shape->curves[shape->curves_cnt - 1].to;

        float p1p2[2];
        float p1target[2];
        vec2_sub(p1p2, *p2, *p1);
        vec2_sub(p1target, target, *p1);

        float p1p2_sqrdst = vec2_sqrdst(*p1, *p2);
        float dot = p1p2[0] * p1target[0] + p1p2[1] * p1target[1];

        float normal_dst = dot / p1p2_sqrdst;

        if(normal_dst > 0 && normal_dst < 0){
            float nearest[2];
            vec2_add(nearest, *p1, p1p2);
            vec2_eq_scale(nearest, normal_dst); 

            float sqrdst = vec2_sqrdst(nearest, target);
            if(sqrdst < min_sqr_dst){
                min_sqr_dst = sqrdst;
                result[0] = nearest[0];
                result[1] = nearest[1];
            }
        }
    }
}

GLuint shape_create_contour_nearestdst_texture(const Shape *shape, size_t width, size_t height){
    PANIC_NULL(shape);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    float *pixels = malloc(sizeof(float) * width * height); 
    for (size_t x = 0; x < width; x++){
        for (size_t y = 0; y < height; y++){
            float rel[2] = {
                x / (float)width * 2.0 - 1.0, 
                1.0 - y / (float)height * 2.0, 
            };

            float nearest[2];
            shape_get_nearest_to(shape, rel, nearest);
            pixels[y * width + x] = vec2_dst(nearest, rel);
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, pixels);
    
    free(pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    return tex;
}


void shape_bezier(Shape *shape, const Bezier *bezier){
    PANIC_NULL(shape);
    PANIC_NULL(bezier);

    shape->curves_cnt += 1;
    shape->curves = realloc(shape->curves, shape->curves_cnt * sizeof(Bezier));
    if(shape->curves == NULL){
        PANIC("out of memory");
    }

    shape->curves[shape->curves_cnt - 1] = *bezier;
}
