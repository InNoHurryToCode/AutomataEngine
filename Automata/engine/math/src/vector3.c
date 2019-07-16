#include <math.h>
#include "../include/automata/vector3.h";

void vec3_add(vec3 r, const vec3 a, const vec3 b) {
	int i = 0;

	while (i < 3) {
		r[i] = a[i] + b[i];
		++i;
	}
}

void vec3_sub(vec3 r, const vec3 a, const vec3 b) {
	int i = 0;

	while (i < 3) {
		r[i] = a[i] - b[i];
		++i;
	}
}


void vec3_scale(vec3 r, const vec3 v, const float s) {
	int i = 0;

	while (i < 3) {
		r[i] = v[i] * s;
		++i;
	}
}

float vec3_mul_inner(const vec3 a, const vec3 b) {
	int i = 0;
	float p = 0.0f;

	while (i < 3) {
		p += a[i] * b[i];
		++i;
	}

	return p;
}

float vec3_len(const vec3 v) {
	return sqrtf(vec3_mul_inner(v, v));
}

void vec3_norm(vec3 r, vec3 const v) {
	float k = 1.0 / vec3_len(v);

	vec3_scale(r, v, k);
}

void vec3_min(vec3 r, const vec3 a, const vec3 b) {
	int i = 0;

	while (i < 3) {
		r[i] = a[i] < b[i] ? a[i] : b[i];
		++i;
	}
}

void vec3_max(vec3 r, const vec3 a, const vec3 b) {
	int i = 0;

	while (i < 3) {
		r[i] = a[i] > b[i] ? a[i] : b[i];
		++i;
	}
}

void vec3_reflect(vec3 r, vec3 const v, vec3 const n) {
	int i = 0;
	float p = 2.0f * vec3_mul_inner(v, n);

	while (i < 3) {
		r[i] = v[i] - p * n[i];
		++i;
	}
}

void vec3_mul_cross(vec3 r, const vec3 a, const vec3 b) {
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
}
