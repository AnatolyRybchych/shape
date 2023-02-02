#ifndef BEZIER_H_
#define BEZIER_H_

typedef struct Bezier Bezier;

void bezier_point(float result[2], const float from[2], const Bezier *to, float progress);

struct Bezier{
    float to[2];

    float c1[2];
    float c2[2];
};

#endif //BEZIER_H_