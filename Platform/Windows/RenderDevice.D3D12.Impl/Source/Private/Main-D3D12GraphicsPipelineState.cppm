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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12GraphicsPipelineState;

import std;

import PonyEngine.Math;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :D3D12PipelineState;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12GraphicsPipelineState final : public IGraphicsPipelineState
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12GraphicsPipelineState(ID3D12PipelineState& pipelineState, const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params);
		[[nodiscard("Pure constructor")]]
		D3D12GraphicsPipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState, 
			const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params);
		D3D12GraphicsPipelineState(const D3D12GraphicsPipelineState&) = delete;
		D3D12GraphicsPipelineState(D3D12GraphicsPipelineState&&) = delete;

		~D3D12GraphicsPipelineState() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IPipelineLayout>& Layout() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ShaderTypeMask ShaderStages() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const RasterizerParams& Rasterizer() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const BlendParams& Blend() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const DepthStencilParams& DepthStencil() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const SampleParams& Sample() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const AttachmentParams& Attachment() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() const noexcept;

		D3D12GraphicsPipelineState& operator =(const D3D12GraphicsPipelineState&) = delete;
		D3D12GraphicsPipelineState& operator =(D3D12GraphicsPipelineState&&) = delete;

	private:
		void SetComplexData(const GraphicsPipelineStateParams& params);

		[[nodiscard("Pure function")]]
		static ShaderTypeMask GetShaderStages(const GraphicsPipelineStateParams& params) noexcept;

		D3D12PipelineState pipelineState;
		std::shared_ptr<const IPipelineLayout> layout;

		std::unique_ptr<std::byte[]> data;

		BlendParams blend;
		AttachmentParams attachment;
		RasterizerParams rasterizer;
		SampleParams sample;
		DepthStencilParams depthStencil;

		ShaderTypeMask shaderStages;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12GraphicsPipelineState::D3D12GraphicsPipelineState(ID3D12PipelineState& pipelineState,
		const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) :
		pipelineState(pipelineState),
		layout(layout),
		rasterizer(params.rasterizer),
		sample(params.sample),
		depthStencil(params.depthStencil),
		shaderStages{GetShaderStages(params)}
	{
		SetComplexData(params);
	}

	D3D12GraphicsPipelineState::D3D12GraphicsPipelineState(
		Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState,
		const std::shared_ptr<const IPipelineLayout>& layout, const GraphicsPipelineStateParams& params) :
		pipelineState(std::move(pipelineState)),
		layout(layout),
		rasterizer(params.rasterizer),
		sample(params.sample),
		depthStencil(params.depthStencil),
		shaderStages{GetShaderStages(params)}
	{
		SetComplexData(params);
	}

	const std::shared_ptr<const IPipelineLayout>& D3D12GraphicsPipelineState::Layout() const noexcept
	{
		return layout;
	}

	ShaderTypeMask D3D12GraphicsPipelineState::ShaderStages() const noexcept
	{
		return shaderStages;
	}

	const RasterizerParams& D3D12GraphicsPipelineState::Rasterizer() const noexcept
	{
		return rasterizer;
	}

	const BlendParams& D3D12GraphicsPipelineState::Blend() const noexcept
	{
		return blend;
	}

	const DepthStencilParams& D3D12GraphicsPipelineState::DepthStencil() const noexcept
	{
		return depthStencil;
	}

	const SampleParams& D3D12GraphicsPipelineState::Sample() const noexcept
	{
		return sample;
	}

	const AttachmentParams& D3D12GraphicsPipelineState::Attachment() const noexcept
	{
		return attachment;
	}

	std::string_view D3D12GraphicsPipelineState::Name() const noexcept
	{
		return pipelineState.Name();
	}

	void D3D12GraphicsPipelineState::Name(const std::string_view name)
	{
		pipelineState.Name(name);
	}

	ID3D12PipelineState& D3D12GraphicsPipelineState::PipelineState() const noexcept
	{
		return pipelineState.PipelineState();
	}

	void D3D12GraphicsPipelineState::SetComplexData(const GraphicsPipelineStateParams& params)
	{
		const std::size_t rtFormatByteSize = params.attachmentParams.renderTargetFormats.size_bytes();
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
			std::memcpy(data.get(), params.attachmentParams.renderTargetFormats.data(), params.attachmentParams.renderTargetFormats.size_bytes());
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

		attachment.renderTargetFormats = params.attachmentParams.renderTargetFormats.size() > 0uz 
			? std::span<const TextureFormatId>(reinterpret_cast<const TextureFormatId*>(data.get()), params.attachmentParams.renderTargetFormats.size())
			: std::span<const TextureFormatId>();
		attachment.depthStencilFormat = params.attachmentParams.depthStencilFormat;

		blend.blendGroup = std::visit(Type::Overload
		{
			[&](const BlendGroupParams& p) noexcept
			{
				return std::variant<BlendGroupParams, LogicBlendGroupParams>(BlendGroupParams
				{
					.renderTargetBlend = p.renderTargetBlend.size() > 0uz
						? std::span<const RenderTargetBlendParams>(reinterpret_cast<const RenderTargetBlendParams*>(data.get() + rtBlendByteOffset), p.renderTargetBlend.size())
						: std::span<const RenderTargetBlendParams>()
				});
			},
			[&](const LogicBlendGroupParams& p) noexcept
			{
				return std::variant<BlendGroupParams, LogicBlendGroupParams>(LogicBlendGroupParams
				{
					.logicOperation = p.logicOperation,
					.renderTargetBlend = p.renderTargetBlend.size() > 0uz
						? std::span<const LogicRenderTargetBlendParams>(reinterpret_cast<const LogicRenderTargetBlendParams*>(data.get() + rtBlendByteOffset), p.renderTargetBlend.size())
						: std::span<const LogicRenderTargetBlendParams>()
				});
			}
		}, params.blend.blendGroup);
	}

	ShaderTypeMask D3D12GraphicsPipelineState::GetShaderStages(const GraphicsPipelineStateParams& params) noexcept
	{
		auto stages = ShaderTypeMask::None;
		if (params.amplificationShader)
		{
			stages |= ShaderTypeMask::Amplification;
		}
		if (params.meshShader)
		{
			stages |= ShaderTypeMask::Mesh;
		}
		if (params.pixelShader)
		{
			stages |= ShaderTypeMask::Pixel;
		}

		return stages;
	}
}
