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
import <cstddef>;
import <format>;
import <memory>;
import <optional>;
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
		virtual ID3D12Resource2* CurrentBackBuffer() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2* CurrentBackBuffer() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> CurrentRtvHandle() const noexcept override;

		/// @brief Gets the current back buffer index.
		/// @return Current back buffer index.
		[[nodiscard("Pure function")]]
		std::uint32_t CurrentBackBufferIndex() const noexcept;
		/// @brief Sets the current back buffer index.
		/// @param index Current back buffer index to set.
		void CurrentBackBufferIndex(std::uint32_t index) noexcept;

		/// @brief Sets the name to the back components.
		/// @param name Name to set.
		void Name(std::string_view name);

		BackManager& operator =(const BackManager&) = delete;
		BackManager& operator =(BackManager&&) = delete;

	private:
		DXGI_FORMAT backFormat; ///< Back format.
		DXGI_FORMAT srgbBackFormat; ///< Srgb back format.
		std::uint32_t currentBackBufferIndex; ///< Current back buffer index.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers; ///< Back buffers.
		std::shared_ptr<DescriptorHeap> rtvHeap; ///< Rtv descriptor heap.
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
		assert(std::ranges::find(backBuffers, nullptr) == backBuffers.cend() && "The back buffers have a nullptr element.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffers set.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Get back buffer formats.");
		backFormat = backBuffers.size() > 0 ? backBuffers[0]->GetDesc1().Format : DXGI_FORMAT_UNKNOWN;
		assert(std::ranges::find_if(backBuffers, [&](const Microsoft::WRL::ComPtr<ID3D12Resource2>& buffer) { return buffer->GetDesc1().Format != backFormat; }) == backBuffers.cend() && "The back buffers must have the same format.");
		srgbBackFormat = backFormat != DXGI_FORMAT_UNKNOWN ? GetSrgbFormat(backFormat) : DXGI_FORMAT_UNKNOWN;
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back buffer formats gotten. Format: {}; sRGB format: {}.", static_cast<int>(backFormat), static_cast<int>(srgbBackFormat));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back descriptor heap.");
		rtvHeap = this->d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, static_cast<std::uint32_t>(backBuffers.size()), false);
		assert(rtvHeap && "The back rtv heap is nullptr.");
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back descriptor heap created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create back handles.");
		const auto rtvDesc = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = srgbBackFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		for (std::uint32_t i = 0u; i < backBuffers.size(); ++i)
		{
			this->d3d12System->Device().CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHeap->CpuHandle(i));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back handles created.");
	}

	BackManager::~BackManager() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release back rtv heap.");
		rtvHeap.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Back rtv heap released.");

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

	ID3D12Resource2* BackManager::CurrentBackBuffer() noexcept
	{
		return backBuffers.size() > 0 ? backBuffers[currentBackBufferIndex].Get() : nullptr;
	}

	const ID3D12Resource2* BackManager::CurrentBackBuffer() const noexcept
	{
		return backBuffers.size() > 0 ? backBuffers[currentBackBufferIndex].Get() : nullptr;
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> BackManager::CurrentRtvHandle() const noexcept
	{
		return backBuffers.size() > 0 ? std::optional(rtvHeap->CpuHandle(currentBackBufferIndex)) : std::nullopt;
	}

	std::uint32_t BackManager::CurrentBackBufferIndex() const noexcept
	{
		return currentBackBufferIndex;
	}

	void BackManager::CurrentBackBufferIndex(const std::uint32_t index) noexcept
	{
		currentBackBufferIndex = index;
	}

	void BackManager::Name(const std::string_view name)
	{
		constexpr std::string_view bufferFormat = "{}-{}";

		auto bufferName = std::string();
		bufferName.reserve(name.size() + bufferFormat.size());
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			bufferName.resize(std::formatted_size(bufferFormat, name, i));
			std::format_to_n(bufferName.begin(), bufferName.size(), bufferFormat, name, i);
			SetName(*backBuffers[i].Get(), bufferName);
		}

		rtvHeap->Name(name);
	}
}
