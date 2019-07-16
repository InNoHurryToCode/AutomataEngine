#ifndef AUTOMATA_MATH_MATRIX_4x4_H
#define AUTOMATA_MATH_MATRIX_4x4_H

#include "vector3.h";
#include "vector4.h";

typedef float mat4x4[4][4];

void mat4x4_identity(mat4x4 M);
void mat4x4_dup(mat4x4 M, mat4x4 N);
void mat4x4_row(vec4 r, mat4x4 M, int i);
void mat4x4_col(vec4 r, mat4x4 M, int i);
void mat4x4_transpose(mat4x4 M, mat4x4 N);
void mat4x4_add(mat4x4 M, mat4x4 a, mat4x4 b);
void mat4x4_sub(mat4x4 M, mat4x4 a, mat4x4 b);
void mat4x4_scale(mat4x4 M, mat4x4 a, float k);
void mat4x4_scale_aniso(mat4x4 M, mat4x4 a, float x, float y, float z);
void mat4x4_mul(mat4x4 M, mat4x4 a, mat4x4 b);
void mat4x4_mul_vec4(vec4 r, mat4x4 M, vec4 v);
void mat4x4_translate(mat4x4 T, float x, float y, float z);
void mat4x4_translate_in_place(mat4x4 M, float x, float y, float z);
void mat4x4_from_vec3_mul_outer(mat4x4 M, vec3 a, vec3 b);
void mat4x4_rotate(mat4x4 R, mat4x4 M, float x, float y, float z, float angle);
void mat4x4_rotate_X(mat4x4 Q, mat4x4 M, float angle);
void mat4x4_rotate_Y(mat4x4 Q, mat4x4 M, float angle);
void mat4x4_rotate_Z(mat4x4 Q, mat4x4 M, float angle);
void mat4x4_invert(mat4x4 T, mat4x4 M);
void mat4x4_orthonormalize(mat4x4 R, mat4x4 M);
void mat4x4_frustum(mat4x4 M, float l, float r, float b, float t, float n, float f);
void mat4x4_ortho(mat4x4 M, float l, float r, float b, float t, float n, float f);
void mat4x4_perspective(mat4x4 m, float y_fov, float aspect, float n, float f);
void mat4x4_look_at(mat4x4 m, vec3 eye, vec3 center, vec3 up);

#endif
