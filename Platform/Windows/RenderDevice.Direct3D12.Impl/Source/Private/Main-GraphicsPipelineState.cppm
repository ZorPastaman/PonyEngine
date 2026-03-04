/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsPipelineState;

import std;

import PonyEngine.Math;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :PipelineState;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class GraphicsPipelineState final : public IGraphicsPipelineState
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsPipelineState(ID3D12PipelineState& pipelineState, const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params);
		[[nodiscard("Pure constructor")]]
		GraphicsPipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState, 
			const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params);
		GraphicsPipelineState(const GraphicsPipelineState&) = delete;
		GraphicsPipelineState(GraphicsPipelineState&&) = delete;

		~GraphicsPipelineState() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IPipelineLayout>& Layout() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual GraphicsShaderTypeMask ShaderStages() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const AttachmentParams& Attachment() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const RasterizerParams& Rasterizer() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const DepthStencilParams& DepthStencil() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const SampleParams& Sample() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const BlendParams& Blend() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() const noexcept;

		GraphicsPipelineState& operator =(const GraphicsPipelineState&) = delete;
		GraphicsPipelineState& operator =(GraphicsPipelineState&&) = delete;

	private:
		void SetComplexData(const GraphicsPipelineStateParams& params);

		[[nodiscard("Pure function")]]
		static GraphicsShaderTypeMask GetShaderStages(const GraphicsPipelineStateParams& params) noexcept;

		class PipelineState pipelineState;
		std::shared_ptr<const IPipelineLayout> layout;

		std::unique_ptr<std::byte[]> data;

		BlendParams blend;
		AttachmentParams attachment;
		SampleParams sample;
		RasterizerParams rasterizer;
		DepthStencilParams depthStencil;

		GraphicsShaderTypeMask shaderStages;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsPipelineState::GraphicsPipelineState(ID3D12PipelineState& pipelineState,
		const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) :
		pipelineState(pipelineState),
		layout(layout),
		sample(params.sample),
		rasterizer(params.rasterizer),
		depthStencil(params.depthStencil),
		shaderStages{GetShaderStages(params)}
	{
		SetComplexData(params);
	}

	GraphicsPipelineState::GraphicsPipelineState(
		Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState,
		const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) :
		pipelineState(std::move(pipelineState)),
		layout(layout),
		sample(params.sample),
		rasterizer(params.rasterizer),
		depthStencil(params.depthStencil),
		shaderStages{GetShaderStages(params)}
	{
		SetComplexData(params);
	}

	const std::shared_ptr<const IPipelineLayout>& GraphicsPipelineState::Layout() const noexcept
	{
		return layout;
	}

	GraphicsShaderTypeMask GraphicsPipelineState::ShaderStages() const noexcept
	{
		return shaderStages;
	}

	const RasterizerParams& GraphicsPipelineState::Rasterizer() const noexcept
	{
		return rasterizer;
	}

	const BlendParams& GraphicsPipelineState::Blend() const noexcept
	{
		return blend;
	}

	const DepthStencilParams& GraphicsPipelineState::DepthStencil() const noexcept
	{
		return depthStencil;
	}

	const SampleParams& GraphicsPipelineState::Sample() const noexcept
	{
		return sample;
	}

	const AttachmentParams& GraphicsPipelineState::Attachment() const noexcept
	{
		return attachment;
	}

	std::string_view GraphicsPipelineState::Name() const noexcept
	{
		return pipelineState.Name();
	}

	void GraphicsPipelineState::Name(const std::string_view name)
	{
		pipelineState.Name(name);
	}

	ID3D12PipelineState& GraphicsPipelineState::PipelineState() const noexcept
	{
		return pipelineState.GetPipelineState();
	}

	void GraphicsPipelineState::SetComplexData(const GraphicsPipelineStateParams& params)
	{
		const std::size_t rtFormatByteSize = params.attachment.renderTargetFormats.size_bytes();
		const auto [rtBlendByteSize, rtBlendAlignment] = std::visit(Type::Overload
		{
			[](const BlendGroupParams& p) noexcept
			{
				return std::pair(p.renderTargetBlend.size_bytes(), alignof(RenderTargetBlendParams));
			},
			[](const LogicBlendGroupParams& p) noexcept
			{
				return std::pair(p.renderTargetBlend.size_bytes(), alignof(LogicRenderTargetBlendParams));
			}
		}, params.blend.blendGroup);
		const std::size_t rtBlendByteOffset = Math::Align(rtFormatByteSize, rtBlendAlignment);
		const std::size_t rtBlendByteEnd = rtBlendByteOffset + rtBlendByteSize;

		if (rtBlendByteEnd > 0uz)
		{
			data = std::make_unique<std::byte[]>(rtBlendByteEnd);
			std::memcpy(data.get(), params.attachment.renderTargetFormats.data(), params.attachment.renderTargetFormats.size_bytes());
			std::visit(Type::Overload
			{
				[&](const BlendGroupParams& p) noexcept
				{
					std::memcpy(data.get() + rtBlendByteOffset, p.renderTargetBlend.data(), p.renderTargetBlend.size_bytes());
				},
				[&](const LogicBlendGroupParams& p) noexcept
				{
					std::memcpy(data.get() + rtBlendByteOffset, p.renderTargetBlend.data(), p.renderTargetBlend.size_bytes());
				}
			}, params.blend.blendGroup);
		}

		attachment.renderTargetFormats = !params.attachment.renderTargetFormats.empty() 
			? std::span<const RenderTargetAttachmentFormat>(reinterpret_cast<const RenderTargetAttachmentFormat*>(data.get()), params.attachment.renderTargetFormats.size())
			: std::span<const RenderTargetAttachmentFormat>();
		attachment.depthStencilFormat = params.attachment.depthStencilFormat;

		blend.blendGroup = std::visit(Type::Overload
		{
			[&](const BlendGroupParams& p) noexcept
			{
				return std::variant<BlendGroupParams, LogicBlendGroupParams>(BlendGroupParams
				{
					.renderTargetBlend = !p.renderTargetBlend.empty()
						? std::span<const RenderTargetBlendParams>(reinterpret_cast<const RenderTargetBlendParams*>(data.get() + rtBlendByteOffset), p.renderTargetBlend.size())
						: std::span<const RenderTargetBlendParams>()
				});
			},
			[&](const LogicBlendGroupParams& p) noexcept
			{
				return std::variant<BlendGroupParams, LogicBlendGroupParams>(LogicBlendGroupParams
				{
					.logicOperation = p.logicOperation,
					.renderTargetBlend = !p.renderTargetBlend.empty()
						? std::span<const LogicRenderTargetBlendParams>(reinterpret_cast<const LogicRenderTargetBlendParams*>(data.get() + rtBlendByteOffset), p.renderTargetBlend.size())
						: std::span<const LogicRenderTargetBlendParams>()
				});
			}
		}, params.blend.blendGroup);
	}

	GraphicsShaderTypeMask GraphicsPipelineState::GetShaderStages(const GraphicsPipelineStateParams& params) noexcept
	{
		auto stages = GraphicsShaderTypeMask::None;
		if (!params.amplificationShader.empty())
		{
			stages |= GraphicsShaderTypeMask::Amplification;
		}
		if (!params.meshShader.empty())
		{
			stages |= GraphicsShaderTypeMask::Mesh;
		}
		if (!params.pixelShader.empty())
		{
			stages |= GraphicsShaderTypeMask::Pixel;
		}

		return stages;
	}
}
