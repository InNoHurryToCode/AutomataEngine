#include <stddef.h>
#include <windows.h>
#include <glad/glad.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "../src/internal_windows.h";

static MSG msg = { 0 };
static HWND window = { 0 };
static HGLRC context = { 0 };

static void internal_createContext(window) {
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,	/* flags */
		PFD_TYPE_RGBA,        /* the kind of framebuffer */
		32,                   /* colordepth of the framebuffer */
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   /* number of bits for the depthbuffer */
		8,                    /* number of bits for the stencilbuffer */
		0,                    /* number of aux buffers in the framebuffer */
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0, 0
	};
	HDC hdc = GetDC(window);
	HGLRC tmpContext = wglCreateContext(hdc);
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	int version = 0;

	/* set the pixel format */
	SetPixelFormat(hdc, pixelFormat, &pfd);

	// create a fake context
	if (!tmpContext) {
		MessageBox(NULL, "Can't create test context", NULL, MB_OK);
		return;
	}

	if (!wglMakeCurrent(hdc, tmpContext)) {
		MessageBox(NULL, "Can't make test context current", NULL, MB_OK);
		return;
	}

	// load opengl extentions
	version = gladLoadGL();

	// create window context
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	context = wglCreateContextAttribsARB(hdc, 0, attribs);
	
	if (!context) {
		context = tmpContext;
	}

	/* delete fake context */
	wglDeleteContext(tmpContext);
	tmpContext = NULL;

	/* assign window context */
	wglMakeCurrent(hdc, context);
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		internal_createContext();
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void internal_create(int width, int height, const char* title) {
	WNDCLASS wc = { 0 };

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

void internal_swapBuffers() {
	SwapBuffers(GetDC(window));
}