#ifndef AUTOMATA_MATH_VECTOR_3_H
#define AUTOMATA_MATH_VECTOR_3_H

typedef float vec3[3];

void vec3_dup(vec3 r, vec3 v);
void vec3_add(vec3 r, vec3 a, vec3 b);
void vec3_sub(vec3 r, vec3 a, vec3 b);
void vec3_scale(vec3 r, vec3 v, float s);
float vec3_mul_inner(vec3 a, vec3 b);
float vec3_len(vec3 v);
void vec3_norm(vec3 r, vec3 v);
void vec3_min(vec3 r, vec3 a, vec3 b);
void vec3_max(vec3 r, vec3 a, vec3 b);
void vec3_reflect(vec3 r, vec3 v, vec3 n);
void vec3_mul_cross(vec3 r, vec3 a, vec3 b);

#endif
