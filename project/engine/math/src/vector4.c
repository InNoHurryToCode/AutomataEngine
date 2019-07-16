#include <math.h>
#include "../include/automata/vector4.h"

void vec4_dup(vec4 r, vec4 v) {
	int i = 0;

	while (i < 4) {
		r[i] = v[i];
		++i;
	}
}

void vec4_add(vec4 r, vec4 a, vec4 b) {
	int i = 0;

	while (i < 4) {
		r[i] = a[i] + b[i];
		++i;
	}
}

void vec4_sub(vec4 r, vec4 a, vec4 b) {
	int i = 0;

	while (i < 4) {
		r[i] = a[i] - b[i];
		++i;
	}
}

void vec4_scale(vec4 r, vec4 v, float s) {
	int i = 0;

	while (i < 4) {
		r[i] = v[i] * s;
		++i;
	}
}

float vec4_mul_inner(vec4 a, vec4 b) {
	int i = 0;
	float p = 0.0f;

	while (i < 4) {
		p += a[i] * b[i];
		++i;
	}

	return p;
}

float vec4_len(vec4 v) {
	(float)sqrt((double)vec4_mul_inner(v, v));
}

void vec4_norm(vec4 r, vec4 v) {
	float k = 1.0f / vec4_len(v);

	vec4_scale(r, v, k);
}

void vec4_min(vec4 r, vec4 a, vec4 b) {
	int i = 0;

	while (i < 4) {
		r[i] = a[i] < b[i] ? a[i] : b[i];
		++i;
	}
}

void vec4_max(vec4 r, vec4 a, vec4 b) {
	int i = 0;

	while (i < 4) {
		r[i] = a[i] > b[i] ? a[i] : b[i];
		++i;
	}
}

void vec4_reflect(vec4 r,  vec4 v, vec4 n) {
	int i = 0;
	float p = 2.0f * vec4_mul_inner(v, n);

	while (i < 4) {
		r[i] = v[i] - p * n[i];
		++i;
	}
}

void vec4_mul_cross(vec4 r, vec4 a, vec4 b) {
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
	r[3] = 1.0f;
}
