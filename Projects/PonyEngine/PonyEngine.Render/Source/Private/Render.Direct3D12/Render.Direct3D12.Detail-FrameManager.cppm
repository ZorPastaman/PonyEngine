/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:FrameManager;

import <memory>;
import <stdexcept>;
import <vector>;

import PonyBase.Utility;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :Frame;
import :IFrameManager;
import :ISubSystemContext;
import :RenderTargetParams;

export namespace PonyEngine::Render::Direct3D12
{
	class FrameManager final : public IFrameManager
	{
	public:
		[[nodiscard("Pure constructor")]]
		FrameManager(ISubSystemContext& d3d12System, const FrameParams& params);
		FrameManager(const FrameManager&) = delete;
		FrameManager(FrameManager&&) = delete;

		~FrameManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT RtvFormat() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT DsvFormat() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<UINT>& Resolution() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept override;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Frame> CreateFrame() override;

		void Clean() noexcept;

		FrameManager& operator =(const FrameManager&) = delete;
		FrameManager& operator =(FrameManager&&) = delete;

	private:
		static constexpr DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

		DXGI_FORMAT rtvFormat;
		PonyMath::Utility::Resolution<UINT> resolution;
		PonyMath::Color::RGBA<FLOAT> clearColor;
		DXGI_SAMPLE_DESC sampleDesc;

		ISubSystemContext* d3d12System;

		std::vector<std::shared_ptr<Frame>> frames;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	FrameManager::FrameManager(ISubSystemContext& d3d12System, const FrameParams& params) :
		rtvFormat(d3d12System.BackManager().Format()),
		resolution(params.resolution),
		clearColor(params.clearColor),
		d3d12System{&d3d12System}
	{
		if (params.msaaParams.sampleCount < 1u || params.msaaParams.sampleQuality < 0.f || params.msaaParams.sampleQuality > 1.f) [[unlikely]]
		{
			throw std::invalid_argument(PonyBase::Utility::SafeFormat("Incorrect msaa parameters. SampleCount: '{}'; SampleQuality: '{}'. SampleCount must be greater or equal to 1. SampleQuality must be in the range [0, 1].",
				params.msaaParams.sampleCount, params.msaaParams.sampleQuality));
		}

		if (params.msaaParams.sampleCount == 1u)
		{
			sampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u};

			return;
		}

		auto msaaLevels = D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS{.Format = rtvFormat, .SampleCount = static_cast<UINT>(params.msaaParams.sampleCount)};
		if (const HRESULT result = this->d3d12System->Device().CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaLevels, sizeof(msaaLevels)); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get msaa levels with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		sampleDesc = DXGI_SAMPLE_DESC{.Count = msaaLevels.SampleCount, .Quality = PonyMath::Core::RoundToIntegral<float, UINT>((msaaLevels.NumQualityLevels - 1) * params.msaaParams.sampleQuality)};
	}

	DXGI_FORMAT FrameManager::RtvFormat() const noexcept
	{
		return rtvFormat;
	}

	DXGI_FORMAT FrameManager::DsvFormat() const noexcept
	{
		return DepthStencilFormat;
	}

	const PonyMath::Utility::Resolution<UINT>& FrameManager::Resolution() const noexcept
	{
		return resolution;
	}

	DXGI_SAMPLE_DESC FrameManager::SampleDesc() const noexcept
	{
		return sampleDesc;
	}

	std::shared_ptr<Frame> FrameManager::CreateFrame()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create textures.");
		const auto renderTarget = d3d12System->ResourceManager().CreateRenderTarget(resolution.Width(), resolution.Height(), rtvFormat, sampleDesc, clearColor);
		assert(renderTarget && "The render target is nullptr.");
		const auto resolveTarget = sampleDesc.Count > 1u ? d3d12System->ResourceManager().CreateRenderTarget(resolution.Width(), resolution.Height(), rtvFormat, DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, clearColor) : nullptr;
		assert(sampleDesc.Count <= 1u || resolveTarget && "The resolve target is nullptr.");
		const auto depthStencil = d3d12System->ResourceManager().CreateDepthStencil(resolution.Width(), resolution.Height(), DepthStencilFormat, sampleDesc, D3D12_DEPTH_STENCIL_VALUE{.Depth = D3D12_MAX_DEPTH, .Stencil = 0u});
		assert(depthStencil && "The depth stencil is nullptr.");
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Textures created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create heaps.");
		const auto rtvHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1u, false);
		assert(rtvHeap && "The rtv heap is nullptr.");
		const auto srvHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1u, true);
		assert(srvHeap && "The srv heap is nullptr.");
		const auto dsvHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1u, false);
		assert(dsvHeap && "The dsv heap is nullptr.");
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Heaps created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create views.");
		const auto rtvDesc = resolveTarget
			? D3D12_RENDER_TARGET_VIEW_DESC
			{
				.Format = rtvFormat,
				.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS,
				.Texture2DMS = D3D12_TEX2DMS_RTV{}
			}
			: D3D12_RENDER_TARGET_VIEW_DESC
			{
				.Format = rtvFormat,
				.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
				.Texture2D = D3D12_TEX2D_RTV{}
			};
		d3d12System->Device().CreateRenderTargetView(&renderTarget->Data(), &rtvDesc, rtvHeap->CpuHandle(0u));
		const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D,
			.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
			.Texture2D = D3D12_TEX2D_SRV{.MostDetailedMip = 0u, .MipLevels = 1u, .PlaneSlice = 0u, .ResourceMinLODClamp = 0.f}
		};
		d3d12System->Device().CreateShaderResourceView(resolveTarget ? &resolveTarget->Data() : &renderTarget->Data(), &srvDesc, srvHeap->CpuHandle(0u));
		const auto dsvDesc = D3D12_DEPTH_STENCIL_VIEW_DESC
		{
			.Format = DepthStencilFormat,
			.ViewDimension = sampleDesc.Count > 1u ? D3D12_DSV_DIMENSION_TEXTURE2DMS : D3D12_DSV_DIMENSION_TEXTURE2D,
			.Flags = D3D12_DSV_FLAG_NONE
		};
		this->d3d12System->Device().CreateDepthStencilView(&depthStencil->Data(), &dsvDesc, dsvHeap->CpuHandle(0u));
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Views created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create frame.");
		const auto frame = std::make_shared<Frame>(renderTarget, resolveTarget, depthStencil, rtvHeap, srvHeap, dsvHeap);
		frames.push_back(frame);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Frame created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(frame.get()));

		return frame;
	}

	void FrameManager::Clean() noexcept
	{
		for (std::size_t i = frames.size(); i-- > 0; )
		{
			if (frames[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy frame at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(frames[i].get()));
				frames.erase(frames.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Frame destroyed.");
			}
		}
	}
}
