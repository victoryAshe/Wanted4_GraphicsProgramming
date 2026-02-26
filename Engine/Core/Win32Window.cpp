#include "Win32Window.h"

namespace Craft
{
	Win32Window::Win32Window(
		uint32_t width, 
		uint32_t height, 
        const std::wstring& title,
		HINSTANCE instance, 
		WNDPROC messageProcedure)
		: width(width), height(height), title(title),
		instance(instance),
		messageProcedure(messageProcedure)
	{
	}

	Win32Window::~Win32Window()
	{
		// Unregister the Window.
		UnregisterClass(className.c_str(), instance);
	}

	bool Win32Window::Initialize()
	{
        // Fill struct to make the window.
        WNDCLASS wc = { };
        wc.lpfnWndProc = messageProcedure;
        wc.hInstance = instance;               // Pointer that indicates Program(process).
        wc.lpszClassName = className.c_str();

        // Exception Handling: Failed to Register Class.
        if (!RegisterClass(&wc))
        {
            return false;
        }


        RECT rect = {};
        rect.left = 0;
        rect.top = 0;
        rect.right = width;
        rect.bottom = height;

        // Get the size of the window.
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
        // => Then, the rect is resized.

        // the Size of the resized window.
        uint32_t windowWidth = rect.right - rect.left;
        uint32_t windowHeight = rect.bottom - rect.top;

        // Set the position of the creation
        // GetSystemMetrics => Get System values.
        uint32_t positionX
            = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
        uint32_t positionY
            = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

        // Create the window.
        handle = CreateWindow(
            className.c_str(),              // Window class
            title.c_str(),                  // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Position and Size.
            positionX, positionY,           // Set the position as the middle.
            windowWidth, windowHeight,

            nullptr,        // Parent window    
            nullptr,        // Menu
            instance,      // Instance handle
            nullptr         // Additional application data
        );

        // Exception Handling: failed to create the window.
        if (!handle)
        {
            return false;
        }


        // Set the Window visible state.
        ShowWindow(handle, SW_SHOW);
		
        return true;
	}
}