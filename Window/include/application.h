#ifndef APPLICATION_INCLUDE
#define APPLICATION_INCLUDE
#include <cstdint>

class Application {
public:
	/** @brief Constructor */
	Application();

	/** @brief Destructor */
	~Application();

	/**
	 * @brief Application initialization.
	 * @param size_w: Window width.
	 * @param size_h: Window height.
	 * @return If there is an error, return 0.
	*/
	bool Initialize(uint32_t size_w, uint32_t size_h);

	/**
	 * @brief Running process.
	 */
	void Run();

	/**
	 * @brief Clean up the application.
	 */
	void Terminate();

private:
	/**
	 * @brief Start up the main window.
	 * @return If there is an error, return 0.
	 */
	bool InitializeWindow();

private:
	HINSTANCE hInstance_;	// app instance handle
	HWND	  hWnd_;		//

};


#endif // APPLICATION_INCLUDE