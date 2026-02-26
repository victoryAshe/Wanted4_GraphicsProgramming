#include "Engine.h"
#include "Win32Window.h"
#include "Graphics/GraphicsContext.h"



namespace Craft
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	bool Engine::Initialize(HINSTANCE instance)
	{
		// Create Window Object.
		window = std::make_unique<Win32Window>(
			setting.width,
			setting.height,
			setting.title,
			instance,
			Win32MessageProcedure
		);

		// Initialize window.
		if (!window->Initialize())
		{
			__debugbreak();
			return false;
		}

		// Create Context Object.
		graphicsContext = std::make_unique<GraphicsContext>();

		// Initialize graphics context.
		graphicsContext->Initialize(*window); // ¿ªÂüÁ¶

		// Message Process Loop invoked from the window.
		// GetMessage - Sync method (Blocking method).
		// PeekMessage - Async method (Non-Blocking method).
		// Sync: Don't process anything before the problematic process is processed.
		// Async: Skip relentless the problematic process is processed.
		MSG msg = {};

		// Loop before Window_Quit_Message.
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				// Appropriately Translate the given message.
				TranslateMessage(&msg);

				// Send the translated message to the process function.
				DispatchMessage(&msg);
			}
			// If there is no window message, play engine loop.
			else
			{
				// Proccess Frame.
				graphicsContext->BeginScene(0.6f, 0.7f, 0.8f);
				graphicsContext->EndScene(setting.vsync);
			}
		}


		return true;
	}

	void Engine::Run()
	{
	}

	LRESULT Engine::Win32MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(handle, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(handle, &ps);
		}
		return 0;

		}
		return DefWindowProc(handle, message, wparam, lparam);
	}
}