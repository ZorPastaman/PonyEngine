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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:RenderTargetContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :DescriptorHeap;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class RenderTargetContainer final : public IRenderTargetContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		RenderTargetContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size) noexcept;
		[[nodiscard("Pure constructor")]]
		RenderTargetContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size) noexcept;
		RenderTargetContainer(const RenderTargetContainer&) = delete;
		RenderTargetContainer(RenderTargetContainer&&) = delete;

		~RenderTargetContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;

		[[nodiscard("Pure function")]]
		RenderTargetMeta& Meta(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]]
		virtual const RenderTargetMeta& Meta(std::uint32_t index) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;

		void Set(std::uint32_t index, const RenderTargetMeta& meta) noexcept;

		RenderTargetContainer& operator =(const RenderTargetContainer&) = delete;
		RenderTargetContainer& operator =(RenderTargetContainer&&) = delete;

	private:
		class DescriptorHeap descriptorHeap;

		std::uint32_t size;

		std::unique_ptr<RenderTargetMeta[]> metas;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	RenderTargetContainer::RenderTargetContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size) noexcept :
		descriptorHeap(descriptorHeap, handleIncrement),
		size{size},
		metas(std::make_unique<RenderTargetMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyRenderTargetMeta{});
	}

	RenderTargetContainer::RenderTargetContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement,
		const std::uint32_t size) noexcept :
		descriptorHeap(std::move(descriptorHeap), handleIncrement),
		size{size},
		metas(std::make_unique<RenderTargetMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyRenderTargetMeta{});
	}

	std::uint32_t RenderTargetContainer::Size() const noexcept
	{
		return size;
	}

	RenderTargetMeta& RenderTargetContainer::Meta(const std::uint32_t index) noexcept
	{
		return metas[index];
	}

	const RenderTargetMeta& RenderTargetContainer::Meta(const std::uint32_t index) const noexcept
	{
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
		return descriptorHeap.CpuHandle(index);
	}

	void RenderTargetContainer::Set(const std::uint32_t index, const RenderTargetMeta& meta) noexcept
	{
		metas[index] = meta;
	}
}
