#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include "../src/internal_windows.h";

#define KEY_PRESSED 0x80

static const int keysAmount = 107;
static int keyStates[107] = { 0 };
static const int keyCodes[107] = {
	0x41,	/* a */
	0x42,	/* b */
	0x43,	/* c */
	0x44,	/* d */
	0x45,	/* e */
	0x46,	/* f */
	0x47,	/* g */
	0x48,	/* h */
	0x49,	/* i */
	0x4A,	/* j */
	0x4B,	/* k */
	0x4C,	/* l */
	0x4D,	/* m */
	0x4E,	/* n */
	0x4F,	/* o */
	0x50,	/* p */
	0x51,	/* q */
	0x52,	/* r */
	0x53,	/* s */
	0x54,	/* t */
	0x55,	/* u */
	0x56,	/* v */
	0x57,	/* w */
	0x58,	/* x */
	0x59,	/* y */
	0x5A,	/* z */
	0x31,	/* 1 */
	0x32,	/* 2 */
	0x33,	/* 3 */
	0x34,	/* 4 */
	0x35,	/* 5 */
	0x36,	/* 6 */
	0x37,	/* 7 */
	0x38,	/* 8 */
	0x39,	/* 9 */
	0x30,	/* 0 */
	0x70,	/* F1 */
	0x71,	/* F2 */
	0x72,	/* F3 */
	0x73,	/* F4 */
	0x74,	/* F5 */
	0x75,	/* F6 */
	0x76,	/* F7 */
	0x77,	/* F8 */
	0x78,	/* F9 */
	0x79,	/* F10 */
	0x7A,	/* F11 */
	0x7B,	/* F12 */
	0x26,	/* arrow up */
	0x28,	/* arrow down */
	0x27,	/* arrow left */
	0x29,	/* arrow right */
	0x0D,	/* enter */
	0x1B,	/* esc */
	0x20,	/* spacebar */
	0x08,	/* backspace */
	0x09,	/* tab */
	0xA0,	/* left ctrl */
	0xA3,	/* right ctrl */
	0xA0,	/* left shift */
	0xA1,	/* right shift */
	0xA4,	/* left alt */
	0xA5,	/* right alt */
	0x5B,	/* left windows */
	0x5C,	/* right windows */
	0x2C,	/* print screen */
	0x2D,	/* insert */
	0x2E,	/* delete */
	0xC0,	/* tilde */
	0xBB,	/* plus */
	0xBD,	/* minus */
	0xDB,	/* bracket left */
	0xDD,	/* bracket right */
	0xBA,	/* semicolon */
	0xDE,	/* quote */
	0xBC,	/* comma */
	0xBE,	/* dot */
	0xBF,	/* slash */
	0xDC,	/* backslash */
	0x21,	/* page up */
	0x22,	/* page down */
	0x24,	/* home */
	0x23,	/* end */
	0x14,	/* caps lock */
	0x90,	/* num lock */
	0x91,	/* scroll lock */
	0x61,	/* numpad 1 */
	0x62,	/* numpad 2 */
	0x63,	/* numpad 3 */
	0x64,	/* numpad 4 */
	0x65,	/* numpad 5 */
	0x66,	/* numpad 6 */
	0x67,	/* numpad 7 */
	0x68,	/* numpad 8 */
	0x69,	/* numpad 9 */
	0x60,	/* numpad 0 */
	0x0D,	/* numpad enter (requires IParam & 0x1000000 to be detected) */
	0x6E,	/* numpad dot */
	0x6B,	/* numpad plus */
	0x6D,	/* numpad minus */
	0x6A,	/* numpad multiply */
	0x6F,	/* numpad divide */
	0x01,	/* mouse button left */
	0x02,	/* mouse button right */
	0x04,	/* mouse button middle */
	0x04,	/* mouse button 5 */
	0x06	/* mouse button 6 */
};

void internal_inputUpdate() {
	int i = 0;

	/* set keys state */
	while (i < keysAmount) {
		/* key pressed */
		if (GetKeyState(keyCodes[i]) & KEY_PRESSED) {
			keyStates[i] = 1;
		} else {
			keyStates[i] = 0;
		}

		++i;
	}
}

int internal_inputGetKey(int key) {
	if (key < 0 || key > keysAmount) {
		return 0;
	}
	
	return keyStates[key];
}

int internal_inputDetectKey() {
	int i = 0;

	/* detect key */
	while (i < keysAmount) {
		if (internal_inputGetKey(i)) {
			return i;
		}

		++i;
	}

	/* no key pressed */
	return keysAmount;
}