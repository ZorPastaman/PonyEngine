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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12BackBuffer;

import :Direct3D12BackBufferParams;
import :IDirect3D12BackBufferPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	class Direct3D12BackBuffer final : public IDirect3D12BackBufferPrivate
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12BackBuffer(IDirect3D12SystemContext& d3d12System, const Direct3D12BackBufferParams& params);
		Direct3D12BackBuffer(const Direct3D12BackBuffer&) = delete;
		Direct3D12BackBuffer(Direct3D12BackBuffer&&) = delete;

		~Direct3D12BackBuffer() noexcept = default; ///< TODO: Replace default destructors with destructor with logs

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferHandle() const noexcept override;

		/// @brief Gets the current back buffer index.
		/// @return Current back buffer index.
		[[nodiscard("Pure function")]]
		UINT CurrentBackBufferIndex() const noexcept;
		/// @brief Sets the current back buffer index.
		/// @param index Current back buffer index to set.
		void CurrentBackBufferIndex(UINT index) noexcept;

		Direct3D12BackBuffer& operator =(const Direct3D12BackBuffer&) = delete;
		Direct3D12BackBuffer& operator =(Direct3D12BackBuffer&&) = delete;

	private:
		DXGI_FORMAT backBufferFormat; ///< Back buffer format.

		UINT currentBackBufferIndex; ///< Current back buffer index.

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers; ///< Back buffers.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> backBufferDescriptorHeap; ///< Rtv descriptor heap.
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> backBufferHandles; ///< Rtv handles.
	};
}

namespace PonyEngine::Render
{
	Direct3D12BackBuffer::Direct3D12BackBuffer(IDirect3D12SystemContext& d3d12System, const Direct3D12BackBufferParams& params) :
		backBufferFormat{params.backBufferFormat},
		currentBackBufferIndex{0u}
	{
		backBuffers.resize(params.backBuffers.size());
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			backBuffers[i] = params.backBuffers[i];
		}

		PONY_LOG(d3d12System.Logger(), PonyDebug::Log::LogType::Info, "Create rtv descriptor heap.");
		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = static_cast<UINT>(backBuffers.size()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = d3d12System.Device();
		if (const HRESULT result = device.CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(backBufferDescriptorHeap.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire rtv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(d3d12System.Logger(), PonyDebug::Log::LogType::Info, "Rtv descriptor heap created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(backBufferDescriptorHeap.Get()));

		backBufferHandles.resize(backBuffers.size());
		backBufferHandles[0].ptr = backBufferDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device.GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for (std::size_t i = 1; i < backBufferHandles.size(); ++i)
		{
			backBufferHandles[i].ptr = backBufferHandles[i - 1].ptr + rtvDescriptorHandleIncrement;
		}

		const auto rtvDescription = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = backBufferFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			device.CreateRenderTargetView(backBuffers[i].Get(), &rtvDescription, backBufferHandles[i]);
		}
	}

	DXGI_FORMAT Direct3D12BackBuffer::Format() const noexcept
	{
		return backBufferFormat;
	}

	ID3D12Resource2& Direct3D12BackBuffer::CurrentBackBuffer() noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	const ID3D12Resource2& Direct3D12BackBuffer::CurrentBackBuffer() const noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Direct3D12BackBuffer::CurrentBackBufferHandle() const noexcept
	{
		return backBufferHandles[currentBackBufferIndex];
	}

	UINT Direct3D12BackBuffer::CurrentBackBufferIndex() const noexcept
	{
		return currentBackBufferIndex;
	}

	void Direct3D12BackBuffer::CurrentBackBufferIndex(const UINT index) noexcept
	{
		currentBackBufferIndex = index;
	}
}
