/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12GpuWaiter;

import <memory>;

import :Direct3D12Fence;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	class Direct3D12GpuWaiter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12GpuWaiter(IDirect3D12SystemContext& d3d12System, ID3D12CommandQueue& waitedCommandQueue, ID3D12CommandQueue& targetCommandQueue);
		Direct3D12GpuWaiter(const Direct3D12GpuWaiter&) = delete;
		Direct3D12GpuWaiter(Direct3D12GpuWaiter&&) = delete;

		~Direct3D12GpuWaiter() noexcept;

		void Wait();

		Direct3D12GpuWaiter& operator =(const Direct3D12GpuWaiter&) = delete;
		Direct3D12GpuWaiter& operator =(Direct3D12GpuWaiter&&) = delete;

	private:
		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::unique_ptr<Direct3D12Fence> fence; ///< Fence.
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> targetCommandQueue; ///< Command queue that should wait.
	};
}

namespace PonyEngine::Render
{
	Direct3D12GpuWaiter::Direct3D12GpuWaiter(IDirect3D12SystemContext& d3d12System, ID3D12CommandQueue& waitedCommandQueue, ID3D12CommandQueue& targetCommandQueue) :
		d3d12System{&d3d12System},
		fence(std::make_unique<Direct3D12Fence>(d3d12System, waitedCommandQueue)),
		targetCommandQueue(&targetCommandQueue)
	{
	}

	Direct3D12GpuWaiter::~Direct3D12GpuWaiter() noexcept
	{
		targetCommandQueue.Reset();
		fence.reset();
	}

	void Direct3D12GpuWaiter::Wait()
	{
		fence->Signal();

		if (const UINT64 currentValue = fence->CurrentValue(); fence->CompletedValue() < currentValue)
		{
			if (const HRESULT result = targetCommandQueue->Wait(&fence->Fence(), currentValue); FAILED(result))
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set gpu wait with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
			}
		}
	}
}
