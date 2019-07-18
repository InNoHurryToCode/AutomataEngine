#include <math.h>
#include "../include/automata/matrix4x4.h"

void mat4x4_dup(mat4x4 m, mat4x4 n) {
	int i = 0;
	int j = 0;

	while (i < 4) {
		while (j < 4) {
			m[i][j] = n[i][j];
			++j;
		}

		++i;
	}
}

void mat4x4_identity(mat4x4 m) {
	int i = 0;
	int j = 0;

	while (i < 4) {
		while (j < 4) {
			m[i][j] = i == j ? 1.f : 0.f;
			++j;
		}

		++i;
	}
}

void mat4x4_row(vec4 m, mat4x4 n, int i) {
	int j = 0;

	while (j < 4) {
		m[j] = n[j][i];
		++j;
	}
}

void mat4x4_col(vec4 m, mat4x4 n, int i) {
	int j = 0;

	while (j < 4) {
		m[j] = n[i][j];
		++j;
	}	
}

void mat4x4_transpose(mat4x4 m, mat4x4 n) {
	int i = 0;
	int j = 0;

	while (j < 4) {
		while (i < 4) {
			m[i][j] = n[j][i];
			++i;
		}

		++j;
	}
}

void mat4x4_add(mat4x4 m, mat4x4 a, mat4x4 b) {
	int i = 0;

	while (i < 4) {
		vec4_add(m[i], a[i], b[i]);
		++i;
	}
}

void mat4x4_sub(mat4x4 m, mat4x4 a, mat4x4 b) {
	int i = 0;

	while (i < 4) {
		vec4_sub(m[i], a[i], b[i]);
		++i;
	}
}

void mat4x4_scale(mat4x4 m, mat4x4 n, float s) {
	int i = 0;

	while (i < 4) {
		vec4_scale(m[i], n[i], s);
		++i;
	}
}

void mat4x4_scale_aniso(mat4x4 m, mat4x4 n, vec3 s) {
	int i = 0;

	vec4_scale(m[0], n[0], s[0]);
	vec4_scale(m[1], n[1], s[1]);
	vec4_scale(m[2], n[2], s[2]);

	while (i < 4) {
		m[3][i] = n[3][i];
		++i;
	}
}

void mat4x4_mul(mat4x4 m, mat4x4 a,  mat4x4 b) {
	mat4x4 temp = { 0.0f };
	int k = 0;
	int r = 0;
	int c = 0;

	while (c < 4) {
		while (r < 4) {
			temp[c][r] = 0.0f;

			while (k < 4) {
				temp[c][r] += a[k][r] * b[c][k];
				++k;
			}

			++r;
		}

		++c;
	}

	mat4x4_dup(m, temp);
}

void mat4x4_mul_vec4(vec4 m, mat4x4 n, vec4 v) {
	int i = 0;
	int j = 0;

	while (j < 4) {
		m[j] = 0.0f;

		while (i < 4) {
			m[j] += n[i][j] * v[i];
			++i;
		}

		++j;
	}
}

void mat4x4_translate(mat4x4 m, vec3 v) {
	mat4x4_identity(m);
	m[3][0] = v[0];
	m[3][1] = v[1];
	m[3][2] = v[2];
}

void mat4x4_translate_in_place(mat4x4 m, vec3 r) {
	int i = 0;
	vec4 t = { r[0], r[1], r[2], 0 };
	vec4 n = { 0 };

	while (i < 4) {
		mat4x4_row(n, m, i);
		m[3][i] += vec4_mul_inner(n, t);
		++i;
	}
}

void mat4x4_from_vec3_mul_outer(mat4x4 m, vec3 a, vec3 b) {
	int i = 0;
	int j = 0;

	while (i < 4) {
		while (j < 4) {
			m[i][j] = i < 3 && j < 3 ? a[i] * b[j] : 0.0f;
			++j;
		}

		++i;
	}
}

void mat4x4_rotate(mat4x4 m, mat4x4 n, vec3 r, float angle) {
	float s = (float)sin((double)angle);
	float c = (float)cos((double)angle);
	vec3 u = { r[0], r[1], r[2] };
	mat4x4 T = { 0.0f };
	mat4x4 S = { 0.0f };
	mat4x4 C = { 0.0f };

	if (vec3_len(u) < 0.0001) {
		mat4x4_dup(m, n);
	} else  {
		vec3_norm(u, u);
		mat4x4_from_vec3_mul_outer(T, u, u);

		S[0][1] = u[2];
		S[0][2] = -u[1];
		S[1][0] = -u[2];
		S[1][2] = u[0];
		S[2][0] = u[1];
		S[2][1] = -u[0];

		mat4x4_scale(S, S, s);
		mat4x4_identity(C);
		mat4x4_sub(C, C, T);
		mat4x4_scale(C, C, c);
		mat4x4_add(T, T, C);
		mat4x4_add(T, T, S);

		T[3][3] = 1.0f;
		mat4x4_mul(m, n, T);
	}
}

void mat4x4_rotate_X(mat4x4 m, mat4x4 n, float angle) {
	float s = (float)sin((double)angle);
	float c = (float)cos((double)angle);
	mat4x4 r = { 0.0f };

	r[0][0] = 1.0f;
	r[1][1] = c;
	r[1][2] = s;
	r[2][1] = -s;
	r[2][2] = c;
	r[3][3] = 1.0f;

	mat4x4_mul(m, n, r);
}

void mat4x4_rotate_Y(mat4x4 m, mat4x4 n, float angle)
{
	float s = (float)sin((double)angle);
	float c = (float)cos((double)angle);
	mat4x4 r = { 0.0f };

	r[0][0] = c;
	r[0][2] = s;
	r[1][1] = 1.0f;
	r[2][0] = -s;
	r[2][2] = c;
	r[3][3] = 1.0f;

	mat4x4_mul(m, n, r);
}

void mat4x4_rotate_Z(mat4x4 m, mat4x4 n, float angle)
{
	float s = (float)sin((double)angle);
	float c = (float)cos((double)angle);
	mat4x4 r = { 0.0f };

	r[0][0] = c;
	r[0][1] = s;
	r[1][0] = -s;
	r[1][1] = c;
	r[2][2] = 1.0f;
	r[3][3] = 1.0f;

	mat4x4_mul(m, n, r);
}

void mat4x4_invert(mat4x4 m, mat4x4 n) {
	float idet = 0.0f;
	float s[6] = { 0.0f };
	float c[6] = { 0.0f };

	s[0] = n[0][0] * n[1][1] - n[1][0] * n[0][1];
	s[1] = n[0][0] * n[1][2] - n[1][0] * n[0][2];
	s[2] = n[0][0] * n[1][3] - n[1][0] * n[0][3];
	s[3] = n[0][1] * n[1][2] - n[1][1] * n[0][2];
	s[4] = n[0][1] * n[1][3] - n[1][1] * n[0][3];
	s[5] = n[0][2] * n[1][3] - n[1][2] * n[0][3];

	c[0] = n[2][0] * n[3][1] - n[3][0] * n[2][1];
	c[1] = n[2][0] * n[3][2] - n[3][0] * n[2][2];
	c[2] = n[2][0] * n[3][3] - n[3][0] * n[2][3];
	c[3] = n[2][1] * n[3][2] - n[3][1] * n[2][2];
	c[4] = n[2][1] * n[3][3] - n[3][1] * n[2][3];
	c[5] = n[2][2] * n[3][3] - n[3][2] * n[2][3];

	/* Assumes it is invertible */
	idet = 1.0f / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

	m[0][0] = (n[1][1] * c[5] - n[1][2] * c[4] + n[1][3] * c[3]) * idet;
	m[0][1] = (-n[0][1] * c[5] + n[0][2] * c[4] - n[0][3] * c[3]) * idet;
	m[0][2] = (n[3][1] * s[5] - n[3][2] * s[4] + n[3][3] * s[3]) * idet;
	m[0][3] = (-n[2][1] * s[5] + n[2][2] * s[4] - n[2][3] * s[3]) * idet;
	m[1][0] = (-n[1][0] * c[5] + n[1][2] * c[2] - n[1][3] * c[1]) * idet;
	m[1][1] = (n[0][0] * c[5] - n[0][2] * c[2] + n[0][3] * c[1]) * idet;
	m[1][2] = (-n[3][0] * s[5] + n[3][2] * s[2] - n[3][3] * s[1]) * idet;
	m[1][3] = (n[2][0] * s[5] - n[2][2] * s[2] + n[2][3] * s[1]) * idet;
	m[2][0] = (n[1][0] * c[4] - n[1][1] * c[2] + n[1][3] * c[0]) * idet;
	m[2][1] = (-n[0][0] * c[4] + n[0][1] * c[2] - n[0][3] * c[0]) * idet;
	m[2][2] = (n[3][0] * s[4] - n[3][1] * s[2] + n[3][3] * s[0]) * idet;
	m[2][3] = (-n[2][0] * s[4] + n[2][1] * s[2] - n[2][3] * s[0]) * idet;
	m[3][0] = (-n[1][0] * c[3] + n[1][1] * c[1] - n[1][2] * c[0]) * idet;
	m[3][1] = (n[0][0] * c[3] - n[0][1] * c[1] + n[0][2] * c[0]) * idet;
	m[3][2] = (-n[3][0] * s[3] + n[3][1] * s[1] - n[3][2] * s[0]) * idet;
	m[3][3] = (n[2][0] * s[3] - n[2][1] * s[1] + n[2][2] * s[0]) * idet;
}

void mat4x4_orthonormalize(mat4x4 m, mat4x4 n) {
	float s = 1.0f;
	vec3 h = { 0.0f };

	mat4x4_dup(m, n);
	vec3_norm(m[2], m[2]);

	s = vec3_mul_inner(m[1], m[2]);
	vec3_scale(h, m[2], s);
	vec3_sub(m[1], m[1], h);
	vec3_norm(m[1], m[1]);

	s = vec3_mul_inner(m[0], m[2]);
	vec3_scale(h, m[2], s);
	vec3_sub(m[0], m[0], h);

	s = vec3_mul_inner(m[0], m[1]);
	vec3_scale(h, m[1], s);
	vec3_sub(m[0], m[0], h);
	vec3_norm(m[0], m[0]);
}

void mat4x4_frustum(mat4x4 m, float l, float r, float b, float t, float n, float f) {
	mat4x4 temp = { 0.0f };
	
	temp[0][0] = 2.0f * n / (r - l);
	temp[1][1] = 2.0f * n / (t - b);
	temp[2][0] = (r + l) / (r - l);
	temp[2][1] = (t + b) / (t - b);
	temp[2][2] = -(f + n) / (f - n);
	temp[2][3] = -1.0f;
	temp[3][2] = -2.0f * (f * n) / (f - n);

	mat4x4_dup(m, temp);
}

void mat4x4_ortho(mat4x4 m, float l, float r, float b, float t, float n, float f) {
	mat4x4 temp = { 0.0f };
	
	temp[0][0] = 2.0f / (r - l);
	temp[1][1] = 2.0f / (t - b);
	temp[2][2] = -2.0f / (f - n);
	temp[3][0] = -(r + l) / (r - l);
	temp[3][1] = -(t + b) / (t - b);
	temp[3][2] = -(f + n) / (f - n);
	temp[3][3] = 1.0f;

	mat4x4_dup(m, temp);
}

void mat4x4_perspective(mat4x4 m, float y_fov, float aspect, float n, float f) {
	float a = 1.0f / (float)tan((double)(y_fov / 2.0f));
	mat4x4 temp = { 0.0f };

	temp[0][0] = a / aspect;
	temp[1][1] = a;
	temp[2][2] = -((f + n) / (f - n));
	temp[2][3] = -1.0f;
	temp[3][2] = -((2.0f * f * n) / (f - n));

	mat4x4_dup(m, temp);
}

/* Adapted from Android's OpenGL Matrix.java.                        */
/* See the OpenGL GLUT documentation for gluLookAt for a description */
/* of the algorithm. We implement it in a straightforward way.       */

void mat4x4_look_at(mat4x4 m, vec3 eye, vec3 center, vec3 up) {
	vec3 f = { 0.0f };
	vec3 s = { 0.0f };
	vec3 t = { 0.0f };
	vec3 negativeEye = { 0.0f };
	mat4x4 temp = { 0.0f };

	negativeEye[0] = -eye[0];
	negativeEye[1] = -eye[1];
	negativeEye[2] = -eye[2];

	vec3_sub(f, center, eye);
	vec3_norm(f, f);
	vec3_mul_cross(s, f, up);
	vec3_norm(s, s);
	vec3_mul_cross(t, s, f);

	temp[0][0] = s[0];
	temp[0][1] = t[0];
	temp[0][2] = -f[0];
	temp[1][0] = s[1];
	temp[1][1] = t[1];
	temp[1][2] = -f[1];
	temp[2][0] = s[2];
	temp[2][1] = t[2];
	temp[2][2] = -f[2];
	temp[3][3] = 1.0f;

	mat4x4_dup(m, temp);
	mat4x4_translate_in_place(m, negativeEye);
}
