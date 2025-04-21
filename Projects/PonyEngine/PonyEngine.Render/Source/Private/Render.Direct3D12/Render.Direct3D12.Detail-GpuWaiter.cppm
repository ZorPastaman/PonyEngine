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

export module PonyEngine.Render.Direct3D12.Detail:GpuWaiter;

import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;

import :Fence;
import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 gpu waiter.
	/// @details It makes a command queue to wait for another command queue.
	class GpuWaiter final
	{
	public:
		/// @brief Creates a @p GpuWaiter.
		/// @param d3d12System Direct3D12 system context.
		/// @param waitedCommandQueue Waited command queue.
		/// @param waitingCommandQueue Waiting command queue.
		[[nodiscard("Pure constructor")]]
		GpuWaiter(ISubSystemContext& d3d12System, ID3D12CommandQueue& waitedCommandQueue, ID3D12CommandQueue& waitingCommandQueue);
		GpuWaiter(const GpuWaiter&) = delete;
		GpuWaiter(GpuWaiter&&) = delete;

		~GpuWaiter() noexcept;

		/// @brief Submit a wait command.
		void Wait();

		/// @brief Sets the name to the cpu waiter components.
		/// @param name Name.
		void Name(std::string_view name);

		GpuWaiter& operator =(const GpuWaiter&) = delete;
		GpuWaiter& operator =(GpuWaiter&&) = delete;

	private:
		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::unique_ptr<Fence> fence; ///< Fence.
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> waitingCommandQueue; ///< Waiting command queue.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	GpuWaiter::GpuWaiter(ISubSystemContext& d3d12System, ID3D12CommandQueue& waitedCommandQueue, ID3D12CommandQueue& waitingCommandQueue) :
		d3d12System{&d3d12System},
		fence(std::make_unique<Fence>(d3d12System, waitedCommandQueue)),
		waitingCommandQueue(&waitingCommandQueue)
	{
	}

	GpuWaiter::~GpuWaiter() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release waiting command queue.");
		waitingCommandQueue.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Waiting command queue released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy fence.");
		fence.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Fence destroyed.");
	}

	void GpuWaiter::Wait()
	{
		fence->Signal();
		fence->Wait(*waitingCommandQueue.Get());
	}

	void GpuWaiter::Name(const std::string_view name)
	{
		fence->Name(name);
	}
}
