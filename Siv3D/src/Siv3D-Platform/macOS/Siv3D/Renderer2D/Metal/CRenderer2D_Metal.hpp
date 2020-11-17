//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/TextureFilter.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer2D/Vertex2DBuilder.hpp>
# import <Metal/Metal.h>
# import <QuartzCore/CAMetalLayer.h>
# include "MetalRenderer2DCommand.hpp"
# include "MetalVertex2DBatch.hpp"

namespace s3d
{
	struct MetalStandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		bool ok() const
		{
			return sprite
				&& fullscreen_triangle;
		}
	};

	struct MetalStandardPS2D
	{
		PixelShader shape;
		PixelShader fullscreen_triangle;

		bool ok() const
		{
			return shape
				&& fullscreen_triangle;
		}
	};

	struct MetalVSConstants2D
	{
		Float4 transform[2];
		Float4 colorMul{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct MetalPSConstants2D
	{
		Float4 colorAdd{ 0, 0, 0, 0 };
		Float4 sdfParam{ 0, 0, 0, 0 };
		Float4 internal{ 0, 0, 0, 0 };
	};

	class CRenderer_Metal;
	class CShader_Metal;

	class CRenderer2D_Metal final : public ISiv3DRenderer2D
	{
	private:
		
		CRenderer_Metal* pRenderer = nullptr;
		CShader_Metal* pShader = nullptr;
		id<MTLDevice> m_device = nil;
		id<MTLCommandQueue> m_commandQueue = nil;
		CAMetalLayer* m_swapchain = nullptr;
				
		id<MTLRenderPipelineState> m_sceneRenderPipelineState = nil;
		id<MTLRenderPipelineState> m_fullscreenTriangleRenderPipelineState = nil;
		MTLRenderPassDescriptor* m_renderPassDescriptor;
		
		std::unique_ptr<MetalStandardVS2D> m_standardVS;
		std::unique_ptr<MetalStandardPS2D> m_standardPS;
		
		ConstantBuffer<MetalVSConstants2D> m_vsConstants2D;
		ConstantBuffer<MetalPSConstants2D> m_psConstants2D;
		
		MetalVertex2DBatch m_batches;
		MetalRenderer2DCommandManager m_commandManager;
		BufferCreatorFunc m_bufferCreator;

	public:

		CRenderer2D_Metal();

		~CRenderer2D_Metal() override;

		void init() override;
		
		void addRect(const FloatRect& rect, const Float4& color) override;

		void flush(id<MTLCommandBuffer> commandBuffer);

		void drawFullScreenTriangle(id<MTLCommandBuffer> commandBuffer, TextureFilter textureFilter);
		
		void begin();
	};
}
