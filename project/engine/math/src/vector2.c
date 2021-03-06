#include <math.h>
#include "../include/automata/vector2.h"

void vec2_dup(vec2 r, vec2 v) {
	int i = 0;

	while (i < 2) {
		r[i] = v[i];
		++i;
	}
}

void vec2_add(vec2 r, vec2 a, vec2 b) {
	int i = 0;

	while (i < 2) {
		r[i] = a[i] + b[i];
		++i;
	}
}

void vec2_sub(vec2 r, vec2 a, vec2 b) {
	int i = 0;

	while (i < 2) {
		r[i] = a[i] - b[i];
		++i;
	}
}

void vec2_scale(vec2 r, vec2 v, float s) {
	int i = 0;

	while (i < 2) {
		r[i] = v[i] * s;
		++i;
	}
}

float vec2_mul_inner(vec2 a, vec2 b) {
	int i = 0;
	float p = 0.0f;

	while (i < 2) {
		p += a[i] * b[i];
		++i;
	}

	return p;
}

float vec2_len(vec2 v) {
	(float)sqrt((double)vec2_mul_inner(v, v));
}

void vec2_norm(vec2 r, vec2 v) {
	float k = 1.0f / vec2_len(v);

	vec2_scale(r, v, k);
}

void vec2_min(vec2 r, vec2 a, vec2 b) {
	int i = 0;

	while (i < 2) {
		r[i] = a[i] < b[i] ? a[i] : b[i];
		++i;
	}
}

void vec2_max(vec2 r, vec2 a, vec2 b) {
	int i = 0;

	while (i < 2) {
		r[i] = a[i] > b[i] ? a[i] : b[i];
		++i;
	}
}

void vec2_reflect(vec2 r, vec2 v, vec2 n) {
	int i = 0;
	float p = 2.0f * vec2_mul_inner(v, n);

	while (i < 2) {
		r[i] = v[i] - p * n[i];
		++i;
	}
}

float vec2_mul_cross(vec2 a, vec2 b) {
	return (a[0] * b[1]) - (a[1] * b[0]);
}
