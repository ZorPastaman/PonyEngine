/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:DepthStencilContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :DescriptorHeap;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class DepthStencilContainer final : public IDepthStencilContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		DepthStencilContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size) noexcept;
		[[nodiscard("Pure constructor")]]
		DepthStencilContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size) noexcept;
		DepthStencilContainer(const DepthStencilContainer&) = delete;
		DepthStencilContainer(DepthStencilContainer&&) = delete;

		~DepthStencilContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;

		[[nodiscard("Pure function")]]
		DepthStencilMeta& Meta(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]]
		virtual const DepthStencilMeta& Meta(std::uint32_t index) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;

		void Set(std::uint32_t index, const DepthStencilMeta& meta) noexcept;

		DepthStencilContainer& operator =(const DepthStencilContainer&) = delete;
		DepthStencilContainer& operator =(DepthStencilContainer&&) = delete;

	private:
		class DescriptorHeap descriptorHeap;

		std::uint32_t size;

		std::unique_ptr<DepthStencilMeta[]> metas;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	DepthStencilContainer::DepthStencilContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size) noexcept :
		descriptorHeap(descriptorHeap, handleIncrement, false),
		size{size},
		metas(std::make_unique<DepthStencilMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyDepthStencilMeta{});
	}

	DepthStencilContainer::DepthStencilContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement,
		const std::uint32_t size) noexcept :
		descriptorHeap(std::move(descriptorHeap), handleIncrement, false),
		size{size},
		metas(std::make_unique<DepthStencilMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyDepthStencilMeta{});
	}

	std::uint32_t DepthStencilContainer::Size() const noexcept
	{
		return size;
	}

	DepthStencilMeta& DepthStencilContainer::Meta(const std::uint32_t index) noexcept
	{
		return metas[index];
	}

	const DepthStencilMeta& DepthStencilContainer::Meta(const std::uint32_t index) const noexcept
	{
		return metas[index];
	}

	std::string_view DepthStencilContainer::Name() const noexcept
	{
		return descriptorHeap.Name();
	}

	void DepthStencilContainer::Name(const std::string_view name)
	{
		descriptorHeap.Name(name);
	}

	ID3D12DescriptorHeap& DepthStencilContainer::DescriptorHeap() const noexcept
	{
		return descriptorHeap.GetDescriptorHeap();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilContainer::CpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.CpuHandle(index);
	}

	void DepthStencilContainer::Set(const std::uint32_t index, const DepthStencilMeta& meta) noexcept
	{
		metas[index] = meta;
	}
}
