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

export module PonyEngine.Render.Direct3D12.Detail:Back;

import <cmath>;
import <cstddef>;
import <format>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;
import <vector>;

import PonyBase.Utility;

import PonyDebug.Log;

import :BackParams;
import :FormatUtility;
import :IBackPrivate;
import :ISubSystemContext;
import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 back.
	class Back final : public IBackPrivate
	{
	public:
		/// @brief Creates a @p Back.
		/// @param d3d12System Direct3D12 system context.
		/// @param params Direct3D12 Back parameters.
		[[nodiscard("Pure constructor")]]
		Back(ISubSystemContext& d3d12System, const BackParams& params);
		Back(const Back&) = delete;
		Back(Back&&) = delete;

		~Back() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT FormatSrgb() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackViewHandle() const noexcept override;

		/// @brief Sets the name to the back components.
		/// @param name Name to set.
		void Name(std::string_view name);

		/// @brief Gets the current back buffer index.
		/// @return Current back buffer index.
		[[nodiscard("Pure function")]]
		UINT CurrentBackBufferIndex() const noexcept;
		/// @brief Sets the current back buffer index.
		/// @param index Current back buffer index to set.
		void CurrentBackBufferIndex(UINT index) noexcept;

		Back& operator =(const Back&) = delete;
		Back& operator =(Back&&) = delete;

	private:
		DXGI_FORMAT backViewFormat; ///< Back view format.
		DXGI_FORMAT srgbBackViewFormat; ///< Srgb back view format.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		UINT currentBackBufferIndex; ///< Current back buffer index.

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers; ///< Back buffers.
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> backViewHeap; ///< Back view descriptor heap.
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> backViewHandles; ///< Back view handles.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Back::Back(ISubSystemContext& d3d12System, const BackParams& params) :
		backViewFormat{params.backViewFormat},
		srgbBackViewFormat{GetSrgbFormat(backViewFormat)},
		d3d12System{&d3d12System},
		currentBackBufferIndex{0u}
	{
		constexpr D3D12_DESCRIPTOR_HEAP_TYPE descHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Set back buffers.");
		backBuffers = params.backBuffers;
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers set.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back view descriptor heap.");
		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = descHeapType,
			.NumDescriptors = static_cast<UINT>(backBuffers.size()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(backViewHeap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire back view descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back view descriptor heap created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back view handles.");
		backViewHandles.resize(backBuffers.size());
		backViewHandles[0].ptr = backViewHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device.GetDescriptorHandleIncrementSize(descHeapType);
		for (std::size_t i = 1; i < backViewHandles.size(); ++i)
		{
			backViewHandles[i].ptr = backViewHandles[i - 1].ptr + rtvDescriptorHandleIncrement;
		}
		const auto rtvDescription = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = srgbBackViewFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			device.CreateRenderTargetView(backBuffers[i].Get(), &rtvDescription, backViewHandles[i]);
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back view handles created.");
	}

	Back::~Back() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back view descriptor heap.");
		backViewHeap.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back view descriptor heap released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back buffers.");
		backBuffers.clear();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers released.");
	}

	DXGI_FORMAT Back::Format() const noexcept
	{
		return backViewFormat;
	}

	DXGI_FORMAT Back::FormatSrgb() const noexcept
	{
		return srgbBackViewFormat;
	}

	ID3D12Resource2& Back::CurrentBackBuffer() noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	const ID3D12Resource2& Back::CurrentBackBuffer() const noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Back::CurrentBackViewHandle() const noexcept
	{
		return backViewHandles[currentBackBufferIndex];
	}

	void Back::Name(const std::string_view name)
	{
		constexpr std::string_view bufferFormat = "{} - Buffer{}";
		constexpr std::string_view heapDescName = " - ViewHeap";

		auto componentName = std::string();
		componentName.reserve(name.size() + bufferFormat.size() + 3);

		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			componentName.resize(std::min(componentName.capacity(), std::formatted_size(bufferFormat, name, i)));
			std::format_to_n(componentName.begin(), componentName.size(), bufferFormat, name, i);
			SetName(*backBuffers[i].Get(), componentName);
		}

		componentName.erase();
		componentName.append(name).append(heapDescName);
		SetName(*backViewHeap.Get(), componentName);
	}

	UINT Back::CurrentBackBufferIndex() const noexcept
	{
		return currentBackBufferIndex;
	}

	void Back::CurrentBackBufferIndex(const UINT index) noexcept
	{
		currentBackBufferIndex = index;
	}
}
