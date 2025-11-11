#include <windows.h>
#include "application.h"

#ifdef WIN32_APP
int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine,
					int		  nCmdShow) {
	Application app;
	if (!app.Initialize(600, 400, "skeleton")) {
		MessageBox(nullptr, "Initialize application failed.", "Error", MB_OK);
		return -1;
	}

	app.Run();
	app.Quit();

	return 0;
}
#endif
