 /***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:RenderTarget;

import <cstring>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.Utility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import :IRenderTargetPrivate;
import :ISubSystemContext;
import :RenderTargetParams;
import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render target.
	class RenderTarget final : public IRenderTargetPrivate
	{
	public:
		/// @brief Creates a @p RenderTarget.
		/// @param d3d12System Direct3D12 system context.
		/// @param params Render target parameters.
		[[nodiscard("Pure constructor")]]
		RenderTarget(ISubSystemContext& d3d12System, const RenderTargetParams& params);
		RenderTarget(const RenderTarget&) = delete;
		RenderTarget(RenderTarget&&) = delete;

		~RenderTarget() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& RenderTargetBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& RenderTargetBuffer() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE RtvHandle() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ID3D12DescriptorHeap& SrvHeap() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12DescriptorHeap& SrvHeap() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual D3D12_GPU_DESCRIPTOR_HANDLE SrvHandle() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2* RenderTargetBufferMsaa() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2* RenderTargetBufferMsaa() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE RtvHandleMsaa() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> ClearColor() const noexcept override;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<UINT>& ResolutionD3D12() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Color::RGBA<FLOAT>& ClearColorD3D12() const noexcept override;
		virtual void ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept override;

		/// @brief Sets the name to the render target components.
		/// @param name Name.
		void Name(std::string_view name);

		RenderTarget& operator =(const RenderTarget&) = delete;
		RenderTarget& operator =(RenderTarget&&) = delete;

	private:
		DXGI_FORMAT rtvFormat; ///< Rtv format.
		DXGI_SAMPLE_DESC rtvSampleDesc; ///< Rtv sample description.

		PonyMath::Utility::Resolution<UINT> resolution; ///< Render target resolution resolution.
		PonyMath::Color::RGBA<FLOAT> clearColor; ///< Clear color.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::shared_ptr<Texture> renderTargetBuffer; ///< Render target buffer.
		std::shared_ptr<DescriptorHeap> rtvHeap; ///< Rtv descriptor heap.
		std::shared_ptr<DescriptorHeap> srvHeap; ///< Srv descriptor heap.

		std::shared_ptr<Texture> msaaRenderTargetBuffer; ///< Msaa render target buffer.
		std::shared_ptr<DescriptorHeap> msaaRtvHeap; ///< Msaa rtv descriptor heap.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RenderTarget::RenderTarget(ISubSystemContext& d3d12System, const RenderTargetParams& params) :
		rtvFormat{d3d12System.BackManager().Format()},
		resolution(params.resolution),
		clearColor(params.clearColor),
		d3d12System{&d3d12System}
	{
		if (params.msaaParams.sampleCount < 1u || params.msaaParams.sampleQuality < 0.f || params.msaaParams.sampleQuality > 1.f) [[unlikely]]
		{
			throw std::invalid_argument(PonyBase::Utility::SafeFormat("Incorrect msaa parameters. SampleCount: '{}'; SampleQuality: '{}'. SampleCount must be greater or equal to 1. SampleQuality must be in the range [0, 1].", 
				params.msaaParams.sampleCount, params.msaaParams.sampleQuality));
		}

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire render target buffer.");
		renderTargetBuffer = this->d3d12System->ResourceManager().CreateRenderTarget(resolution.Width(), resolution.Height(), rtvFormat, DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, clearColor.Span());
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render target buffer acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire rtv descriptor heap.");
		rtvHeap = this->d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1u, false);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Rtv descriptor heap acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create rtv handle.");
		const auto rtvDesc = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		this->d3d12System->Device().CreateRenderTargetView(&renderTargetBuffer->Data(), &rtvDesc, rtvHeap->CpuHandle(0u));
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Rtv handle created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire srv descriptor heap.");
		srvHeap = this->d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1u, true);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srv descriptor heap acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create srv handle.");
		const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D,
			.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
			.Texture2D = D3D12_TEX2D_SRV{.MostDetailedMip = 0u, .MipLevels = 1u, .PlaneSlice = 0u, .ResourceMinLODClamp = 0.f}
		};
		this->d3d12System->Device().CreateShaderResourceView(&renderTargetBuffer->Data(), &srvDesc, srvHeap->CpuHandle(0u));
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srv handle created.");

		if (params.msaaParams.sampleCount <= 1u)
		{
			rtvSampleDesc = DXGI_SAMPLE_DESC{.Count = params.msaaParams.sampleCount, .Quality = 0u};
			PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "No msaa render target buffer created.");

			return;
		}

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Get sample description. Count: '{}'; Quality: '{}'; Format: '{}'.", params.msaaParams.sampleCount, params.msaaParams.sampleQuality, static_cast<int>(rtvFormat));
		auto msaaLevels = D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS{.Format = rtvFormat, .SampleCount = static_cast<UINT>(params.msaaParams.sampleCount)};
		if (const HRESULT result = this->d3d12System->Device().CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaLevels, sizeof(msaaLevels)); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get msaa levels with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		rtvSampleDesc = DXGI_SAMPLE_DESC{.Count = msaaLevels.SampleCount, .Quality = PonyMath::Core::RoundToIntegral<float, UINT>((msaaLevels.NumQualityLevels - 1) * params.msaaParams.sampleQuality)};
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Sample description gotten. Count: '{}'; Quality: '{}'.", rtvSampleDesc.Count, rtvSampleDesc.Quality);

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire msaa render target buffer.");
		msaaRenderTargetBuffer = this->d3d12System->ResourceManager().CreateRenderTarget(resolution.Width(), resolution.Height(), rtvFormat, rtvSampleDesc, clearColor.Span());
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Msaa render target buffer acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire msaa rtv descriptor heap.");
		msaaRtvHeap = this->d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1u, false);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Msaa rtv descriptor heap acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create msaa rtv handle.");
		const auto msaaRtvDesc = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS
		};
		this->d3d12System->Device().CreateRenderTargetView(&msaaRenderTargetBuffer->Data(), &msaaRtvDesc, msaaRtvHeap->CpuHandle(0u));
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Msaa rtv handle created.");
	}

	RenderTarget::~RenderTarget() noexcept
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release msaa rtv descriptor heap.");
		msaaRtvHeap.reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Msaa rtv descriptor heap released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release msaa render target buffer.");
		msaaRenderTargetBuffer.reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Msaa render target buffer released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release rtv descriptor heap.");
		rtvHeap.reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Rtv descriptor heap released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release render target buffer.");
		renderTargetBuffer.reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render target buffer released.");
	}

	PonyMath::Utility::Resolution<std::uint32_t> RenderTarget::Resolution() const noexcept
	{
		return static_cast<PonyMath::Utility::Resolution<std::uint32_t>>(ResolutionD3D12());
	}

	PonyMath::Color::RGBA<float> RenderTarget::ClearColor() const noexcept
	{
		return static_cast<PonyMath::Color::RGBA<float>>(ClearColorD3D12());
	}

	void RenderTarget::ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept
	{
		ClearColorD3D12(static_cast<PonyMath::Color::RGBA<FLOAT>>(color));
	}

	const PonyMath::Utility::Resolution<UINT>& RenderTarget::ResolutionD3D12() const noexcept
	{
		return resolution;
	}

	const PonyMath::Color::RGBA<FLOAT>& RenderTarget::ClearColorD3D12() const noexcept
	{
		return clearColor;
	}

	void RenderTarget::ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept
	{
		clearColor = color;
	}

	void RenderTarget::Name(const std::string_view name)
	{
		constexpr std::string_view bufferName = " - Buffer";
		constexpr std::string_view heapName = " - ViewHeap";
		constexpr std::string_view srvHeapName = " - SrvHeap";
		constexpr std::string_view msaaBufferName = " - BufferMsaa";
		constexpr std::string_view msaaHeapName = " - ViewHeapMsaa";

		auto componentName = std::string();
		componentName.reserve(name.size() + msaaHeapName.size());

		componentName.append(name).append(bufferName);
		SetName(renderTargetBuffer->Data(), componentName);

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(rtvHeap->Heap(), componentName);

		componentName.erase();
		componentName.append(name).append(srvHeapName);
		SetName(srvHeap->Heap(), componentName);

		if (msaaRenderTargetBuffer)
		{
			componentName.erase();
			componentName.append(name).append(msaaBufferName);
			SetName(msaaRenderTargetBuffer->Data(), componentName);
		}

		if (msaaRtvHeap)
		{
			componentName.erase();
			componentName.append(name).append(msaaHeapName);
			SetName(msaaRtvHeap->Heap(), componentName);
		}
	}

	DXGI_FORMAT RenderTarget::Format() const noexcept
	{
		return rtvFormat;
	}

	DXGI_SAMPLE_DESC RenderTarget::SampleDesc() const noexcept
	{
		return rtvSampleDesc;
	}

	ID3D12Resource2& RenderTarget::RenderTargetBuffer() noexcept
	{
		return renderTargetBuffer->Data();
	}

	const ID3D12Resource2& RenderTarget::RenderTargetBuffer() const noexcept
	{
		return renderTargetBuffer->Data();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::RtvHandle() const noexcept
	{
		return rtvHeap->CpuHandle(0u);
	}

	ID3D12DescriptorHeap& RenderTarget::SrvHeap() noexcept
	{
		return srvHeap->Heap();
	}

	const ID3D12DescriptorHeap& RenderTarget::SrvHeap() const noexcept
	{
		return srvHeap->Heap();
	}

	D3D12_GPU_DESCRIPTOR_HANDLE RenderTarget::SrvHandle() const noexcept
	{
		return srvHeap->GpuHandle(0u);
	}

	ID3D12Resource2* RenderTarget::RenderTargetBufferMsaa() noexcept
	{
		return msaaRenderTargetBuffer ? &msaaRenderTargetBuffer->Data() : nullptr;
	}

	const ID3D12Resource2* RenderTarget::RenderTargetBufferMsaa() const noexcept
	{
		return msaaRenderTargetBuffer ? &msaaRenderTargetBuffer->Data() : nullptr;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::RtvHandleMsaa() const noexcept
	{
		return msaaRtvHeap->CpuHandle(0u);
	}
}
