
#include "Core/Win32Window.h"

// Call-back function.
// use for processing window message.
// Window procedure.
LRESULT CALLBACK  WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

int main()
{

	// Graphics Programming.
	// Create Window, => Draw images on the window using API.
    // Using Win32 API

    // The size of window.
    uint32_t width = 1280;
    uint32_t height = 800;

    // if the parameter below is nullptr, OS try to get the pointer of this program.
    HINSTANCE hInstance = GetModuleHandle(nullptr); 

    // Create Window
    Craft::Win32Window window(
        width, height,
        hInstance,
        WindowProc
    );

    // Initialize and Exception Handling.
    if (!window.Initialize())
    {
        return -1;
    }

    // Message Process Loop invoked from the window.
    // GetMessage - Sync method (Blocking method).
    // PeekMessage - Async method (Non-Blocking method).
    // Sync: Don't process anything before the problematic process is processed.
    // Async: Skip relentless the problematic process is processed.
    MSG msg = {};

    // Loop before Window_Quit_Message.
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
        {
            // Appropriately Translate the given message.
            TranslateMessage(&msg);
            
            // Send the translated message to the process function.
            DispatchMessage(&msg);
        }
        else
        {
            // If there is no window message, play engine loop.
        }        
    }

    

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
