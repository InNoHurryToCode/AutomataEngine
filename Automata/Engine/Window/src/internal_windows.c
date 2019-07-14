#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <glad/glad.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "../src/internal_windows.h";

static MSG msg = { 0 };
static HWND window = NULL;
static HGLRC context = NULL;

static int createContext(HWND hwnd) {
	HDC hdc = NULL;
	HGLRC tmpContext = NULL;
	int version = 0;
	int pixelFormat = 0;
	const PIXELFORMATDESCRIPTOR pfd = {
		.nSize = sizeof(pfd),
		.nVersion = 1,
		.iPixelType = PFD_TYPE_RGBA,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.cColorBits = 32,
		.cAlphaBits = 8,
		.iLayerType = PFD_MAIN_PLANE,
		.cDepthBits = 24,
		.cStencilBits = 8,
	};
	const int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	/* get device context */
	hdc = GetDC(hwnd);

	if (!hdc) {
		return 0;
	}

	/* set pixel format */
	pixelFormat = ChoosePixelFormat(hdc, &pfd);

	if (!SetPixelFormat(hdc, pixelFormat, &pfd)) {
		return 0;
	}

	/* create test opengl context */
	tmpContext = wglCreateContext(hdc);

	if (!tmpContext) {
		return 0;
	}

	/* set test opengl context */
	if (!wglMakeCurrent(hdc, tmpContext)) {
		return 0;
	}

	/* load opengl extentions */
	version = gladLoadGL();

	/* create real opengl context */
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	context = wglCreateContextAttribsARB(hdc, 0, attribs);

	if (!context) {
		context = tmpContext;
	}

	/* delete test context */
	wglDeleteContext(tmpContext);
	tmpContext = NULL;

	/* set real opengl context */
	if (!wglMakeCurrent(hdc, context)) {
		return 0;
	}

	/* creating context successful */
	return 1;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CLOSE:
		case WM_DESTROY:
			/* close window */
			if (context) {
				wglDeleteContext(context);
			}

			PostQuitMessage(0);
			break;

		case WM_CREATE:
			/* create context */
			if (!createContext(hwnd)) {
				DestroyWindow(hwnd);
			}
			break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int internal_windowCreate(int width, int height, const char* title) {
	WNDCLASS wc = { 0 };

	/* initialize window */
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "automatawindow";

	if (!RegisterClass(&wc)) {
		return EXIT_FAILURE;
	}

	/* create window */
	window = CreateWindow(wc.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, HWND_DESKTOP, NULL, wc.hInstance, NULL);

	if (!window) {
		return 0;
	}

	/* creating window successful */
	return 1;
}

int internal_windowDestroy() {
	if (!window) {
		return 0;
	}

	/* destroy the window */
	if (!DestroyWindow(window)) {
		return 0;
	}

	return 1;
}

int internal_windowShouldClose() {
	/* close window */
	if (GetMessage(&msg, NULL, 0, 0) <= 0) {
		return 1;
	}

	/* update window */
	return 0;
}

void internal_windowUpdate() {
	/* update window */
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void internal_windowSwapBuffers() {
	if (!window) {
		return;
	}

	/* swap buffers */
	SwapBuffers(GetDC(window));
}