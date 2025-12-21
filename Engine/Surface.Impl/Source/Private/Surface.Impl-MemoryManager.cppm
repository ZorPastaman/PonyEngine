/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface.Impl:MemoryManager;

import std;

import PonyEngine.Memory;

export namespace PonyEngine::Surface
{
	/// @brief Memory manager.
	class MemoryManager final
	{
	public:
		/// @brief Creates a memory manager.
		/// @param arenaAlignment Arena alignment.
		/// @param arenaSize Arena initial size.
		[[nodiscard("Pure constructor")]]
		MemoryManager(std::size_t arenaAlignment, std::size_t arenaSize);
		MemoryManager(const MemoryManager&) = delete;
		MemoryManager(MemoryManager&&) = delete;

		~MemoryManager() noexcept = default;

		/// @brief Allocates a data that must be used till the next temp allocation.
		/// @tparam T Data type.
		/// @param count Data count.
		/// @return Data span.
		template<Memory::ArenaCompatible T> [[nodiscard("Pure function")]]
		std::span<T> AllocateTemp(std::size_t count) const;

		MemoryManager& operator =(const MemoryManager&) = delete;
		MemoryManager& operator =(MemoryManager&&) = delete;

	private:
		mutable Memory::Arena arena; ///< Arena.
	};
}

namespace PonyEngine::Surface
{
	MemoryManager::MemoryManager(const std::size_t arenaAlignment, const std::size_t arenaSize) :
		arena(arenaAlignment, arenaSize)
	{
	}

	template<Memory::ArenaCompatible T>
	std::span<T> MemoryManager::AllocateTemp(const std::size_t count) const
	{
		arena.Free();
		const Memory::Arena::Slice<T> slice = arena.Allocate<T>(count);

		return arena.Span(slice);
	}
}
