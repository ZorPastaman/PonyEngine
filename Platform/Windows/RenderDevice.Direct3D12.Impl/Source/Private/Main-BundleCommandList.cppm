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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:BundleCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class BundleCommandList final : public ISecondaryGraphicsCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		BundleCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		BundleCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		BundleCommandList(const BundleCommandList&) = delete;
		BundleCommandList(BundleCommandList&&) = delete;

		~BundleCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;
		[[nodiscard("Pure function")]] 
		virtual bool IsOpen() const noexcept override;

		virtual void SetDepthBias(const DepthBias& bias) override;
		virtual void SetDepthBounds(float min, float max) override;
		virtual void SetStencilReference(const StencilReference& reference) override;

		virtual void DispatchMesh(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		BundleCommandList& operator =(const BundleCommandList&) = delete;
		BundleCommandList& operator =(BundleCommandList&&) = delete;

	private:
		class CommandList commandList;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	BundleCommandList::BundleCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList)
	{
	}

	BundleCommandList::BundleCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void BundleCommandList::Reset()
	{
		commandList.Reset();
	}

	void BundleCommandList::Close()
	{
		commandList.Close();
	}

	bool BundleCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
	}

	void BundleCommandList::SetDepthBias(const DepthBias& bias)
	{
		commandList.SetDepthBias(bias);
	}

	void BundleCommandList::SetDepthBounds(const float min, const float max)
	{
		commandList.SetDepthBounds(min, max);
	}

	void BundleCommandList::SetStencilReference(const StencilReference& reference)
	{
		commandList.SetStencilReference(reference);
	}

	void BundleCommandList::DispatchMesh(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.DispatchMesh(threadGroupCounts);
	}

	std::string_view BundleCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void BundleCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& BundleCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}
}
