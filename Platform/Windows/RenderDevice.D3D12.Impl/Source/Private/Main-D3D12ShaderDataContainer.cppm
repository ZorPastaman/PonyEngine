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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12ShaderDataContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12DescriptorHeap;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12ShaderDataContainer final : public IShaderDataContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12ShaderDataContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size, bool shaderVisible) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12ShaderDataContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size, bool shaderVisible) noexcept;
		D3D12ShaderDataContainer(const D3D12ShaderDataContainer&) = delete;
		D3D12ShaderDataContainer(D3D12ShaderDataContainer&&) = delete;

		~D3D12ShaderDataContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsShaderVisible() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual const ShaderDataMeta& Meta(std::uint32_t index) const noexcept override;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(UINT index) const noexcept;

		void Set(std::uint32_t index, const ShaderDataMeta& meta) noexcept;

		D3D12ShaderDataContainer& operator =(const D3D12ShaderDataContainer&) = delete;
		D3D12ShaderDataContainer& operator =(D3D12ShaderDataContainer&&) = delete;

	private:
		D3D12DescriptorHeap descriptorHeap;

		std::uint32_t size;
		bool shaderVisible;

		std::unique_ptr<ShaderDataMeta[]> metas;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12ShaderDataContainer::D3D12ShaderDataContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size, const bool shaderVisible) noexcept :
		descriptorHeap(descriptorHeap, handleIncrement),
		size{size},
		shaderVisible{shaderVisible},
		metas(std::make_unique<ShaderDataMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyShaderDataMeta{});
	}

	D3D12ShaderDataContainer::D3D12ShaderDataContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement,
		const std::uint32_t size, const bool shaderVisible) noexcept :
		descriptorHeap(std::move(descriptorHeap), handleIncrement),
		size{size},
		shaderVisible{shaderVisible},
		metas(std::make_unique<ShaderDataMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyShaderDataMeta{});
	}

	std::uint32_t D3D12ShaderDataContainer::Size() const noexcept
	{
		return size;
	}

	bool D3D12ShaderDataContainer::IsShaderVisible() const noexcept
	{
		return shaderVisible;
	}

	const ShaderDataMeta& D3D12ShaderDataContainer::Meta(const std::uint32_t index) const noexcept
	{
		return metas[index];
	}

	ID3D12DescriptorHeap& D3D12ShaderDataContainer::DescriptorHeap() const noexcept
	{
		return descriptorHeap.DescriptorHeap();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12ShaderDataContainer::CpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.CpuHandle(index);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE D3D12ShaderDataContainer::GpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.GpuHandle(index);
	}

	void D3D12ShaderDataContainer::Set(const std::uint32_t index, const ShaderDataMeta& meta) noexcept
	{
		metas[index] = meta;
	}
}
