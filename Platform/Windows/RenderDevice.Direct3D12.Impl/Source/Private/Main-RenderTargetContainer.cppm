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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:RenderTargetContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :DescriptorHeap;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Container wrapper of RTVs.
	class RenderTargetContainer final : public IRenderTargetContainer
	{
	public:
		/// @brief Creates a render target container wrapper.
		/// @param descriptorHeap Descriptor heap.
		/// @param handleIncrement Descriptor handle increment.
		/// @param size Descriptor heap size.
		[[nodiscard("Pure constructor")]]
		RenderTargetContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size);
		/// @brief Creates a render target container wrapper.
		/// @param descriptorHeap Descriptor heap.
		/// @param handleIncrement Descriptor handle increment.
		/// @param size Descriptor heap size.
		[[nodiscard("Pure constructor")]]
		RenderTargetContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size);
		RenderTargetContainer(const RenderTargetContainer&) = delete;
		RenderTargetContainer(RenderTargetContainer&&) = delete;

		~RenderTargetContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;

		/// @brief Gets a meta at the @p index.
		/// @param index Container element index.
		/// @return Container element meta.
		[[nodiscard("Pure function")]]
		RTVMeta& Meta(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]]
		virtual const RTVMeta& Meta(std::uint32_t index) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the descriptor heap.
		/// @return Descriptor heap.
		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		/// @brief Gets a CPU descriptor handle.
		/// @param index Descriptor index.
		/// @return CPU descriptor handle.
		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;

		RenderTargetContainer& operator =(const RenderTargetContainer&) = delete;
		RenderTargetContainer& operator =(RenderTargetContainer&&) = delete;

	private:
		class DescriptorHeap descriptorHeap; ///< Descriptor heap
		std::uint32_t size; ///< Descriptor heap size.
		std::unique_ptr<RTVMeta[]> metas; ///< Descriptor heap metas.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	RenderTargetContainer::RenderTargetContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size) :
		descriptorHeap(descriptorHeap, handleIncrement, false),
		size{size},
		metas(std::make_unique<RTVMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyRTVMeta{});
	}

	RenderTargetContainer::RenderTargetContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement, const std::uint32_t size) :
		descriptorHeap(std::move(descriptorHeap), handleIncrement, false),
		size{size},
		metas(std::make_unique<RTVMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyRTVMeta{});
	}

	std::uint32_t RenderTargetContainer::Size() const noexcept
	{
		return size;
	}

	RTVMeta& RenderTargetContainer::Meta(const std::uint32_t index) noexcept
	{
		assert(index < size && "Out of range.");
		return metas[index];
	}

	const RTVMeta& RenderTargetContainer::Meta(const std::uint32_t index) const noexcept
	{
		assert(index < size && "Out of range.");
		return metas[index];
	}

	std::string_view RenderTargetContainer::Name() const noexcept
	{
		return descriptorHeap.Name();
	}

	void RenderTargetContainer::Name(const std::string_view name)
	{
		descriptorHeap.Name(name);
	}

	ID3D12DescriptorHeap& RenderTargetContainer::DescriptorHeap() const noexcept
	{
		return descriptorHeap.GetDescriptorHeap();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetContainer::CpuHandle(const UINT index) const noexcept
	{
		assert(index < size && "Out of range.");
		return descriptorHeap.CpuHandle(index);
	}
}
