#include <stdlib.h>
#include <windows.h>
#include "../src/internal_windows.h";

/// --- replace this with GLAD!
#include <GL/GL.h>
#pragma comment (lib, "opengl32.lib")
/// ---

static MSG msg = { 0 };
static HGLRC context = { 0 };

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
	
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

static void internal_createContext(HWND window) {
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,	/* Flags */
		PFD_TYPE_RGBA,        /* The kind of framebuffer */
		32,                   /* Colordepth of the framebuffer */
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   /* Number of bits for the depthbuffer */
		8,                    /* Number of bits for the stencilbuffer */
		0,                    /* Number of Aux buffers in the framebuffer */
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC dc = GetDC(window);
	int pixelFormat = ChoosePixelFormat(dc, &pfd);

	/* set the pixel format */
	SetPixelFormat(dc, pixelFormat, &pfd);

	/* create window context */
	context = wglCreateContext(dc);
	wglMakeCurrent(GetDC(window), context);
}

void internal_create(int width, int height, const char* title) {
	WNDCLASS wc = { 0 };
	HWND window = { 0 };

	/* initialize window */
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.style = CS_OWNDC;
	wc.lpszClassName = "automatawindow";

	if (!RegisterClass(&wc)) {
		return NULL;
	}

	/* create window */
	window = CreateWindow(wc.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, HWND_DESKTOP, NULL, wc.hInstance, NULL);

	if (!IsWindow(window)) {
		return;
	}

	/* create opengl context */
	internal_createContext(window);
}

void internal_destroy() {
	wglDeleteContext(context);
}

int internal_shouldClose() {
	return GetMessage(&msg, NULL, 0, 0) > 0 ? 0 : 1;
}

void internal_update() {
	DispatchMessage(&msg);
}