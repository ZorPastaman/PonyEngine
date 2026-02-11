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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ShaderDataContainer;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :DescriptorHeap;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class ShaderDataContainer final : public IShaderDataContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		ShaderDataContainer(ID3D12DescriptorHeap& descriptorHeap, UINT handleIncrement, std::uint32_t size, bool shaderVisible) noexcept;
		[[nodiscard("Pure constructor")]]
		ShaderDataContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, UINT handleIncrement, std::uint32_t size, bool shaderVisible) noexcept;
		ShaderDataContainer(const ShaderDataContainer&) = delete;
		ShaderDataContainer(ShaderDataContainer&&) = delete;

		~ShaderDataContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsShaderVisible() const noexcept override;

		[[nodiscard("Pure function")]]
		ShaderDataMeta& Meta(std::uint32_t index) noexcept;
		[[nodiscard("Pure function")]] 
		virtual const ShaderDataMeta& Meta(std::uint32_t index) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12DescriptorHeap& DescriptorHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle(UINT index) const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle(UINT index) const noexcept;

		void Set(std::uint32_t index, const ShaderDataMeta& meta) noexcept;

		ShaderDataContainer& operator =(const ShaderDataContainer&) = delete;
		ShaderDataContainer& operator =(ShaderDataContainer&&) = delete;

	private:
		class DescriptorHeap descriptorHeap;

		std::uint32_t size;
		bool shaderVisible;

		std::unique_ptr<ShaderDataMeta[]> metas;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ShaderDataContainer::ShaderDataContainer(ID3D12DescriptorHeap& descriptorHeap, const UINT handleIncrement, const std::uint32_t size, const bool shaderVisible) noexcept :
		descriptorHeap(descriptorHeap, handleIncrement),
		size{size},
		shaderVisible{shaderVisible},
		metas(std::make_unique<ShaderDataMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyShaderDataMeta{});
	}

	ShaderDataContainer::ShaderDataContainer(Platform::Windows::ComPtr<ID3D12DescriptorHeap>&& descriptorHeap, const UINT handleIncrement,
		const std::uint32_t size, const bool shaderVisible) noexcept :
		descriptorHeap(std::move(descriptorHeap), handleIncrement),
		size{size},
		shaderVisible{shaderVisible},
		metas(std::make_unique<ShaderDataMeta[]>(this->size))
	{
		std::ranges::fill(metas.get(), metas.get() + this->size, EmptyShaderDataMeta{});
	}

	std::uint32_t ShaderDataContainer::Size() const noexcept
	{
		return size;
	}

	bool ShaderDataContainer::IsShaderVisible() const noexcept
	{
		return shaderVisible;
	}

	ShaderDataMeta& ShaderDataContainer::Meta(const std::uint32_t index) noexcept
	{
		return metas[index];
	}

	const ShaderDataMeta& ShaderDataContainer::Meta(const std::uint32_t index) const noexcept
	{
		return metas[index];
	}

	std::string_view ShaderDataContainer::Name() const noexcept
	{
		return descriptorHeap.Name();
	}

	void ShaderDataContainer::Name(const std::string_view name)
	{
		descriptorHeap.Name(name);
	}

	ID3D12DescriptorHeap& ShaderDataContainer::DescriptorHeap() const noexcept
	{
		return descriptorHeap.GetDescriptorHeap();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE ShaderDataContainer::CpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.CpuHandle(index);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE ShaderDataContainer::GpuHandle(const UINT index) const noexcept
	{
		return descriptorHeap.GpuHandle(index);
	}

	void ShaderDataContainer::Set(const std::uint32_t index, const ShaderDataMeta& meta) noexcept
	{
		metas[index] = meta;
	}
}
