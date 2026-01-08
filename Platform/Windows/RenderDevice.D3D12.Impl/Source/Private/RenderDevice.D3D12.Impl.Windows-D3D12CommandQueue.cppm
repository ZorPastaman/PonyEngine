/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12CommandQueue;

import std;

import PonyEngine.Log;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice.Ext;

import :D3D12Utility;

export namespace PonyEngine::Render::Windows
{
	class D3D12CommandQueue
	{
	public:
		D3D12CommandQueue(const D3D12CommandQueue&) = delete;
		D3D12CommandQueue(D3D12CommandQueue&&) = delete;

		virtual ~D3D12CommandQueue() noexcept;

		void SetName(std::string_view name);

		D3D12CommandQueue& operator =(const D3D12CommandQueue&) = delete;
		D3D12CommandQueue& operator =(D3D12CommandQueue&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		D3D12CommandQueue(IRenderDeviceContext& renderDevice, ID3D12Device14& device, INT priority, D3D12_COMMAND_LIST_TYPE commandListType);

		[[nodiscard("Pure function")]]
		IRenderDeviceContext& RenderDevice() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12Device14& Device() const noexcept;

	private:
		IRenderDeviceContext* renderDevice;
		Platform::Windows::ComPtr<ID3D12Device14> device;

		GUID guid;
		Platform::Windows::ComPtr<ID3D12CommandQueue> commandQueue;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12CommandQueue::~D3D12CommandQueue() noexcept
	{
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing d3d12 command queue... Type: '{}'.", static_cast<int>(commandQueue->GetDesc().Type));
		commandQueue.Reset();
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Releasing d3d12 command queue done.");
	}

	void D3D12CommandQueue::SetName(const std::string_view name)
	{
		Windows::SetName(*commandQueue, name);
	}

	D3D12CommandQueue::D3D12CommandQueue(IRenderDeviceContext& renderDevice, ID3D12Device14& device, const INT priority, const D3D12_COMMAND_LIST_TYPE commandListType) :
		renderDevice{&renderDevice},
		device(&device),
		guid(Platform::Windows::AcquireGuid())
	{
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = priority,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring d3d12 command queue... Type: '{}'; Priority: '{}'; GUID: '{}'.", static_cast<int>(commandQueueDescription.Type), commandQueueDescription.Priority, guid);
		if (const HRESULT result = this->device->CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddress())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to acquire d3d12 command queue: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Acquiring d3d12 command queue done.");
	}

	IRenderDeviceContext& D3D12CommandQueue::RenderDevice() const noexcept
	{
		return *renderDevice;
	}

	ID3D12Device14& D3D12CommandQueue::Device() const noexcept
	{
		return *device;
	}
}
