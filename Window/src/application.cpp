#include "application.h"

Application::Application()
	: hInstance_	(::GetModuleHandle(nullptr))
	, main_window_	{ "Main Window" } {
}

bool Application::Initialize(const int &size_w, const int &size_h, const std::string& window_name) {
	printf("Started Initializing the Application\n");

	if (!main_window_.Initialize(hInstance_, size_w, size_h, window_name, true)) {
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
	main_window_.Quit(hInstance_, "MainWindow");
	hInstance_	= nullptr;

	printf("Application was Quit Safely\n");
}
