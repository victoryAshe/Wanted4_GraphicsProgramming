#include "Renderer.h"
#include "Core/Common.h"
#include "Graphics/GraphicsContext.h"

#include <d3dcompiler.h>

namespace Craft 
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		// @Temp: 재사용하는 RenderCommand 해제.
		auto& command = renderQueue[0];
		SafeRelease(command.vertexBuffer);
		SafeRelease(command.indexBuffer);
		SafeRelease(command.inputLayout);
		SafeRelease(command.vertexShader);
		SafeRelease(command.pixelShader);
	}

	void Renderer::Initialize()
	{
		// @Temp: Framework 구성될 때까지 임시로 재사용할 resource 생성.
		auto& device = GraphicsContext::Get().GetDevice();


		// ====== Create VertexBuffer ======
		// Vertext Data (3 dots).
		// NDC 좌표계: Noramlize Device Coordinate, clip space.
		float vertices[] =
		{
			0.0f, 0.5f, 0.1f,	// first point
			0.5f, -0.5f, 0.1f,	// second point
			-0.5f, -0.5f, 0.1f,	// third point.
		};

		// Set Buffer Attribute.
		/*
		UINT ByteWidth,
		D3D11_USAGE Usage,
		UINT BindFlags,
		UINT CPUAccessFlags,
		UINT MiscFlags,
		UINT StructureByteStride,
		*/
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = sizeof(float) * _countof(vertices);
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;


		// Set Sub-resource data (실제 data 할당).
		/*
		// pSysMem에 설정된 data를 한 번에 전체 사용할 때는 아래 두 UINT를 0으로 설정.     
		const void *pSysMem;
		UINT SysMemPitch;
		UINT SysMemSlicePitch;
		*/
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices;

		// Create Vertex Buffer.
		ID3D11Buffer* vertexBuffer = nullptr;
		HRESULT result = device.CreateBuffer(
			&vertexBufferDesc,
			&vertexData,
			&vertexBuffer
		);

		// Exception Handling.
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}


		// ====== Create IndexBuffer ======
		// index (삼각형 조합할 때 사용할 점의 순서를 지정).
		uint32_t indices[] = { 0,1,2 };

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * _countof(indices);
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indices;

		// Create IndexBuffer.
		ID3D11Buffer* indexBuffer = nullptr;
		result = device.CreateBuffer(
			&indexBufferDesc,
			&indexData,
			&indexBuffer
		);


		// Exception Handling.
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}


		// ====== Create Input Layout ======
		// Shader compile.

		// Create Shader Object.

		// Create Input Layout.


		// Insert RendeerQueue.
		RenderCommand command;
		command.vertexBuffer = vertexBuffer;
		command.indexBuffer = indexBuffer;
		command.indexcount = _countof(indices);

	}

	void Renderer::DrawScene()
	{
	}

}