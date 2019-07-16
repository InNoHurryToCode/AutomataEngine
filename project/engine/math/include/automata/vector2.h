#ifndef AUTOMATA_MATH_VECTOR_2_H
#define AUTOMATA_MATH_VECTOR_2_H

typedef float vec2[2];

void vec4_dup(vec2 r, vec2 v);
void vec2_add(vec2 r, vec2 a, vec2 b);
void vec2_sub(vec2 r, vec2 a, vec2 b);
void vec2_scale(vec2 r, vec2 v, float s);
float vec2_mul_inner(vec2 a, vec2 b);
float vec2_len(vec2 v);
void vec2_norm(vec2 r, vec2 v);
void vec2_min(vec2 r, vec2 a, vec2 b);
void vec2_max(vec2 r, vec2 a, vec2 b);
void vec2_reflect(vec2 r, vec2 v, vec2 n);
float vec2_mul_cross(vec2 a, vec2 b);

#endif
