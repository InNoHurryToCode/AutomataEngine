#ifndef AUTOMATA_MATH_VECTOR_4_H
#define AUTOMATA_MATH_VECTOR_4_H

typedef float vec4[4];

void vec4_dup(vec4 r, vec4 v);
void vec4_add(vec4 r, vec4 a, vec4 b);
void vec4_sub(vec4 r, vec4 a, vec4 b);
void vec4_scale(vec4 r, vec4 v, float s);
float vec4_mul_inner(vec4 a, vec4 b);
float vec4_len(vec4 v);
void vec4_norm(vec4 r, vec4 v);
void vec4_min(vec4 r, vec4 a, vec4 b);
void vec4_max(vec4 r, vec4 a, vec4 b);
void vec4_reflect(vec4 r, vec4 v, vec4 n);
void vec4_mul_cross(vec4 r, vec4 a, vec4 b);

#endif
