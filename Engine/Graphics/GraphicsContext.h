#pragma once

#include <d3d11.h>	 // Direct3D 11 General.
#include <dxgi.h>	// Related to DXGI Device (swap chain)
#include <string>

// Device (Graphic Card)
// There are 3 Objects handled as "Device" in Direct3D.
// Device: Create Resource.
// DeviceContext: Binding => Allocate created resources to graphic card.
// SwapChain: Swap Back-Buffer <=> Front-Buffer.

// View: Use for special resource communication between CPU <=> GPU
//	=> When CPU creates resource, => GPU copy and use it.
//  Unique concept used in DX.

// RenderTargetView: Frame(Image) resource to draw on the screen.
// Forward Renderer: if the light volume is small, forward renderer is the fastest. => This Time, we use it.
// Deferred Renderer: GPU builds images at every stage => CPU draws the final image at the last.
//	=> Unreal default renderer: Deferred Renderer. 
//		But, if neccessary (if the target device is mobile, etc.) you can turn on the forward renderer.


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

		// Prepare frame.
		void BeginScene(float red, float green, float blue);

		// 나중에 Renderer에서 DrawScene(또는 DrawFrame) 함수가 호출될 예정.

		// Change chain: send completed frame to moniter.
		// vsync가 0이면 수직동기화 X. 1이면 모니터 수직동기화 사용.
		void EndScene(uint32_t vsync);

	private:
		// Create Devices.
		void CreateDevice();
		void CreateSwapChain(const Win32Window& window);
		void CreateViewport(const Win32Window& window);

		void CreateRenderTargetView();

	private:

		// Devices.
		// Direct3D resources could be only handled by as a pointer.
		// Request Create/Delete to API.
		ID3D11Device* device = nullptr;

		// Creates DrawCall.
		ID3D11DeviceContext* context = nullptr;

		// Provides Double Buffering Features.
		IDXGISwapChain* swapChain = nullptr;

		// Resource.
		// RTV: RenderTargetView
		ID3D11RenderTargetView* renderTargetView = nullptr;

		// ViewPort.
		D3D11_VIEWPORT viewport = {};

		// ScreenSize
		uint32_t width = 0;
		uint32_t height = 0;

	};

}