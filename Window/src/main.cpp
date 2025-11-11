#include "application.h"

#ifdef WIN32_APP
/** WIN32 APP MODE */
#else
int main (int argc, char *argv[]) {
	Application app;
	if (!app.Initialize(1200, 800, "skeleton")) {
		printf("!! Initialize Failed !!\n");
		return -1;
	}

	app.Run();
	app.Quit();

	return 0;
}
#endif

#ifdef NONE_APP_CLASS
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wP, LPARAM lP);

#ifdef WIN32_APP
int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine,
					int		  nCmdShow) {
	WNDCLASSEX wc{};

	wc.hInstance			= hInstance;
	wc.lpszClassName		= "MainWindow";
	wc.lpfnWndProc			= StaticWndProc;
	wc.style				= 0;
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.hIcon				= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm				= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor				= LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName			= nullptr;
	wc.hbrBackground		= GetSysColorBrush(COLOR_WINDOW);

	if (!RegisterClassEx(&wc)) return 0;

	HWND main_wnd = CreateWindow(
		"MainWindow",
		"Skeleton Window",
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 500,
		HWND_DESKTOP,
		nullptr,
		hInstance,
		nullptr
		);

	if (!main_wnd) return 0;

	ShowWindow(main_wnd, nCmdShow);
	UpdateWindow(main_wnd);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
#else
int main (int argc, char *argv[]) {
	WNDCLASSEX wc{};

	/** APP INSTANCE */
	auto hInstance = GetModuleHandle(nullptr);

	wc.hInstance			= hInstance;
	wc.lpszClassName		= "MainWindow";
	wc.lpfnWndProc			= StaticWndProc;
	wc.style				= 0;
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.hIcon				= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm				= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor				= LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName			= nullptr;
	wc.hbrBackground		= GetSysColorBrush(COLOR_WINDOW);

	if (!RegisterClassEx(&wc)) return 0;

	HWND main_wnd = CreateWindow(
		"MainWindow",
		"Skeleton Window",
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 500,
		HWND_DESKTOP,
		nullptr,
		hInstance,
		nullptr
		);

	if (!main_wnd) return 0;

	ShowWindow(main_wnd, SW_SHOWNORMAL);
	UpdateWindow(main_wnd);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		printf("command on\n");
	}

	return 0;

}
#endif

LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wP, LPARAM lP) {
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, uMsg, wP, lP);
}
#endif

