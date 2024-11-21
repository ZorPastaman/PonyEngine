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
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Render.Detail;

import :Direct3D12Constants;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 depth stencil.
	class Direct3D12DepthStencil final
	{
	public:
		/// @brief Creates a @p Direct3D12DepthStencil.
		/// @param render Render context.
		/// @param device Render device.
		/// @param resolution Render resolution.
		Direct3D12DepthStencil(IRenderContext& render, ID3D12Device10& device, const PonyMath::Utility::Resolution<UINT>& resolution);
		Direct3D12DepthStencil(const Direct3D12DepthStencil&) = delete;
		Direct3D12DepthStencil(Direct3D12DepthStencil&&) = delete;

		~Direct3D12DepthStencil() noexcept;

		/// @brief Gets the depth stencil view handle.
		/// @return Depth stencil view handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE DsvHandle() const noexcept;

		Direct3D12DepthStencil& operator =(const Direct3D12DepthStencil&) = delete;
		Direct3D12DepthStencil& operator =(Direct3D12DepthStencil&&) = delete;

	private:
		IRenderContext* render; ///< Render context.

		Microsoft::WRL::ComPtr<ID3D12Resource2> depthStencilBuffer; ///< Depth stencil buffer.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap; ///< Depth stencil view heap.
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle; ///< Depth stencil view handle.
	};
}

namespace PonyEngine::Render
{
	Direct3D12DepthStencil::Direct3D12DepthStencil(IRenderContext& render, ID3D12Device10& device, const PonyMath::Utility::Resolution<UINT>& resolution) :
		render{&render}
	{
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Acquire depth stencil buffer. Resolution: '{}'; Format: '{}'.", resolution.ToString(), static_cast<std::underlying_type_t<DXGI_FORMAT>>(DepthStencilFormat));
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
			.Format = DepthStencilFormat,
			.SampleDesc = SampleDescription,
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
		constexpr auto clearValue = D3D12_CLEAR_VALUE
		{
			.Format = DepthStencilFormat,
			.DepthStencil = D3D12_DEPTH_STENCIL_VALUE{.Depth = D3D12_MAX_DEPTH, .Stencil = 0u}
		};
		if (const HRESULT result = device.CreateCommittedResource3(&heapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE, &clearValue, 
			nullptr, 0u, nullptr, IID_PPV_ARGS(depthStencilBuffer.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 depth stencil buffer with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil buffer acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(depthStencilBuffer.Get()));

		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Acquire dsv heap.");
		constexpr auto dsvDescriptorHeapDesc = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
			.NumDescriptors = 1u,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device.CreateDescriptorHeap(&dsvDescriptorHeapDesc, IID_PPV_ARGS(dsvHeap.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire dsv heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Dsv heap acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(dsvHeap.Get()));

		constexpr auto dsvDesc = D3D12_DEPTH_STENCIL_VIEW_DESC
		{
			.Format = DepthStencilFormat,
			.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D,
			.Flags = D3D12_DSV_FLAG_NONE
		};
		dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
		device.CreateDepthStencilView(depthStencilBuffer.Get(), &dsvDesc, dsvHandle);
	}

	Direct3D12DepthStencil::~Direct3D12DepthStencil() noexcept
	{
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Release dsv heap.");
		dsvHeap.Reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Dsv heap released.");

		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Release depth stencil buffer.");
		depthStencilBuffer.Reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil buffer released.");
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Direct3D12DepthStencil::DsvHandle() const noexcept
	{
		return dsvHandle;
	}
}
