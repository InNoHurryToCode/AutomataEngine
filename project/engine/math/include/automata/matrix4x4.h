#ifndef AUTOMATA_MATH_MATRIX_4x4_H
#define AUTOMATA_MATH_MATRIX_4x4_H

#include "vector3.h"
#include "vector4.h"

typedef float mat4x4[4][4];

void mat4x4_dup(mat4x4 m, mat4x4 n);
void mat4x4_identity(mat4x4 m);
void mat4x4_row(vec4 m, mat4x4 n, int i);
void mat4x4_col(vec4 m, mat4x4 n, int i);
void mat4x4_transpose(mat4x4 m, mat4x4 n);
void mat4x4_add(mat4x4 m, mat4x4 a, mat4x4 b);
void mat4x4_sub(mat4x4 m, mat4x4 a, mat4x4 b);
void mat4x4_scale(mat4x4 m, mat4x4 n, float s);
void mat4x4_scale_aniso(mat4x4 m, mat4x4 n, vec3 s);
void mat4x4_mul(mat4x4 m, mat4x4 a, mat4x4 b);
void mat4x4_mul_vec4(vec4 m, mat4x4 n, vec4 v);
void mat4x4_translate(mat4x4 m, vec3 v);
void mat4x4_translate_in_place(mat4x4 m, vec3 r);
void mat4x4_from_vec3_mul_outer(mat4x4 m, vec3 a, vec3 b);
void mat4x4_rotate(mat4x4 m, mat4x4 n, vec3 r, float angle);
void mat4x4_rotate_X(mat4x4 m, mat4x4 n, float angle);
void mat4x4_rotate_Y(mat4x4 m, mat4x4 n, float angle);
void mat4x4_rotate_Z(mat4x4 m, mat4x4 n, float angle);
void mat4x4_invert(mat4x4 m, mat4x4 n);
void mat4x4_orthonormalize(mat4x4 m, mat4x4 n);
void mat4x4_frustum(mat4x4 m, float l, float r, float b, float t, float n, float f);
void mat4x4_ortho(mat4x4 m, float l, float r, float b, float t, float n, float f);
void mat4x4_perspective(mat4x4 m, float y_fov, float aspect, float n, float f);
void mat4x4_look_at(mat4x4 m, vec3 eye, vec3 center, vec3 up);

#endif
