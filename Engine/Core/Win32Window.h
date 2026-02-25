#pragma once

#include <Windows.h>
#include <string>
#include <stdint.h>


namespace Craft
{
	// window class created using WIN32 API.
	class Win32Window
	{
	public:
		Win32Window(
			uint32_t width = 1280,
			uint32_t height = 800,
			HINSTANCE instance = nullptr,
			
			// Call-back function.
			// use for processing window message.
			// Window procedure.
			WNDPROC messageProcedure = nullptr
		);

		~Win32Window();

		// Initializer.
		bool Initialize();

		// Getter.
		inline uint32_t Width() const { return width; }
		inline uint32_t Height() const { return height; }
		inline HWND Handle() const { return handle; }

	private:
		std::wstring title = L"Craft Engine";
		
		// !!IT MIGHT BE "UNIQUE NAME"!!: Register the window class.
		std::wstring className = L"Craft Engine Class";

		// The Window size.
		uint32_t width = 0;
		uint32_t height = 0;

		// Window Object pointer(Handle)
		HWND handle = nullptr;

		// Program pointer (Instance)
		HINSTANCE instance = nullptr;

		// message procedure function pointer.
		WNDPROC messageProcedure = nullptr;
	};
}