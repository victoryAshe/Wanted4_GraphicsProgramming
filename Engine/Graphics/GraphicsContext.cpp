#include "GraphicsContext.h"
#include "Core/Win32Window.h"
#include "Core/Common.h"

#include <cassert>

namespace Craft
{
	// Initialize singleton variable.
	GraphicsContext* GraphicsContext::instance = nullptr;

	GraphicsContext::GraphicsContext()
	{
		assert(!instance);
		instance = this;
	}

	GraphicsContext::~GraphicsContext()
	{
		// free the resources.
		SafeRelease(device);
		SafeRelease(context);
		SafeRelease(swapChain);
	}

	void GraphicsContext::Initialize(const Win32Window& window)
	{
		// Set member variable 
		width = window.Width();
		height = window.Height();

		// Create Device.
		CreateDevice();

		// Create SwapChain.
		CreateSwapChain(window);

		//Create ViewPort.
		CreateViewport(window);

		// Create RTV.
		CreateRenderTargetView();

		// @Incomplete: In this Engine, We don't have to change viewport.
		// because we use only one viewport.
		// If you want to use multiple viewport, change the code below.
		context->RSSetViewports(1, &viewport);
	}

	void GraphicsContext::BeginScene(float red, float green, float blue)
	{
		// Prepare the image to draw.
		// Fill the image with the one colour.
		// Simple Rendering Process: 
		// Prepare a blank paper => Draw => Send to the moniter.

		// Set paper to draw.
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// the colour we'll gonna use.
		float backgroundColour[4] = { red, green, blue, 1.0f };

		// Make it as a blank paper => Fill it with a colour. 
		// It is memset => Partially Fill X.
		context->ClearRenderTargetView(renderTargetView, backgroundColour);
	}

	void GraphicsContext::EndScene(uint32_t vsync)
	{
		// Send to the moniter (exchange backbuffer <=> frontbuffer).
		swapChain->Present(0, 0);
	}

	GraphicsContext& GraphicsContext::Get()
	{
		assert(instance);
		return *instance;
	}

	void GraphicsContext::CreateDevice()
	{
		// 플래그 지정.
		uint32_t flag = 0;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// Direct3D API 버전 정보.
		// 그래픽카드가 지원하는지 확인하는 용도.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		// 장치 생성.
		// Device / DeviceContext 생성.
		/*
		*   IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE DriverType,
			HMODULE Software,
			UINT Flags,
			CONST D3D_FEATURE_LEVEL* pFeatureLevels,
			UINT FeatureLevels,
			UINT SDKVersion,
			ID3D11Device** ppDevice,
			D3D_FEATURE_LEVEL* pFeatureLevel,
			ID3D11DeviceContext** ppImmediateContext );
		*/
		// 오류인 경우 음수값 반환됨.
		HRESULT result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&context
		);

		// 예외처리.
		//SUCCEEDED()
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}


	}

	void GraphicsContext::CreateSwapChain(const Win32Window& window)
	{
		// Get Obejct Creates SwapChain.
		IDXGIFactory* factory = nullptr;
		HRESULT result = CreateDXGIFactory(
			__uuidof(IDXGIFactory),
			reinterpret_cast<void**>(&factory)
		);

		// 예외 처리.
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		/*
		*   DXGI_MODE_DESC BufferDesc;
			DXGI_SAMPLE_DESC SampleDesc;
			DXGI_USAGE BufferUsage;
			UINT BufferCount;
			HWND OutputWindow;
			BOOL Windowed;
			DXGI_SWAP_EFFECT SwapEffect;
			UINT Flags;
		*/
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.Windowed = true;	// 창 모드로 시작.
		swapChainDesc.OutputWindow = window.Handle();
		// 화면 출력용.
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// 사용할 버퍼 수.
		swapChainDesc.BufferCount = 2;

		// 안티-안리아싱(Anti-Aliasing)에 수퍼샘플링 수준 설정.
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		// 버퍼(프레임-이미지) 설정.
		swapChainDesc.BufferDesc.Width = window.Width();
		swapChainDesc.BufferDesc.Height = window.Height();
		// 이미지 픽셀 포맷(32비트-부호없고-정규화된 포맷).
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// 버퍼 교환 효과 설정.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// 스왑 체인 생성.

		result = factory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 팩토리 객체 해제.
		SafeRelease(factory);
	}

	void GraphicsContext::CreateViewport(const Win32Window& window)
	{
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window.Width());
		viewport.Height = static_cast<float>(window.Height());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
	}

	void GraphicsContext::CreateRenderTargetView()
	{
		// Traditional Method:
		// Set Image attribute struct.
		// create RTV based on the struct.

		// But we: crate back-buffer's RTV.
		// SwapCahin has basic back-buffer.
		// we'll create RTV using SwapChain's back-buffer.

		// variable to save back-buffer information loaded from swap-chain.
		ID3D11Texture2D* backbuffer = nullptr;
		HRESULT result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));

		// Exception Handling.
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// Device Creates RTV.
		result = device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView
		);

		// Exception Handling.
		if (FAILED(result))
		{
			// Release resource used for creating RTV. 
			SafeRelease(backbuffer);

			__debugbreak();
			return;
		}

		// Release resource used for creating RTV. 
		SafeRelease(backbuffer);
	}
}