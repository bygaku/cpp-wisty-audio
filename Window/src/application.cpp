#include "application.h"

Application::Application()
	: hInstance_	(::GetModuleHandle(nullptr))
	, main_window_	{ } {
}

bool Application::Initialize(const int &size_w, const int &size_h, const std::string& window_name) {
	printf("Started Initializing the Application\n");

	if (!main_window_.Initialize(size_w, size_h, window_name, true)) {
		return false;
	}

	return true;
}

void Application::Run() {
	printf("Application Running\n");

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Application::Quit() {
	if (hInstance_) {
		UnregisterClass(kWindowClassName_, hInstance_);
	}

	hInstance_	= nullptr;

	printf("Application was Quit Safely\n");
}

LRESULT CALLBACK Application::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wP, LPARAM lP) {
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

bool Application::InitializeWindow() {
	if (hInstance_ == nullptr) {
		return false;
	}

	WNDCLASSEX wc{};
	wc.hInstance			= hInstance_;
	wc.lpszClassName		= kWindowClassName_;
	wc.lpfnWndProc			= Window::StaticWndProc;
	wc.style				= 0;
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.hIcon				= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm				= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor				= LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName			= nullptr;
	wc.hbrBackground		= GetSysColorBrush(COLOR_WINDOW);

	if (!RegisterClassEx(&wc)) return false;

	hWnd_ = CreateWindowEx(
		WS_EX_TOOLWINDOW,
		kWindowClassName_,
		window_name_,
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		w_, h_,
		HWND_DESKTOP,
		nullptr,
		hInstance_,
		nullptr
		);

	if (!hWnd_) return false;

	return true;
}
