#pragma once

#include <memory>
#include <Windows.h>
#include <string>

// Engine Setting.
struct EngineSetting
{
	uint32_t width = 1280;
	uint32_t height = 800;
	std::wstring title = L"Craft Engine";
	float framerate = 120.0f;
	uint32_t vsync = 0;
};


namespace Craft
{



	// Forward Declararaihno.
	class Win32Window;
	class GraphicsContext;

	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		// Initializer.
		bool Initialize(HINSTANCE instance);

		// Run Engine Loop.
		void Run();

	protected:
		// Call-back function: Process window message.
		static LRESULT CALLBACK Win32MessageProcedure(
			HWND handle, 
			UINT message, 
			WPARAM wparam, 
			LPARAM lparam
		);

	protected:

		// Window Object.
		std::unique_ptr<Win32Window> window;

		// Graphics Context Object. (Manage Device, etc.)
		std::unique_ptr<GraphicsContext> graphicsContext;
		
		// Engine Setting Variable.
		EngineSetting setting;
	};
}
