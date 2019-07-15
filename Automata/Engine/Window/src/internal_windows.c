#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <glad/glad.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "../src/internal_windows.h";

static MSG msg = { 0 };
static HWND hwnd = NULL;
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
	RECT rc = { 0 };
	const WNDCLASS wc = {
		.lpfnWndProc = WndProc,
		.hInstance = GetModuleHandle(NULL),
		.hbrBackground = (HBRUSH)(COLOR_BACKGROUND),
		.lpszClassName = "automatawindow",
	};

	/* calculate window size */
	rc.right = width;
	rc.top = height;
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, NULL);

	/* register window class */
	if (!RegisterClass(&wc)) {
		return EXIT_FAILURE;
	}

	/* create window */
	hwnd = CreateWindow(wc.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, HWND_DESKTOP, NULL, wc.hInstance, NULL);

	if (!hwnd) {
		return 0;
	}

	/* creating window successful */
	return 1;
}

void internal_windowDestroy() {
	if (!hwnd) {
		return 0;
	}

	/* destroy the window */
	DestroyWindow(hwnd);
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
	if (!hwnd || !GetDC(hwnd)) {
		return;
	}

	/* swap buffers */
	SwapBuffers(GetDC(hwnd));
}

int internal_WindowGetWidth() {
	RECT rc = { 0 };

	/* get window size */
	if (GetClientRect(hwnd, &rc)) {
		return rc.right - rc.left;
	}
	
	return 0;
}

int internal_WindowGetHeight() {
	RECT rc = { 0 };

	/* get window size */
	if (GetClientRect(hwnd, &rc)) {
		return rc.bottom - rc.top;
	}

	return 0;
}

void internal_WindowSetSize(int width, int height) {	
	RECT rc = { 0, 0, width, height };
	
	if (!hwnd || width < 0 || height < 0) {
		return 0;
	}

	/* set window size */
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, NULL);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}

void internal_WindowSetTitle(const char* title) {
	/* set window title */
	SetWindowText(hwnd, title);
}

void internal_WindowCenter() {
	RECT rc = { 0 };
	int x = 0;
	int y = 0;

	/* get center position */
	GetWindowRect(hwnd, &rc);
	x = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	y = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

	/* set window to center */
	SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}
