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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Fence;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12Utility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Fence final : public IFence
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12Fence(ID3D12Fence1& fence) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit D3D12Fence(Platform::Windows::ComPtr<ID3D12Fence1>&& fence) noexcept;
		D3D12Fence(const D3D12Fence&) = delete;
		D3D12Fence(D3D12Fence&&) = delete;

		~D3D12Fence() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::uint64_t CompletedValue() const noexcept override;
		virtual void Signal(std::uint64_t value) override;

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12Fence1& Fence() const noexcept;

		void SetEventOnCompletion(std::uint64_t value, HANDLE event) const;

		D3D12Fence& operator =(const D3D12Fence&) = delete;
		D3D12Fence& operator =(D3D12Fence&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12Fence1> fence;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Fence::D3D12Fence(ID3D12Fence1& fence) noexcept :
		fence(&fence)
	{
	}

	D3D12Fence::D3D12Fence(Platform::Windows::ComPtr<ID3D12Fence1>&& fence) noexcept :
		fence(std::move(fence))
	{
	}

	std::uint64_t D3D12Fence::CompletedValue() const noexcept
	{
		return static_cast<std::uint64_t>(fence->GetCompletedValue());
	}

	void D3D12Fence::Signal(const std::uint64_t value)
	{
		if (const HRESULT result = fence->Signal(value); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to signal fence: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void D3D12Fence::SetName(const std::string_view name)
	{
		SetObjectName(*fence, name);
	}

	ID3D12Fence1& D3D12Fence::Fence() const noexcept
	{
		return *fence;
	}

	void D3D12Fence::SetEventOnCompletion(const std::uint64_t value, const HANDLE event) const
	{
		if (const HRESULT result = fence->SetEventOnCompletion(static_cast<UINT64>(value), event); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set event on completion: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
