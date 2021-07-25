#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	// Register the window class
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window

	HWND hwnd = CreateWindowEx(
		0, // Optional window styles
		CLASS_NAME, // Window class
		L"Learn to Program Windows", // Window text
		WS_OVERLAPPEDWINDOW, // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL, // Parent window
		NULL, // Menu
		hInstance, // Instance handle
		NULL // Additional application data
	);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really Quit?", L"My Application", MB_OKCANCEL) == IDOK) {
			DestroyWindow(hwnd);
		}
		// If reach here, user canceled
		return 0;

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);

		return 0;

	case WM_SIZE:
		int width = LOWORD(lParam); // Macro to get the low-order word
		int height = HIWORD(lParam); // Macro to get teh high-order word

		// Respond to the message
		OnSize(hwnd, (UINT)wParam, width, height);
		break;
	}
	// Perform default action for the message, which varies by message type
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void OnSize(HWND hwnd, UINT flag, int width, int height) {
	// Handle resizing
}
