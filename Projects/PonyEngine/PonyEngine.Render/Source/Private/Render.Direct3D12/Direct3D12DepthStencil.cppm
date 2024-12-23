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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12DepthStencil;

import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Utility;

import PonyDebug.Log;

import :Direct3D12RenderTargetParams;
import :Direct3D12Utility;
import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 depth stencil.
	class Direct3D12DepthStencil final : public IDirect3D12DepthStencilPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12DepthStencil.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12DepthStencil(IDirect3D12SystemContext& d3d12System);
		[[nodiscard("Pure constructor")]]
		Direct3D12DepthStencil(const Direct3D12DepthStencil& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12DepthStencil(Direct3D12DepthStencil&& other) noexcept = default;

		~Direct3D12DepthStencil() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT DsvFormat() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& DepthStencilBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& DepthStencilBuffer() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE DsvHandle() const noexcept override;

		/// @brief Sets the name to the depth stencil components.
		/// @param name Name.
		void Name(std::string_view name);

		Direct3D12DepthStencil& operator =(const Direct3D12DepthStencil& other) noexcept = default;
		Direct3D12DepthStencil& operator =(Direct3D12DepthStencil&& other) noexcept = default;

	private:
		static constexpr DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT; ///< Depth stencil format.

		IDirect3D12SystemContext* d3d12System; ///< Render system context.

		Microsoft::WRL::ComPtr<ID3D12Resource2> depthStencilBuffer; ///< Depth stencil buffer.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap; ///< Depth stencil view heap.
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle; ///< Depth stencil view handle.
	};
}

namespace PonyEngine::Render
{
	Direct3D12DepthStencil::Direct3D12DepthStencil(IDirect3D12SystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire depth stencil buffer.");
		constexpr auto heapProperties = D3D12_HEAP_PROPERTIES
		{
			.Type = D3D12_HEAP_TYPE_DEFAULT,
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
		const IDirect3D12RenderTargetPrivate& renderTarget = d3d12System.RenderTargetPrivate();
		const PonyMath::Utility::Resolution<UINT>& resolution = renderTarget.ResolutionD3D12();
		const DXGI_SAMPLE_DESC sampleDesc = renderTarget.SampleDesc();
		const auto bufferDesc = D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
			.Width = resolution.Width(),
			.Height = resolution.Height(),
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DepthStencilFormat,
			.SampleDesc = sampleDesc,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		constexpr auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = DepthStencilFormat,
			.DepthStencil = D3D12_DEPTH_STENCIL_VALUE{.Depth = D3D12_MAX_DEPTH, .Stencil = 0u}
		};
		ID3D12Device10& device = d3d12System.Device();
		if (const HRESULT result = device.CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ, &clearValue, 
			nullptr, 0u, nullptr, IID_PPV_ARGS(depthStencilBuffer.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire depth stencil buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil buffer acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire dsv descriptor heap.");
		constexpr auto dsvDescriptorHeapDesc = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
			.NumDescriptors = 1u,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device.CreateDescriptorHeap(&dsvDescriptorHeapDesc, IID_PPV_ARGS(dsvHeap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire dsv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Dsv descriptor heap acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create depth stencil handle.");
		const auto dsvDesc = D3D12_DEPTH_STENCIL_VIEW_DESC
		{
			.Format = DepthStencilFormat,
			.ViewDimension = sampleDesc.Count > 1u ? D3D12_DSV_DIMENSION_TEXTURE2DMS : D3D12_DSV_DIMENSION_TEXTURE2D,
			.Flags = D3D12_DSV_FLAG_NONE
		};
		dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
		device.CreateDepthStencilView(depthStencilBuffer.Get(), &dsvDesc, dsvHandle);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil handle created.");
	}

	Direct3D12DepthStencil::~Direct3D12DepthStencil() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release dsv descriptor heap.");
		dsvHeap.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Dsv descriptor heap released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release depth stencil buffer.");
		depthStencilBuffer.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil buffer released.");
	}

	DXGI_FORMAT Direct3D12DepthStencil::DsvFormat() const noexcept
	{
		return DepthStencilFormat;
	}

	ID3D12Resource2& Direct3D12DepthStencil::DepthStencilBuffer() noexcept
	{
		return *depthStencilBuffer.Get();
	}

	const ID3D12Resource2& Direct3D12DepthStencil::DepthStencilBuffer() const noexcept
	{
		return *depthStencilBuffer.Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Direct3D12DepthStencil::DsvHandle() const noexcept
	{
		return dsvHandle;
	}

	void Direct3D12DepthStencil::Name(const std::string_view name)
	{
		constexpr std::string_view bufferName = " - Buffer";
		constexpr std::string_view heapName = " - ViewHeap";

		auto componentName = std::string();
		componentName.reserve(name.size() + heapName.size());

		componentName.append(name).append(bufferName);
		SetName(*depthStencilBuffer.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(*dsvHeap.Get(), componentName);
	}
}
