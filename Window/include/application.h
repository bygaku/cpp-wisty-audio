#ifndef APPLICATION_INCLUDE
#define APPLICATION_INCLUDE
#include <windows.h>
#include <cstdio>
#include <cstdint>
#include <string>

class IApplication;

/**
 * @brief Easy wrapper class of WindowsAPI
 * @code
 *	[in entry function]:
 *
 *	Application app;
 *
 *	if(!app.Initialize()) {	// default initialization.
 *		return -1;
 *	}
 *
 *	app.Run();
 *	app.Terminate();
 *
 *	return 0;
 * @endcode
 */
class Application {
public:
	/** @brief Constructor */
	Application();

	/** @brief Destructor */
	~Application() {
		if (!hInstance_) return;
		Application::Finalize();
	}

	/**
	 * @brief Application initialization.
	 * @param size_w: Window width. default: 800
	 * @param size_h: Window height. default: 600
	 * @param window_name: The name of window title bar. default: "Default"
	 * @return If there is an error, return false.
	*/
	bool Initialize(const int& size_w = 800, const int& size_h = 600, const std::string& window_name = "default");

	/**
	 * @brief Running process.
	 */
	void Run();

	/**
	 * @brief Clean up the application.
	 * @attention This method can be optionally written when you explicitly want to finalize it.
	 * @attention Reason: it is automatically called in the destructor.
	 */
	void Finalize();

private:
	/**
	 * @brief Window procedure.
	 * @param hWnd Window handle.
	 * @param uMsg Message code.
	 * @param wP Additional data related to the message.
	 * @param lP Additional data related to the message.
	 * @return
	 */
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wP, LPARAM lP);

	/**
	 * @brief Start up the main window.
	 * @return If there is an error, return false.
	 */
	bool InitializeWindow();

private:
	const LPCTSTR kWindowClassName_ = "MainWindow";

	HINSTANCE hInstance_;		// App instance handle
	HWND	  hWnd_;			// Window handle
	LPCTSTR	  window_name_;		// Name of title bar
	int  	  w_;				// Window width
	int  	  h_;				// Window height

};


#endif // APPLICATION_INCLUDE