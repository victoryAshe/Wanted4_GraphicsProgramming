#pragma once

#include <vector>
#include <d3d11.h>

namespace Craft
{
	// Render Command.
	struct RenderCommand
	{
		// Buffer: memory의 덩어리.
		
		// 정점Vertex Buffer.
		ID3D11Buffer* vertexBuffer = nullptr;

		// Index buffer(optrional, but typically used)
		ID3D11Buffer* indexBuffer = nullptr;

		// Buffer explains input data(vertex)'s appearance.
		// GL: VertextBufferObject.
		ID3D11Buffer* inputLayout = nullptr;

		// 필수 셰이더 (VS/PS)
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;

		// IndexCount.
		// vertextBuffer와 연결된 index를 어디까지 그릴지 지정.
		uint32_t indexcount = 0;
	};

	// DrawCall 담당.
	// Unreal: RHI를 접두어로 사용.
	// RHI: Render Hardware Interface => Graphic Card.
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		// Initializer.
		void Initialize();
		
		// Process DrawCall creates.
		// => Run Rendering Pipe-line.
		void DrawScene();

	private:
		// Render queue.: It doesn't have to be a queue data structure.
		std::vector<RenderCommand> renderQueue;

	};

}