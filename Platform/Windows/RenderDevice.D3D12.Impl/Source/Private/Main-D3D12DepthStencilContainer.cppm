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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12DepthStencilContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12DescriptorHeap;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12DepthStencilContainer final : public IDepthStencilContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12DepthStencilContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12DepthStencilContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size) noexcept;
		D3D12DepthStencilContainer(const D3D12DepthStencilContainer&) = delete;
		D3D12DepthStencilContainer(D3D12DepthStencilContainer&&) = delete;

		~D3D12DepthStencilContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;

		[[nodiscard("Pure function")]]
		DepthStencilMeta& Meta(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]]
		virtual const DepthStencilMeta& Meta(std::uint32_t index) const noexcept override;

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;

		void Set(std::uint32_t index, const DepthStencilMeta& meta) noexcept;

		D3D12DepthStencilContainer& operator =(const D3D12DepthStencilContainer&) = delete;
		D3D12DepthStencilContainer& operator =(D3D12DepthStencilContainer&&) = delete;

	private:
		D3D12DescriptorHeap descriptorHeap;

		std::uint32_t size;

		std::unique_ptr<DepthStencilMeta[]> metas;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12DepthStencilContainer::D3D12DepthStencilContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size) noexcept :
		descriptorHeap(descriptorHeap, handleIncrement),
		size{size},
		metas(std::make_unique<DepthStencilMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyDepthStencilMeta{});
	}

	D3D12DepthStencilContainer::D3D12DepthStencilContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement,
		const std::uint32_t size) noexcept :
		descriptorHeap(std::move(descriptorHeap), handleIncrement),
		size{size},
		metas(std::make_unique<DepthStencilMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyDepthStencilMeta{});
	}

	std::uint32_t D3D12DepthStencilContainer::Size() const noexcept
	{
		return size;
	}

	DepthStencilMeta& D3D12DepthStencilContainer::Meta(const std::uint32_t index) noexcept
	{
		return metas[index];
	}

	const DepthStencilMeta& D3D12DepthStencilContainer::Meta(const std::uint32_t index) const noexcept
	{
		return metas[index];
	}

	void D3D12DepthStencilContainer::SetName(const std::string_view name)
	{
		descriptorHeap.SetName(name);
	}

	ID3D12DescriptorHeap& D3D12DepthStencilContainer::DescriptorHeap() const noexcept
	{
		return descriptorHeap.DescriptorHeap();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12DepthStencilContainer::CpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.CpuHandle(index);
	}

	void D3D12DepthStencilContainer::Set(const std::uint32_t index, const DepthStencilMeta& meta) noexcept
	{
		metas[index] = meta;
	}
}
