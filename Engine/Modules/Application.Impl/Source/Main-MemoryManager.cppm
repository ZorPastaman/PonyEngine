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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:MemoryManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Memory manager.
	class MemoryManager final
	{
	public:
		/// @brief Creates a memory manager.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit MemoryManager(IApplication& application) noexcept;
		MemoryManager(const MemoryManager&) = delete;
		MemoryManager(MemoryManager&&) = delete;

		~MemoryManager() noexcept = default;

		/// @brief Acquires a temporary buffer.
		/// @param requiredSize Required size.
		/// @param requiredAlignment Required alignment.
		/// @return Temporary buffer.
		[[nodiscard("Pure function")]]
		TempBuffer AcquireTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment) const;
		/// @brief Releases a temporary buffer.
		/// @param buffer Temporary buffer.
		void ReleaseTempBuffer(TempBuffer buffer) const noexcept;

		MemoryManager& operator =(const MemoryManager&) = delete;
		MemoryManager& operator =(MemoryManager&&) = delete;

	private:
		/// @brief Aligned allocator.
		/// @tparam T Placed type.
		template<typename T>
		class AlignedAllocator
		{
		public:
			using value_type = T;
			using is_always_equal = std::false_type;

			/// @brief Creates an aligned allocator.
			/// @param alignment Alignment.
			[[nodiscard("Pure constructor")]]
			explicit AlignedAllocator(std::size_t alignment) noexcept;
			[[nodiscard("Pure constructor")]]
			AlignedAllocator(const AlignedAllocator& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			AlignedAllocator(AlignedAllocator&& other) noexcept = default;
			template<typename U> [[nodiscard("Pure constructor")]]
			explicit AlignedAllocator(const AlignedAllocator<U>& other) noexcept;

			~AlignedAllocator() noexcept = default;

			/// @brief Gets the alignment.
			/// @return Alignment.
			[[nodiscard("Pure function")]]
			std::size_t Alignment() const noexcept;

			/// @brief Allocates a memory.
			/// @param n Object count.
			/// @return Allocated memory.
			[[nodiscard("Pure function")]]
			T* allocate(std::size_t n);
			/// @brief Deallocates the memory.
			/// @param p Memory to deallocate.
			void deallocate(T* p, std::size_t) noexcept;

			AlignedAllocator& operator =(const AlignedAllocator& other) noexcept = default;
			AlignedAllocator& operator =(AlignedAllocator&& other) noexcept = default;

			[[nodiscard("Pure operator")]]
			bool operator ==(const AlignedAllocator& other) const noexcept = default;

		private:
			std::size_t alignment; ///< Alignment.
		};

		/// @brief Buffer cache.
		class Cache final
		{
		public:
			using Buffer = std::vector<std::byte, AlignedAllocator<std::byte>>;

			/// @brief Creates a buffer cache.
			/// @param application Application.
			[[nodiscard("Pure constructor")]]
			explicit Cache(IApplication& application) noexcept;
			Cache(const Cache&) = delete;
			Cache(Cache&&) = delete;

			~Cache() noexcept = default;

			/// @brief Acquires a temporary buffer.
			/// @param requiredSize Required size.
			/// @param requiredAlignment Required alignment.
			/// @return Temporary buffer.
			[[nodiscard("Pure function")]]
			TempBuffer AcquireTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment);
			/// @brief Releases a temporary buffer.
			/// @param buffer Temporary buffer.
			void ReleaseTempBuffer(TempBuffer buffer) noexcept;

			Cache& operator =(const Cache&) = delete;
			Cache& operator =(Cache&&) = delete;

		private:
			/// @brief Gets a suitable buffer.
			/// @param requiredAlignment Required alignment.
			/// @return Buffer.
			[[nodiscard("Pure function")]]
			Buffer GetBuffer(std::size_t requiredAlignment);

			IApplication* application; ///< Application.

			std::stack<Buffer> bufferCache; ///< Buffer cache.
			std::unordered_map<const std::byte*, Buffer> usedBuffers; ///< Buffers that are in use now.
		};

		/// @brief Gets a cache for a current thread.
		/// @param application Application.
		/// @return Cache.
		[[nodiscard("Pure function")]]
		static Cache& GetCache(IApplication& application);

		IApplication* application; ///< Application.
	};
}

namespace PonyEngine::Application
{
	MemoryManager::MemoryManager(IApplication& application) noexcept :
		application{&application}
	{
	}

	TempBuffer MemoryManager::AcquireTempBuffer(const std::size_t requiredSize, const std::size_t requiredAlignment) const
	{
		return GetCache(*application).AcquireTempBuffer(requiredSize, requiredAlignment);
	}

	void MemoryManager::ReleaseTempBuffer(const TempBuffer buffer) const noexcept
	{
		GetCache(*application).ReleaseTempBuffer(buffer);
	}

	MemoryManager::Cache::Cache(IApplication& application) noexcept :
		application{&application}
	{
	}

	TempBuffer MemoryManager::Cache::AcquireTempBuffer(const std::size_t requiredSize, const std::size_t requiredAlignment)
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Acquiring temp buffer... Size: '{}'; Alignment: '{}'.", requiredSize, requiredAlignment);

		if (requiredAlignment < alignof(std::max_align_t) || !std::has_single_bit(requiredAlignment)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid alignment");
		}

		Buffer buffer = GetBuffer(requiredAlignment);
		if (const std::size_t size = std::max(requiredSize, 1024uz); buffer.size() < size) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Growing temp buffer.");
			buffer.resize(size);
		}

		const auto tempBuffer = TempBuffer{.buffer = std::span(buffer.data(), buffer.size())};
		usedBuffers.emplace(buffer.data(), std::move(buffer));

		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Acquiring temp buffer done. Buffer: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(tempBuffer.buffer.data()));

		return tempBuffer;
	}

	void MemoryManager::Cache::ReleaseTempBuffer(const TempBuffer buffer) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Releasing temp buffer... Buffer: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(buffer.buffer.data()));

		const auto position = usedBuffers.find(buffer.buffer.data());
		if (position == usedBuffers.cend()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Fatal, "TempBuffer memory corruption detected. Terminating.");
			std::terminate();
		}

		bufferCache.push(std::move(position->second));
		usedBuffers.erase(position);

		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Releasing temp buffer done.");
	}

	MemoryManager::Cache::Buffer MemoryManager::Cache::GetBuffer(const std::size_t requiredAlignment)
	{
		if (bufferCache.empty()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Creating new temp buffer.");
			return Buffer(AlignedAllocator<std::byte>(requiredAlignment));
		}

		Buffer buffer = std::move(bufferCache.top());
		bufferCache.pop();

		if (buffer.get_allocator().Alignment() < requiredAlignment) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Realigning temp buffer.");
			buffer = Buffer(AlignedAllocator<std::byte>(requiredAlignment));
		}

		return buffer;
	}

	MemoryManager::Cache& MemoryManager::GetCache(IApplication& application)
	{
		thread_local auto cache = std::make_unique<Cache>(application);
		return *cache;
	}

	template<typename T>
	MemoryManager::AlignedAllocator<T>::AlignedAllocator(const std::size_t alignment) noexcept :
		alignment{alignment}
	{
	}

	template<typename T>
	template<typename U>
	MemoryManager::AlignedAllocator<T>::AlignedAllocator(const AlignedAllocator<U>& other) noexcept :
		alignment{other.Alignment()}
	{
	}

	template<typename T>
	std::size_t MemoryManager::AlignedAllocator<T>::Alignment() const noexcept
	{
		return alignment;
	}

	template<typename T>
	T* MemoryManager::AlignedAllocator<T>::allocate(const std::size_t n)
	{
		return static_cast<T*>(operator new[](n * sizeof(T), std::align_val_t{alignment}));
	}

	template<typename T>
	void MemoryManager::AlignedAllocator<T>::deallocate(T* const p, const std::size_t) noexcept
	{
		operator delete[](p, std::align_val_t{alignment});
	}
}
