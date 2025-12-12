#include "window.h"

Window::Window(LPCTSTR window_class_name)
	: window_class_name_(window_class_name)
	, hWnd_			(nullptr)
	, window_name_	("Default")
	, w_			(800)
	, h_			(600) {
}

Window::~Window() {

}

void Window::Quit(HINSTANCE hInstance, LPCTSTR window_class_name) {
	UnregisterClass(window_class_name, hInstance);
}

bool Window::Initialize(HINSTANCE hInstance, const int &size_w, const int &size_h, const std::string &window_name, bool main_window) {
	if (hInstance == nullptr) {
		return false;
	}

	WNDCLASSEX wc{};
	wc.hInstance			= hInstance;
	wc.lpszClassName		= window_class_name_;
	wc.lpfnWndProc			= Window::StaticWndProc;
	wc.style				= 0;
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.hIcon				= LoadIcon(hInstance, IDI_APPLICATION);
	wc.hIconSm				= LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor				= LoadCursor(hInstance, IDC_ARROW);
	wc.lpszMenuName			= nullptr;
	wc.hbrBackground		= GetSysColorBrush(COLOR_WINDOW);

	if (!RegisterClassEx(&wc)) return false;

	hWnd_ = CreateWindowEx(
		WS_EX_TOOLWINDOW,
		window_class_name_,
		window_name_,
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		w_, h_,
		HWND_DESKTOP,
		nullptr,
		hInstance,
		nullptr
		);

	if (!hWnd_) return false;

	return true;
}

LRESULT Window::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wP, LPARAM lP) {
	switch (uMsg) {
		case WM_CREATE: {
			printf("Creating the Window\n");
			auto* tpCreateSt = reinterpret_cast<CREATESTRUCT*>(lP);

#ifndef WIN32_APP
#endif
			::ShowWindow(hWnd, SW_SHOWNORMAL);
			::UpdateWindow(hWnd);
			printf("Window Creation Completed\n");
		}
			break;
		case WM_DESTROY: {
			printf("Window Destroy\n");
			PostQuitMessage(0);
		}
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wP, lP);
	}

	return 0;
}
