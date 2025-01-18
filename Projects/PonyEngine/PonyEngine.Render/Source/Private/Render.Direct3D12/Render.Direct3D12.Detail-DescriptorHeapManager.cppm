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

export module PonyEngine.Render.Direct3D12.Detail:DescriptorHeapManager;

import <cstddef>;
import <memory>;
import <type_traits>;

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
		virtual std::shared_ptr<DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT descriptorCount, DescriptorHeapVisibility visibility) override;

		DescriptorHeapManager& operator =(const DescriptorHeapManager& other) noexcept = default;
		DescriptorHeapManager& operator =(DescriptorHeapManager&& other) noexcept = default;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	DescriptorHeapManager::DescriptorHeapManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<DescriptorHeap> DescriptorHeapManager::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_TYPE heapType, const UINT descriptorCount, const DescriptorHeapVisibility visibility)
	{
		const auto heapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = heapType,
			.NumDescriptors = descriptorCount,
			.Flags = ToHeapFlags(visibility),
			.NodeMask = 0u
		};
		ID3D12Device10& device = d3d12System->Device();
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;
		if (const HRESULT result = device.CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(heap.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return std::make_shared<DescriptorHeap>(*heap.Get(), device.GetDescriptorHandleIncrementSize(heapType));
	}
}
