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

import <cmath>;
import <format>;
import <string>;
import <string_view>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import :Direct3D12BackBufferParams;
import :Direct3D12Utility;
import :IDirect3D12BackBufferPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 back buffer.
	class Direct3D12BackBuffer final : public IDirect3D12BackBufferPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12BackBuffer.
		/// @param d3d12System Direct3D12 system context.
		/// @param params Direct3D12 back buffer parameters.
		[[nodiscard("Pure constructor")]]
		Direct3D12BackBuffer(IDirect3D12SystemContext& d3d12System, const Direct3D12BackBufferParams& params);
		Direct3D12BackBuffer(const Direct3D12BackBuffer&) = delete;
		Direct3D12BackBuffer(Direct3D12BackBuffer&&) = delete;

		~Direct3D12BackBuffer() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferHandle() const noexcept override;

		/// @brief Sets the name to the back buffer components.
		/// @param name Name to set.
		void Name(std::string_view name);

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

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

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
		d3d12System{&d3d12System},
		currentBackBufferIndex{0u}
	{
		constexpr D3D12_DESCRIPTOR_HEAP_TYPE descHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Set back buffers.");
		backBuffers = params.backBuffers;
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers set.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back buffer descriptor heap.");
		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = descHeapType,
			.NumDescriptors = static_cast<UINT>(backBuffers.size()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(backBufferDescriptorHeap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire back buffer descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffer descriptor heap created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(backBufferDescriptorHeap.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back buffer handles.");
		backBufferHandles.resize(backBuffers.size());
		backBufferHandles[0].ptr = backBufferDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device.GetDescriptorHandleIncrementSize(descHeapType);
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
			PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffer handle at '{}' index created at '{}'.", i, backBufferHandles[i].ptr);
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffer handles created.");
	}

	Direct3D12BackBuffer::~Direct3D12BackBuffer() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back buffer descriptor heap.");
		backBufferDescriptorHeap.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffer descriptor heap released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back buffers.");
		backBuffers.clear();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers released.");
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

	void Direct3D12BackBuffer::Name(const std::string_view name)
	{
		constexpr std::string_view bufferFormat = "{} - Buffer{}";
		constexpr std::string_view heapDescName = " - HeapDescriptor";

		auto componentName = std::string();
		componentName.reserve(name.size() + heapDescName.size());

		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			componentName.resize(std::min(componentName.capacity(), std::formatted_size(bufferFormat, name, i)));
			std::format_to_n(componentName.begin(), componentName.size(), bufferFormat, name, i);
			SetName(*backBuffers[i].Get(), componentName);
		}

		componentName.erase();
		componentName.append(name).append(heapDescName);
		SetName(*backBufferDescriptorHeap.Get(), componentName);
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
