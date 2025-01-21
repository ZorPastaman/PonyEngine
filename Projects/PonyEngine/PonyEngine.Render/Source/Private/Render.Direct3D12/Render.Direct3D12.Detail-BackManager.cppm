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

export module PonyEngine.Render.Direct3D12.Detail:BackManager;

import <algorithm>;
import <cmath>;
import <cstddef>;
import <format>;
import <memory>;
import <string>;
import <string_view>;
import <vector>;

import PonyDebug.Log;

import :BackParams;
import :DescriptorHeap;
import :FormatUtility;
import :IBackManager;
import :ISubSystemContext;
import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 back manager.
	class BackManager final : public IBackManager
	{
	public:
		/// @brief Creates a @p BackManager.
		/// @param d3d12System Direct3D12 system context.
		/// @param params Direct3D12 Back parameters.
		[[nodiscard("Pure constructor")]]
		BackManager(ISubSystemContext& d3d12System, const BackParams& params);
		BackManager(const BackManager&) = delete;
		BackManager(BackManager&&) = delete;

		~BackManager() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT FormatSrgb() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackHandle() const noexcept override;

		/// @brief Gets the current back buffer index.
		/// @return Current back buffer index.
		[[nodiscard("Pure function")]]
		UINT CurrentBackBufferIndex() const noexcept;
		/// @brief Sets the current back buffer index.
		/// @param index Current back buffer index to set.
		void CurrentBackBufferIndex(UINT index) noexcept;

		/// @brief Sets the name to the back components.
		/// @param name Name to set.
		void Name(std::string_view name);

		BackManager& operator =(const BackManager&) = delete;
		BackManager& operator =(BackManager&&) = delete;

	private:
		DXGI_FORMAT backFormat; ///< Back format.
		DXGI_FORMAT srgbBackFormat; ///< Srgb back format.
		UINT currentBackBufferIndex; ///< Current back buffer index.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers; ///< Back buffers.
		std::shared_ptr<DescriptorHeap> backHeap; ///< Back descriptor heap.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	BackManager::BackManager(ISubSystemContext& d3d12System, const BackParams& params) :
		currentBackBufferIndex{0u},
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Set back buffers.");
		backBuffers = params.backBuffers;
		assert(!backBuffers.empty() && "The back buffers array can't be empty");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers set.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Get back buffer format.");
		backFormat = backBuffers[0]->GetDesc1().Format;
		assert(std::ranges::find_if(backBuffers, [&](const Microsoft::WRL::ComPtr<ID3D12Resource2>& buffer) { return buffer->GetDesc1().Format != backFormat; }) == backBuffers.cend() && "The back buffers must have the same format.");
		srgbBackFormat = GetSrgbFormat(backFormat);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffer format gotten. Format: {}; Srgb format: {}.", static_cast<int>(backFormat), static_cast<int>(srgbBackFormat));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back descriptor heap.");
		backHeap = this->d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, static_cast<UINT>(backBuffers.size()), false);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back descriptor heap created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back handles.");
		const auto rtvDesc = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = srgbBackFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		for (UINT i = 0u; i < backBuffers.size(); ++i)
		{
			this->d3d12System->Device().CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, backHeap->CpuHandle(i));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back handles created.");
	}

	BackManager::~BackManager() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back descriptor heap.");
		backHeap.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back descriptor heap released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back buffers.");
		backBuffers.clear();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers released.");
	}

	DXGI_FORMAT BackManager::Format() const noexcept
	{
		return backFormat;
	}

	DXGI_FORMAT BackManager::FormatSrgb() const noexcept
	{
		return srgbBackFormat;
	}

	ID3D12Resource2& BackManager::CurrentBackBuffer() noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	const ID3D12Resource2& BackManager::CurrentBackBuffer() const noexcept
	{
		return *backBuffers[currentBackBufferIndex].Get();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE BackManager::CurrentBackHandle() const noexcept
	{
		return backHeap->CpuHandle(currentBackBufferIndex);
	}

	UINT BackManager::CurrentBackBufferIndex() const noexcept
	{
		return currentBackBufferIndex;
	}

	void BackManager::CurrentBackBufferIndex(const UINT index) noexcept
	{
		currentBackBufferIndex = index;
	}

	void BackManager::Name(const std::string_view name)
	{
		constexpr std::string_view bufferFormat = "{} - Buffer{}";
		constexpr std::string_view heapName = " - Heap";

		auto componentName = std::string();
		componentName.reserve(name.size() + bufferFormat.size());

		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			componentName.resize(std::min(componentName.capacity(), std::formatted_size(bufferFormat, name, i)));
			std::format_to_n(componentName.begin(), componentName.size(), bufferFormat, name, i);
			SetName(*backBuffers[i].Get(), componentName);
		}

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(backHeap->Heap(), componentName);
	}
}
