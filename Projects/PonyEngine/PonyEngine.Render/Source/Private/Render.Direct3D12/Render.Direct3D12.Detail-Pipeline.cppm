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

export module PonyEngine.Render.Direct3D12.Detail:Pipeline;

import PonyBase.Utility.COM;

import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 pipeline.
	class Pipeline
	{
	public:
		Pipeline(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;

		virtual ~Pipeline() noexcept;

		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		/// @brief Sets the name to the components.
		/// @param name Name.
		virtual void Name(std::string_view name);

		Pipeline& operator =(const Pipeline&) = delete;
		Pipeline& operator =(Pipeline&&) = delete;

	protected:
		/// @brief Creates a pipeline.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueuePriority Command queue priority.
		/// @param commandListType Command list type.
		[[nodiscard("Pure constructor")]]
		Pipeline(ISubSystemContext& d3d12System, INT commandQueuePriority, D3D12_COMMAND_LIST_TYPE commandListType);

		/// @brief Gets the Direct3D12 system.
		/// @return Direct3D12 system.
		[[nodiscard("Pure function")]]
		ISubSystemContext& D3D12System() const noexcept;

		/// @brief Gets the command list.
		/// @return Command list.
		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList7& CommandList() noexcept;
		/// @brief Gets the command list.
		/// @return Command list.
		[[nodiscard("Pure function")]]
		const ID3D12GraphicsCommandList7& CommandList() const noexcept;

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Closes command lists.
		void CloseLists();

		/// @brief Adds the buffer barrier.
		/// @param barrier Buffer barrier to add.
		void AddBarrier(const D3D12_BUFFER_BARRIER& barrier);
		/// @brief Adds the texture barrier.
		/// @param barrier Texture barrier to add.
		void AddBarrier(const D3D12_TEXTURE_BARRIER& barrier);
		/// @brief Populates barriers.
		void PopulateBarriers();

	private:
		GUID guid; ///< Copy pipeline guid.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Copy command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Copy command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Copy command list.

		std::vector<D3D12_BUFFER_BARRIER> bufferBarriers; ///< Buffer barriers cache.
		std::vector<D3D12_TEXTURE_BARRIER> textureBarriers; ///< Buffer barriers cache.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Pipeline::~Pipeline() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command list.");
		commandList.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command list released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command allocator.");
		commandAllocator.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command allocator released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command queue.");
		commandQueue.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command queue released.");
	}

	ID3D12CommandQueue& Pipeline::CommandQueue() noexcept
	{
		return *commandQueue.Get();
	}

	const ID3D12CommandQueue& Pipeline::CommandQueue() const noexcept
	{
		return *commandQueue.Get();
	}

	void Pipeline::Name(const std::string_view name)
	{
		SetName(*commandQueue.Get(), name);
		SetName(*commandAllocator.Get(), name);
		SetName(*commandList.Get(), name);
	}

	Pipeline::Pipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority, const D3D12_COMMAND_LIST_TYPE commandListType) :
		guid{PonyBase::Utility::COM::AcquireGuid()},
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Pipeline guid: '{}'.", PonyBase::Utility::COM::ToString(guid));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire command queue. Type: {}; Priority: '{}'.", static_cast<int>(commandListType), commandQueuePriority);
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = commandQueuePriority,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = this->d3d12System->Device().CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command queue with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command queue acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire command allocator.");
		if (const HRESULT result = this->d3d12System->Device().CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command allocator acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire command list.");
		if (const HRESULT result = this->d3d12System->Device().CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command list acquired.");
	}

	ISubSystemContext& Pipeline::D3D12System() const noexcept
	{
		return *d3d12System;
	}

	ID3D12GraphicsCommandList7& Pipeline::CommandList() noexcept
	{
		return *commandList.Get();
	}

	const ID3D12GraphicsCommandList7& Pipeline::CommandList() const noexcept
	{
		return *commandList.Get();
	}

	void Pipeline::ResetLists()
	{
		if (const HRESULT result = commandAllocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(commandAllocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Pipeline::CloseLists()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Pipeline::AddBarrier(const D3D12_BUFFER_BARRIER& barrier)
	{
		bufferBarriers.push_back(barrier);
	}

	void Pipeline::AddBarrier(const D3D12_TEXTURE_BARRIER& barrier)
	{
		textureBarriers.push_back(barrier);
	}

	void Pipeline::PopulateBarriers()
	{
		auto barrierGroups = std::array<D3D12_BARRIER_GROUP, 2>();
		UINT32 count = 0u;
		if (bufferBarriers.size() > 0)
		{
			barrierGroups[count++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_BUFFER,
				.NumBarriers = static_cast<UINT32>(bufferBarriers.size()),
				.pBufferBarriers = bufferBarriers.data()
			};
		}
		if (textureBarriers.size() > 0)
		{
			barrierGroups[count++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_TEXTURE,
				.NumBarriers = static_cast<UINT32>(textureBarriers.size()),
				.pTextureBarriers = textureBarriers.data()
			};
		}

		if (count > 0u)
		{
			commandList->Barrier(count, barrierGroups.data());
		}

		bufferBarriers.clear();
		textureBarriers.clear();
	}
}
