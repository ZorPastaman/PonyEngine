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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Fence;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Fence wrapper.
	class Fence final : public IFence
	{
	public:
		/// @brief Creates a fence wrapper.
		/// @param fence Fence.
		[[nodiscard("Pure constructor")]]
		explicit Fence(ID3D12Fence1& fence) noexcept;
		/// @brief Creates a fence wrapper.
		/// @param fence Fence.
		[[nodiscard("Pure constructor")]]
		explicit Fence(Platform::Windows::ComPtr<ID3D12Fence1>&& fence) noexcept;
		Fence(const Fence&) = delete;
		Fence(Fence&&) = delete;

		~Fence() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::uint64_t CompletedValue() const noexcept override;
		virtual void Signal(std::uint64_t value) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the fence.
		/// @return Fence.
		[[nodiscard("Pure function")]]
		ID3D12Fence1& GetFence() const noexcept;

		/// @brief Sets the event on completion.
		/// @param value Waited fence value.
		/// @param event Event to trigger.
		void SetEventOnCompletion(std::uint64_t value, HANDLE event) const;

		Fence& operator =(const Fence&) = delete;
		Fence& operator =(Fence&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12Fence1> fence; ///< Fence.

		std::string name; ///< Name.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Fence::Fence(ID3D12Fence1& fence) noexcept :
		fence(&fence)
	{
	}

	Fence::Fence(Platform::Windows::ComPtr<ID3D12Fence1>&& fence) noexcept :
		fence(std::move(fence))
	{
		assert(this->fence && "The fence is nullptr.");
	}

	std::uint64_t Fence::CompletedValue() const noexcept
	{
		return fence->GetCompletedValue();
	}

	void Fence::Signal(const std::uint64_t value)
	{
		if (const HRESULT result = fence->Signal(value); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to signal fence: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	std::string_view Fence::Name() const noexcept
	{
		return name;
	}

	void Fence::Name(const std::string_view name)
	{
		SetObjectName(*fence, name);

		try
		{
			this->name = name;
		}
		catch (...)
		{
			SetObjectName(*fence, this->name);
			throw;
		}
	}

	ID3D12Fence1& Fence::GetFence() const noexcept
	{
		return *fence;
	}

	void Fence::SetEventOnCompletion(const std::uint64_t value, const HANDLE event) const
	{
		if (const HRESULT result = fence->SetEventOnCompletion(value, event); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set event on completion: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
