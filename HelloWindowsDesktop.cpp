// HelloWindowsDesktop.cpp
// Compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global Variables:

// Main window class name
static TCHAR szWindowClass[] = _T("DesktopApp");

// String that appears in the application's title bar
static TCHAR szTitle[] = _T("Custom File Explorer");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Custom File Explorer"),
			NULL
		);

		return 1;
	}
	
	// Store instance handle in our global variable
	hInst = hInstance;

	/* 
	* Parameters to CreateWindowEx explained:
	* WX_EX_OVERLAPPEDWINDOW : optional extended window style
	* szWindowClass : name of the application
	* szTitle : text that appears in the title bar
	* WS_OVERLAPPEDWINDOW : type of window to create
	* CW_USEDEFAULT, CW_USEDEFAULT : initial position (x,y)
	* 500, 100 : initial size (width, length)
	* NULL : parent of this window
	* NULL : application does not have a menu bar
	* hInstance : first parameter from WinMain
	* Null : not used in this application
	*/
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL,
			_T("Call to CreateWindowEx failed"),
			_T("Custom File Explorer"),
			NULL
		);

		return 1;
	}

	/*
	* Parameters to ShowWindow explained:
	* hWnd : value returned from CreateWindow
	* nCmdShow : fourth parameter from WinMain
	*/
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

/*
* Function : WndProc(HWND, UINT, WPARAM, LPARAM)
* 
* PURPOSE : Processes messages for the main window
* 
* WM_PAINT - Paint the main window
* MW_DESTROY - Post a quit message and return
*/
LRESULT CALLBACK WndProc(
	HWND hWnd, 
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows Desktop!");

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here the application is laid out.
		// For this introduction, just print out "Hello, Windows Desktop!"
		// in the top left corner.
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
		// End application-specific layout section

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}