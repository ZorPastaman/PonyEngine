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

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.Utility;

import PonyMath.Color;
import PonyMath.Utility;

import PonyDebug.Log;

import :Attachment;
import :FormatUtility;
import :Frame;
import :FrameParams;
import :IFrameManager;
import :ISubSystemContext;
import :View;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 frame manager.
	class FrameManager final : public IFrameManager
	{
	public:
		/// @brief Creates a frame manager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit FrameManager(ISubSystemContext& d3d12System);
		FrameManager(const FrameManager&) = delete;
		FrameManager(FrameManager&&) = delete;

		~FrameManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual FrameParams ConvertFrameParams(const Render::FrameParams& frameParams) const override;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Frame> CreateFrame(const FrameParams& frameParams) override;

		/// @brief Cleans out of dead frames.
		void Clean() noexcept;

		FrameManager& operator =(const FrameManager&) = delete;
		FrameManager& operator =(FrameManager&&) = delete;

	private:
		/// @brief Throws if the @p format doesn't support features @p support1 and @p support2.
		/// @param format Format.
		/// @param support1 Support1.
		/// @param support2 Support2.
		void CheckFormat(DXGI_FORMAT format, D3D12_FORMAT_SUPPORT1 support1, D3D12_FORMAT_SUPPORT2 support2) const;

		/// @brief Creates textures required by the @p frameParams.
		/// @param frameParams Frame parameters.
		/// @param renderTarget Render target.
		/// @param resolve Resolve.
		/// @param depthStencil Depth stencil.
		void CreateTextures(const FrameParams& frameParams, std::shared_ptr<Texture>& renderTarget, std::shared_ptr<Texture>& resolve, std::shared_ptr<Texture>& depthStencil) const;
		/// @brief Creates heaps for the textures.
		/// @param renderTarget Render target.
		/// @param depthStencil Depth stencil.
		/// @param rtvHeap Render target view heap.
		/// @param srvHeap Shader resource view heap.
		/// @param dsvHeap Depth stencil view heap.
		/// @param rtvHeapSize Render target heap size.
		/// @param srvHeapSize Shader resource view heap size.
		/// @param dsvHeapSize Depth stencil view heap size.
		void CreateHeaps(const Texture* renderTarget, const Texture* depthStencil,
			std::shared_ptr<DescriptorHeap>& rtvHeap, std::shared_ptr<DescriptorHeap>& srvHeap, std::shared_ptr<DescriptorHeap>& dsvHeap,
			std::uint32_t& rtvHeapSize, std::uint32_t& srvHeapSize, std::uint32_t& dsvHeapSize) const;
		/// @brief Creates view for the textures by the @p frameParams.
		/// @param frameParams Frame parameters.
		/// @param renderTarget Render target.
		/// @param resolve Resolve.
		/// @param depthStencil Depth stencil.
		/// @param rtvHeap Render target view heap.
		/// @param srvHeap Shader resource view heap.
		/// @param dsvHeap Depth stencil view heap.
		/// @param renderTargetIndex Render target view index.
		/// @param outputIndex Output view index.
		/// @param depthStencilIndex Depth stencil view index.
		void CreateViews(const FrameParams& frameParams, Texture* renderTarget, Texture* resolve, Texture* depthStencil, DescriptorHeap* rtvHeap, DescriptorHeap* srvHeap, DescriptorHeap* dsvHeap,
			std::uint32_t& renderTargetIndex, std::uint32_t& outputIndex, std::uint32_t& depthStencilIndex) const;

		/// @brief Creates a texture map for a frame.
		/// @param renderTarget Render target.
		/// @param resolve Resolve.
		/// @param depthStencil Depth stencil.
		/// @return Map of an attachment to a texture.
		[[nodiscard("Weird call")]]
		static std::unordered_map<Attachment, std::shared_ptr<Texture>> CreateTextureData(std::shared_ptr<Texture>&& renderTarget, std::shared_ptr<Texture>&& resolve, std::shared_ptr<Texture>&& depthStencil);
		/// @brief Creates a heap map for a frame.
		/// @param renderTarget Render target.
		/// @param depthStencil Depth stencil.
		/// @param rtvHeap Render target view heap.
		/// @param srvHeap Shader resource view heap.
		/// @param dsvHeap Depth stencil view heap.
		/// @return Map of a view to a heap.
		[[nodiscard("Weird call")]]
		static std::unordered_map<View, std::shared_ptr<DescriptorHeap>> CreateHeapData(const Texture* renderTarget, const Texture* depthStencil, 
			std::shared_ptr<DescriptorHeap>&& rtvHeap, std::shared_ptr<DescriptorHeap>&& srvHeap, std::shared_ptr<DescriptorHeap>&& dsvHeap);
		/// @brief Creates a handle map for a frame.
		/// @param renderTarget Render target.
		/// @param depthStencil Depth stencil.
		/// @param renderTargetIndex Render target view index.
		/// @param outputIndex Output view index.
		/// @param depthStencilIndex Depth stencil view index.
		/// @return Map of a view to a handle index.
		[[nodiscard("Weird call")]]
		static std::unordered_map<View, std::uint32_t> CreateHandleData(const Texture* renderTarget, const Texture* depthStencil,
			std::uint32_t renderTargetIndex, std::uint32_t outputIndex, std::uint32_t depthStencilIndex);

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Frame>> frames; ///< Frames.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	FrameManager::FrameManager(ISubSystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
		frames.reserve(8);
	}

	FrameParams FrameManager::ConvertFrameParams(const Render::FrameParams& frameParams) const
	{
		auto answer = FrameParams
		{
			.resolution = frameParams.resolution,
			.clearColor = frameParams.clearColor,
			.clearDepth = frameParams.clearDepth,
			.clearStencil = frameParams.clearStencil,
			.rtvFormat = GetD3D12Format(frameParams.rtvFormat),
			.dsvFormat = GetD3D12Format(frameParams.dsvFormat)
		};

		if (answer.rtvFormat != DXGI_FORMAT_UNKNOWN)
		{
			CheckFormat(answer.rtvFormat, D3D12_FORMAT_SUPPORT1_RENDER_TARGET, D3D12_FORMAT_SUPPORT2_NONE);
		}
		if (answer.dsvFormat != DXGI_FORMAT_UNKNOWN)
		{
			CheckFormat(answer.dsvFormat, D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL, D3D12_FORMAT_SUPPORT2_NONE);
		}

		if (answer.rtvFormat != DXGI_FORMAT_UNKNOWN && frameParams.msaa.sampleCount > 1u)
		{
			if (frameParams.msaa.sampleCount < 1u || frameParams.msaa.sampleQuality < 0.f || frameParams.msaa.sampleQuality > 1.f) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Incorrect msaa parameters. SampleCount: '{}'; SampleQuality: '{}'. SampleCount must be greater or equal to 1. SampleQuality must be in the range [0, 1].",
					frameParams.msaa.sampleCount, frameParams.msaa.sampleQuality));
			}
			auto msaaLevels = D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS{.Format = answer.rtvFormat, .SampleCount = static_cast<UINT>(frameParams.msaa.sampleCount)};
			if (const HRESULT result = this->d3d12System->Device().CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaLevels, sizeof(msaaLevels)); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get msaa levels with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			if (msaaLevels.NumQualityLevels < 1u) [[unlikely]]
			{
				throw std::runtime_error("Unsupported msaa sample count.");
			}
			answer.sampleDesc = DXGI_SAMPLE_DESC{.Count = msaaLevels.SampleCount, .Quality = PonyMath::Core::RoundToIntegral<float, UINT>((msaaLevels.NumQualityLevels - 1) * frameParams.msaa.sampleQuality)};
		}
		else
		{
			answer.sampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u};
		}

		return answer;
	}

	std::shared_ptr<Frame> FrameManager::CreateFrame(const FrameParams& frameParams)
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create textures.");
		std::shared_ptr<Texture> renderTarget, resolve, depthStencil;
		CreateTextures(frameParams, renderTarget, resolve, depthStencil);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Textures created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create heaps.");
		std::shared_ptr<DescriptorHeap> rtvHeap, srvHeap, dsvHeap;
		std::uint32_t rtvHeapSize, srvHeapSize, dsvHeapSize;
		CreateHeaps(renderTarget.get(), depthStencil.get(), rtvHeap, srvHeap, dsvHeap, rtvHeapSize, srvHeapSize, dsvHeapSize);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Heaps created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create views.");
		std::uint32_t renderTargetIndex, outputIndex, depthStencilIndex;
		CreateViews(frameParams, renderTarget.get(), resolve.get(), depthStencil.get(), rtvHeap.get(), srvHeap.get(), dsvHeap.get(), 
			renderTargetIndex, outputIndex, depthStencilIndex);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Views created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create frame data.");
		std::unordered_map<View, std::shared_ptr<DescriptorHeap>> heaps = CreateHeapData(renderTarget.get(), depthStencil.get(), std::move(rtvHeap), std::move(srvHeap), std::move(dsvHeap));
		std::unordered_map<View, std::uint32_t> handles = CreateHandleData(renderTarget.get(), depthStencil.get(), renderTargetIndex, outputIndex, depthStencilIndex);
		std::unordered_map<Attachment, std::shared_ptr<Texture>> textures = CreateTextureData(std::move(renderTarget), std::move(resolve), std::move(depthStencil));
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Frame data created.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create frame.");
		const auto frame = std::make_shared<Frame>(std::move(textures), std::move(heaps), std::move(handles));
		frames.push_back(frame);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Frame created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(frame.get()));

		return frame;
	}

	void FrameManager::Clean() noexcept
	{
		for (std::size_t i = frames.size(); i-- > 0; )
		{
			if (const std::shared_ptr<Frame>& frame = frames[i]; frame.use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy frame at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(frame.get()));
				frames.erase(frames.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Frame destroyed.");
			}
		}
	}

	void FrameManager::CheckFormat(const DXGI_FORMAT format, const D3D12_FORMAT_SUPPORT1 support1, const D3D12_FORMAT_SUPPORT2 support2) const
	{
		auto formatSupport = D3D12_FEATURE_DATA_FORMAT_SUPPORT{.Format = format};
		if (const HRESULT result = this->d3d12System->Device().CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &formatSupport, sizeof(formatSupport)); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to format support with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if ((formatSupport.Support1 & support1) != support1 || (formatSupport.Support2 & support2) != support2) [[unlikely]]
		{
			throw std::invalid_argument("Unsupported format.");
		}
	}

	void FrameManager::CreateTextures(const FrameParams& frameParams, std::shared_ptr<Texture>& renderTarget, std::shared_ptr<Texture>& resolve, std::shared_ptr<Texture>& depthStencil) const
	{
		if (frameParams.rtvFormat != DXGI_FORMAT_UNKNOWN)
		{
			renderTarget = d3d12System->ResourceManager().CreateRenderTarget(frameParams.resolution.Width(), frameParams.resolution.Height(), frameParams.rtvFormat, frameParams.sampleDesc, frameParams.clearColor);

			if (frameParams.sampleDesc.Count > 1u)
			{
				resolve = d3d12System->ResourceManager().CreateRenderTarget(frameParams.resolution.Width(), frameParams.resolution.Height(), frameParams.rtvFormat, DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, frameParams.clearColor);
			}
		}

		if (frameParams.dsvFormat != DXGI_FORMAT_UNKNOWN)
		{
			depthStencil = d3d12System->ResourceManager().CreateDepthStencil(frameParams.resolution.Width(), frameParams.resolution.Height(), frameParams.dsvFormat, frameParams.sampleDesc, D3D12_DEPTH_STENCIL_VALUE{.Depth = frameParams.clearDepth, .Stencil = frameParams.clearStencil});
		}
	}

	void FrameManager::CreateHeaps(const Texture* const renderTarget, const Texture* const depthStencil,
		std::shared_ptr<DescriptorHeap>& rtvHeap, std::shared_ptr<DescriptorHeap>& srvHeap, std::shared_ptr<DescriptorHeap>& dsvHeap,
		std::uint32_t& rtvHeapSize, std::uint32_t& srvHeapSize, std::uint32_t& dsvHeapSize) const
	{
		rtvHeapSize = renderTarget != nullptr;
		srvHeapSize = renderTarget != nullptr;
		dsvHeapSize = depthStencil != nullptr;

		if (rtvHeapSize > 0)
		{
			rtvHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, rtvHeapSize, false);
		}

		if (srvHeapSize > 0)
		{
			srvHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, srvHeapSize, true);
		}

		if (dsvHeapSize > 0)
		{
			dsvHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, dsvHeapSize, false);
		}
	}

	void FrameManager::CreateViews(const FrameParams& frameParams, Texture* const renderTarget, Texture* const resolve, Texture* const depthStencil, DescriptorHeap* const rtvHeap, DescriptorHeap* const srvHeap, DescriptorHeap* const dsvHeap,
		std::uint32_t& renderTargetIndex, std::uint32_t& outputIndex, std::uint32_t& depthStencilIndex) const
	{
		std::uint32_t rtvHeapIndex = 0u;
		std::uint32_t srvHeapIndex = 0u;
		std::uint32_t dsvHeapIndex = 0u;

		if (renderTarget)
		{
			renderTargetIndex = rtvHeapIndex++;
			const auto rtvDesc = D3D12_RENDER_TARGET_VIEW_DESC
			{
				.Format = frameParams.rtvFormat,
				.ViewDimension = frameParams.sampleDesc.Count > 1u ? D3D12_RTV_DIMENSION_TEXTURE2DMS : D3D12_RTV_DIMENSION_TEXTURE2D
			};
			d3d12System->Device().CreateRenderTargetView(&renderTarget->Data(), &rtvDesc, rtvHeap->CpuHandle(renderTargetIndex));

			outputIndex = srvHeapIndex++;
			const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
			{
				.Format = frameParams.rtvFormat,
				.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D,
				.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
				.Texture2D = D3D12_TEX2D_SRV{.MostDetailedMip = 0u, .MipLevels = 1u, .PlaneSlice = 0u, .ResourceMinLODClamp = 0.f}
			};
			d3d12System->Device().CreateShaderResourceView(resolve ? &resolve->Data() : &renderTarget->Data(), &srvDesc, srvHeap->CpuHandle(outputIndex));
		}

		if (depthStencil)
		{
			depthStencilIndex = dsvHeapIndex++;
			const auto dsvDesc = D3D12_DEPTH_STENCIL_VIEW_DESC
			{
				.Format = frameParams.dsvFormat,
				.ViewDimension = frameParams.sampleDesc.Count > 1u ? D3D12_DSV_DIMENSION_TEXTURE2DMS : D3D12_DSV_DIMENSION_TEXTURE2D,
				.Flags = D3D12_DSV_FLAG_NONE
			};
			d3d12System->Device().CreateDepthStencilView(&depthStencil->Data(), &dsvDesc, dsvHeap->CpuHandle(depthStencilIndex));
		}
	}

	std::unordered_map<Attachment, std::shared_ptr<Texture>> FrameManager::CreateTextureData(std::shared_ptr<Texture>&& renderTarget, std::shared_ptr<Texture>&& resolve, std::shared_ptr<Texture>&& depthStencil)
	{
		const std::size_t textureCount = (renderTarget != nullptr) + (resolve != nullptr) + (depthStencil != nullptr);
		std::unordered_map<Attachment, std::shared_ptr<Texture>> textures;
		textures.reserve(textureCount);

		if (renderTarget)
		{
			textures[Attachment::RenderTarget] = std::move(renderTarget);
		}

		if (resolve)
		{
			textures[Attachment::Resolve] = std::move(resolve);
		}

		if (depthStencil)
		{
			textures[Attachment::DepthStencil] = std::move(depthStencil);
		}

		return textures;
	}

	std::unordered_map<View, std::shared_ptr<DescriptorHeap>> FrameManager::CreateHeapData(const Texture* const renderTarget, const Texture* const depthStencil,
		std::shared_ptr<DescriptorHeap>&& rtvHeap, std::shared_ptr<DescriptorHeap>&& srvHeap, std::shared_ptr<DescriptorHeap>&& dsvHeap)
	{
		const std::size_t heapCount = (renderTarget != nullptr) * 2 + (depthStencil != nullptr);
		std::unordered_map<View, std::shared_ptr<DescriptorHeap>> heaps;
		heaps.reserve(heapCount);

		if (renderTarget)
		{
			heaps[View::RenderTarget] = std::move(rtvHeap);
			heaps[View::Output] = std::move(srvHeap);
		}

		if (depthStencil)
		{
			heaps[View::DepthStencil] = std::move(dsvHeap);
		}

		return heaps;
	}

	std::unordered_map<View, std::uint32_t> FrameManager::CreateHandleData(const Texture* const renderTarget, const Texture* const depthStencil,
		const std::uint32_t renderTargetIndex, const std::uint32_t outputIndex, const std::uint32_t depthStencilIndex)
	{
		const std::size_t handleCount = (renderTarget != nullptr) * 2 + (depthStencil != nullptr);
		std::unordered_map<View, std::uint32_t> handles;
		handles.reserve(handleCount);

		if (renderTarget)
		{
			handles[View::RenderTarget] = renderTargetIndex;
			handles[View::Output] = outputIndex;
		}

		if (depthStencil)
		{
			handles[View::DepthStencil] = depthStencilIndex;
		}

		return handles;
	}
}
