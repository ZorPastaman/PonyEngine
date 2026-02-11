/***************************************************
 * MIT License                                     *
 *                                                 *
 * right (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class CommandList final
	{
	public:
		[[nodiscard("Pure constructor")]]
		CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept;
		[[nodiscard("Pure constructor")]]
		CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept;
		CommandList(const CommandList&) = delete;
		CommandList(CommandList&&) = delete;

		~CommandList() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& GetCommandList() const noexcept;

		void Reset();
		void Close();

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		CommandList& operator =(const CommandList&) = delete;
		CommandList& operator =(CommandList&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator;
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	CommandList::CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) noexcept :
		allocator(&allocator),
		commandList(&commandList)
	{
	}

	CommandList::CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) noexcept :
		allocator(std::move(allocator)),
		commandList(std::move(commandList))
	{
		assert(this->allocator && "The allocator is nullptr.");
		assert(this->commandList && "The command list is nullptr.");
	}

	ID3D12GraphicsCommandList10& CommandList::GetCommandList() const noexcept
	{
		return *commandList;
	}

	void CommandList::Reset()
	{
		if (const HRESULT result = allocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command allocator: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(allocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void CommandList::Close()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to close command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	std::string_view CommandList::Name() const noexcept
	{
		return name;
	}

	void CommandList::Name(const std::string_view name)
	{
		SetObjectName(*allocator, name);

		try
		{
			SetObjectName(*commandList, name);

			try
			{
				this->name = name;
			}
			catch (...)
			{
				SetObjectName(*commandList, this->name);
				throw;
			}
		}
		catch (...)
		{
			SetObjectName(*allocator, this->name);
			throw;
		}
	}
}
