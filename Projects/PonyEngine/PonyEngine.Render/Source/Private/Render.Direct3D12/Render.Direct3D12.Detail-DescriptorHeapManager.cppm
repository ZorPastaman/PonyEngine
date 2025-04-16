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

export module PonyEngine.Render.Direct3D12.Detail:DescriptorHeapManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.Utility;

import :DescriptorHeap;
import :IDescriptorHeapManager;
import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Descriptor heap manager.
	class DescriptorHeapManager final : public IDescriptorHeapManager
	{
	public:
		/// @brief Creates a @p DescriptorHeapManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit DescriptorHeapManager(ISubSystemContext& d3d12System) noexcept;
		[[nodiscard("Pure constructor")]]
		DescriptorHeapManager(const DescriptorHeapManager& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		DescriptorHeapManager(DescriptorHeapManager&& other) noexcept = default;

		~DescriptorHeapManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, std::uint32_t descriptorCount, bool shaderVisible) override;

		/// @brief Cleans out of dead descriptor heaps.
		void Clean() noexcept;

		DescriptorHeapManager& operator =(const DescriptorHeapManager& other) noexcept = default;
		DescriptorHeapManager& operator =(DescriptorHeapManager&& other) noexcept = default;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<DescriptorHeap>> descriptorHeaps; ///< Descriptor heaps.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	DescriptorHeapManager::DescriptorHeapManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<DescriptorHeap> DescriptorHeapManager::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_TYPE heapType, const std::uint32_t descriptorCount, const bool shaderVisible)
	{
		const auto heapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = heapType,
			.NumDescriptors = descriptorCount,
			.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;
		if (const HRESULT result = d3d12System->Device().CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(heap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		const auto descriptorHeap = std::make_shared<DescriptorHeap>(*heap.Get(), d3d12System->Device().GetDescriptorHandleIncrementSize(heapType));
		descriptorHeaps.push_back(descriptorHeap);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Descriptor heap created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(descriptorHeap.get()));

		return descriptorHeap;
	}

	void DescriptorHeapManager::Clean() noexcept
	{
		for (std::size_t i = descriptorHeaps.size(); i-- > 0; )
		{
			if (const std::shared_ptr<DescriptorHeap>& descriptorHeap = descriptorHeaps[i]; descriptorHeap.use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy descriptor heap at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(descriptorHeap.get()));
				descriptorHeaps.erase(descriptorHeaps.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Descriptor heap destroyed.");
			}
		}
	}
}
