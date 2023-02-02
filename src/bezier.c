#include "bezier.h"
#include "vec.h"

void bezier_point(float result[2], const float from[2], const Bezier *to, float progress){
    float inter1[2];
    float inter2[2];
    float inter3[2];

    vec2_lerp(inter1, from, to->c1, progress);
    vec2_lerp(inter2, to->c1, to->c2, progress);
    vec2_lerp(inter3, to->c2, to->to, progress);

    vec2_eq_lerp(inter1, inter2, progress);
    vec2_eq_lerp(inter2, inter3, progress);

    vec2_lerp(result, inter1, inter2, progress);
}