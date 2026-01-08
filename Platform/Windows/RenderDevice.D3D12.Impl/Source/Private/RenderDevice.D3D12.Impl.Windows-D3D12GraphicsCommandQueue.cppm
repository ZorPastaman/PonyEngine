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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12GraphicsCommandQueue;

import :D3D12CommandQueue;

export namespace PonyEngine::Render::Windows
{
	class D3D12GraphicsCommandQueue final : public D3D12CommandQueue
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12GraphicsCommandQueue(IRenderDeviceContext& renderDevice, ID3D12Device14& device, INT priority);
		D3D12GraphicsCommandQueue(const D3D12GraphicsCommandQueue&) = delete;
		D3D12GraphicsCommandQueue(D3D12GraphicsCommandQueue&&) = delete;

		virtual ~D3D12GraphicsCommandQueue() noexcept override = default;

		D3D12GraphicsCommandQueue& operator =(const D3D12GraphicsCommandQueue&) = delete;
		D3D12GraphicsCommandQueue& operator =(D3D12GraphicsCommandQueue&&) = delete;

	private:

	};
}

namespace PonyEngine::Render::Windows
{
	D3D12GraphicsCommandQueue::D3D12GraphicsCommandQueue(IRenderDeviceContext& renderDevice, ID3D12Device14& device, const INT priority) :
		D3D12CommandQueue(renderDevice, device, priority, D3D12_COMMAND_LIST_TYPE_DIRECT)
	{
	}
}
