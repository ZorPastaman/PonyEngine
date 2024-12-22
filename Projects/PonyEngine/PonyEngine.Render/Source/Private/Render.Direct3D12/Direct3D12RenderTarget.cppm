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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderTarget;

import <string>;
import <string_view>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import :Direct3D12RenderTargetParams;
import :Direct3D12Utility;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render target.
	class Direct3D12RenderTarget final : public IDirect3D12RenderTargetPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12RenderTarget.
		/// @param d3d12System Direct3D12 system context.
		/// @param params Render target parameters.
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderTarget(IDirect3D12SystemContext& d3d12System, const Direct3D12RenderTargetParams& params);
		Direct3D12RenderTarget(const Direct3D12RenderTarget&) = delete;
		Direct3D12RenderTarget(Direct3D12RenderTarget&&) = delete;

		~Direct3D12RenderTarget() noexcept;

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

		Direct3D12RenderTarget& operator =(const Direct3D12RenderTarget&) = delete;
		Direct3D12RenderTarget& operator =(Direct3D12RenderTarget&&) = delete;

	private:
		DXGI_FORMAT rtvFormat; ///< Rtv format.
		DXGI_SAMPLE_DESC rtvSampleDesc; ///< Rtv sample description.

		PonyMath::Utility::Resolution<UINT> resolution; ///< Render target resolution resolution.
		PonyMath::Color::RGBA<FLOAT> clearColor; ///< Clear color.

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12Resource2> renderTargetBuffer; ///< Render target buffer.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap; ///< Rtv descriptor heap.
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle; ///< Rtv handle.
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderTarget::Direct3D12RenderTarget(IDirect3D12SystemContext& d3d12System, const Direct3D12RenderTargetParams& params) :
		rtvFormat{d3d12System.BackBufferPrivate().Format()},
		resolution(params.resolution),
		clearColor(params.clearColor),
		d3d12System{&d3d12System}
	{
		assert(params.msaaParams.sampleQuality >= 0.f && params.msaaParams.sampleQuality <= 1.f && "The msaa sample quality is incorrect.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Get sample description. Count: '{}'; Quality: '{}'; Format: '{}'.", params.msaaParams.sampleCount, params.msaaParams.sampleQuality, static_cast<int>(rtvFormat));
		ID3D12Device10& device = this->d3d12System->Device();
		auto msaaLevels = D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS{.Format = rtvFormat, .SampleCount = static_cast<UINT>(params.msaaParams.sampleCount)};
		if (const HRESULT result = device.CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaLevels, sizeof(msaaLevels)); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get msaa levels with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		rtvSampleDesc = DXGI_SAMPLE_DESC{.Count = msaaLevels.SampleCount, .Quality = PonyMath::Core::RoundToIntegral<float, UINT>((msaaLevels.NumQualityLevels - 1) * params.msaaParams.sampleQuality)};
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Sample description gotten. Count: '{}'; Quality: '{}'.", rtvSampleDesc.Count, rtvSampleDesc.Quality);

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire render target buffer.");
		constexpr auto heapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_DEFAULT,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
		const auto bufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = resolution.Width(),
			.Height = resolution.Height(),
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = rtvFormat,
			.SampleDesc = rtvSampleDesc,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = rtvFormat,
		};
		std::memcpy(clearValue.Color, clearColor.Span().data(), clearColor.ComponentCount * sizeof(FLOAT));
		if (const HRESULT result = device.CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_COMMON, &clearValue,
			nullptr, 0u, nullptr, IID_PPV_ARGS(renderTargetBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire render target buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render target buffer acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderTargetBuffer.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire rtv descriptor heap.");
		constexpr auto rtvDescriptorHeapDesc = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = 1u,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device.CreateDescriptorHeap(&rtvDescriptorHeapDesc, IID_PPV_ARGS(rtvHeap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire rtv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Rtv descriptor heap acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(rtvHeap.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create rtv handle.");
		const auto rtvDesc = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = rtvSampleDesc.Count > 1u ? D3D12_RTV_DIMENSION_TEXTURE2DMS : D3D12_RTV_DIMENSION_TEXTURE2D,
		};
		rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		device.CreateRenderTargetView(renderTargetBuffer.Get(), &rtvDesc, rtvHandle);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Rtv handle created at '0x{:X}'.", rtvHandle.ptr);
	}

	Direct3D12RenderTarget::~Direct3D12RenderTarget() noexcept
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release rtv descriptor heap.");
		rtvHeap.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Rtv descriptor heap released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release render target buffer.");
		renderTargetBuffer.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Render target buffer released.");
	}

	PonyMath::Utility::Resolution<std::uint32_t> Direct3D12RenderTarget::Resolution() const noexcept
	{
		return static_cast<PonyMath::Utility::Resolution<std::uint32_t>>(ResolutionD3D12());
	}

	PonyMath::Color::RGBA<float> Direct3D12RenderTarget::ClearColor() const noexcept
	{
		return static_cast<PonyMath::Color::RGBA<float>>(ClearColorD3D12());
	}

	void Direct3D12RenderTarget::ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept
	{
		ClearColorD3D12(static_cast<PonyMath::Color::RGBA<FLOAT>>(color));
	}

	const PonyMath::Utility::Resolution<UINT>& Direct3D12RenderTarget::ResolutionD3D12() const noexcept
	{
		return resolution;
	}

	const PonyMath::Color::RGBA<FLOAT>& Direct3D12RenderTarget::ClearColorD3D12() const noexcept
	{
		return clearColor;
	}

	void Direct3D12RenderTarget::ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept
	{
		clearColor = color;
	}

	void Direct3D12RenderTarget::Name(const std::string_view name)
	{
		constexpr std::string_view bufferName = " - Buffer";
		constexpr std::string_view heapName = " - ViewHeap";

		auto componentName = std::string();
		componentName.reserve(name.size() + heapName.size());

		componentName.append(name).append(bufferName);
		SetName(*renderTargetBuffer.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(*rtvHeap.Get(), componentName);
	}

	DXGI_FORMAT Direct3D12RenderTarget::Format() const noexcept
	{
		return rtvFormat;
	}

	DXGI_SAMPLE_DESC Direct3D12RenderTarget::SampleDesc() const noexcept
	{
		return rtvSampleDesc;
	}

	ID3D12Resource2& Direct3D12RenderTarget::RenderTargetBuffer() noexcept
	{
		return *renderTargetBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12RenderTarget::RenderTargetBuffer() const noexcept
	{
		return *renderTargetBuffer.Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Direct3D12RenderTarget::RtvHandle() const noexcept
	{
		return rtvHandle;
	}
}
