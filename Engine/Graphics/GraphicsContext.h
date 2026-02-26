#pragma once

#include <d3d11.h>	 // Direct3D 11 General.
#include <dxgi.h>	// Related to DXGI Device (swap chain)
#include <string>

// Device (Graphic Card)
// There are 3 Objects handled as "Device" in Direct3D.
// Device: Create Resource.
// DeviceContext: Binding => Allocate created resources to graphic card.
// SwapChain: Swap Back-Buffer <=> Front-Buffer.

namespace Craft
{
	// Forward Declaration
	class Win32Window;


	// Provides Features related to Graphics
	// and, Manages Resources.	
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		//Initializer.
		void Initialize(const Win32Window& window);

	private:
		// Create Devices.
		void CreateDevice();
		void CreateSwapChain(const Win32Window& window);
		void CreateViewport(const Win32Window& window);

	private:

		// Devices.
		// Direct3D resources could be only handled by as a pointer.
		// Request Create/Delete to API.
		ID3D11Device* device = nullptr;

		// Creates DrawCall.
		ID3D11DeviceContext* context = nullptr;

		// Provides Double Buffering Features.
		IDXGISwapChain* swapChain = nullptr;

		// ViewPort.
		D3D11_VIEWPORT viewport = {};

		// ScreenSize
		uint32_t width = 0;
		uint32_t height = 0;

	};

}