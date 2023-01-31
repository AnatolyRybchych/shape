#include <stdlib.h>
#include <memory.h>

#include "shape.h"
#include "panic.h"
#include "vec.h"

void shape_init(Shape *shape, uint32_t width, uint32_t height){
    PANIC_NULL(shape);

    memset(shape, 0, sizeof(*shape));
    *shape = (Shape){
        .width = width,
        .height = height,
        .fragments = malloc(sizeof(ShapeFragment) * width * height)
    };

    PANIC_NULL(shape->fragments);
    for(size_t i = 0; i < shape->width * shape->height; i++){
        shape->fragments[i] = (ShapeFragment){
            .x = INFINITY,
            .y = INFINITY,
        };
    }
}

void shape_free(Shape *shape){
    if(shape->fragments){
        free(shape->fragments);
    }

    memset(shape, 0, sizeof(*shape));
}

void shape_draw_circle(Shape *shape, float cx, float cy, float r){
    PANIC_NULL(shape);

    for (uint32_t x = 0; x < shape->width; x++){
        for (uint32_t y = 0; y < shape->height; y++){
            float rel_x = (x / (float)shape->width) * 2.0 - 1.0;
            float rel_y = (y / (float)shape->height) * 2.0 - 1.0;

            ShapeFragment *frag = &shape->fragments[y * shape->width + x];

            float dcx = cx - rel_x;
            float dcy = dstf(cy - rel_y, r);
            float dc_len_sqr = dcx * dcx + dcy * dcy;
            float dnearsest_len_sqr = dc_len_sqr - r;
            
            float dnearest_len_sqr = frag->x * frag->x + frag->y * frag->y;

            if(dnearsest_len_sqr <= dnearest_len_sqr){
                float nearest[2] = {dcx, dcy};
                vec2_eq_scale(nearest, dnearsest_len_sqr / dc_len_sqr);

                frag->x = nearest[0];
                frag->y = nearest[1];

                //printf("{%f;\t%f}\n", rel_x, rel_y);
            }
        }
    }
}

GLuint shape_create_texture(Shape *shape){
    PANIC_NULL(shape);

    GLuint texture;
    glGenTextures(1, &texture);
    if(texture == 0){
        PANIC("glGenTextures() returns 0");
    }

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, shape->width, shape->height, 0, GL_RG, GL_FLOAT, shape->fragments);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}
