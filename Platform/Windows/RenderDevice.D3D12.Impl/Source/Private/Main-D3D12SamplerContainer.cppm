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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12SamplerContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12DescriptorHeap;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12SamplerContainer final : public ISamplerContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12SamplerContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size, bool shaderVisible) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12SamplerContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size, bool shaderVisible) noexcept;
		D3D12SamplerContainer(const D3D12SamplerContainer&) = delete;
		D3D12SamplerContainer(D3D12SamplerContainer&&) = delete;

		~D3D12SamplerContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsShaderVisible() const noexcept override;

		[[nodiscard("Pure function")]]
		SamplerMeta& Meta(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]]
		virtual const SamplerMeta& Meta(std::uint32_t index) const noexcept override;

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(UINT index) const noexcept;

		void Set(std::uint32_t index, const SamplerMeta& meta) noexcept;

		D3D12SamplerContainer& operator =(const D3D12SamplerContainer&) = delete;
		D3D12SamplerContainer& operator =(D3D12SamplerContainer&&) = delete;

	private:
		D3D12DescriptorHeap descriptorHeap;

		std::uint32_t size;
		bool shaderVisible;

		std::unique_ptr<SamplerMeta[]> metas;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12SamplerContainer::D3D12SamplerContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size, const bool shaderVisible) noexcept :
		descriptorHeap(descriptorHeap, handleIncrement),
		size{size},
		shaderVisible{shaderVisible},
		metas(std::make_unique<SamplerMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptySamplerParams{});
	}

	D3D12SamplerContainer::D3D12SamplerContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement,
		const std::uint32_t size, const bool shaderVisible) noexcept :
		descriptorHeap(std::move(descriptorHeap), handleIncrement),
		size{size},
		shaderVisible{shaderVisible},
		metas(std::make_unique<SamplerMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptySamplerParams{});
	}

	std::uint32_t D3D12SamplerContainer::Size() const noexcept
	{
		return size;
	}

	bool D3D12SamplerContainer::IsShaderVisible() const noexcept
	{
		return shaderVisible;
	}

	SamplerMeta& D3D12SamplerContainer::Meta(const std::uint32_t index) noexcept
	{
		return metas[index];
	}

	const SamplerMeta& D3D12SamplerContainer::Meta(const std::uint32_t index) const noexcept
	{
		return metas[index];
	}

	void D3D12SamplerContainer::SetName(const std::string_view name)
	{
		descriptorHeap.SetName(name);
	}

	ID3D12DescriptorHeap& D3D12SamplerContainer::DescriptorHeap() const noexcept
	{
		return descriptorHeap.DescriptorHeap();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12SamplerContainer::CpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.CpuHandle(index);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE D3D12SamplerContainer::GpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.GpuHandle(index);
	}

	void D3D12SamplerContainer::Set(const std::uint32_t index, const SamplerMeta& meta) noexcept
	{
		metas[index] = meta;
	}
}
