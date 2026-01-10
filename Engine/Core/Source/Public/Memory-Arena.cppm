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

export module PonyEngine.Memory:Arena;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Memory
{
	/// @brief The concept is satisfied for pure data types.
	template<typename T>
	concept ArenaCompatible = std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T>;

	/// @brief Arena memory.
	/// @details It's a contiguous memory array that can automatically grow.
	///          It works only with pure data types - it allows fast allocations and deallocations.
	class Arena final
	{
	public:
		/// @brief Size marker that can be used to free an arena to this point.
		struct Marker final
		{
			std::size_t index = 0uz; ///< Marker index. Only an arena may use it.
		};
		/// @brief Data slice.
		/// @tparam T Data type.
		/// @details Because an arena can grow, it would invalidate all previously created spans.
		///          That's why you should use slices - they keep indices. You can get current spans via functions in an arena.
		template<ArenaCompatible T>
		struct Slice final
		{
			std::size_t byteOffset = 0uz; ///< Offset in bytes.
			std::size_t objectCount = 0uz; ///< Count of objects of type @p T.
		};

		/// @brief Creates an arena.
		/// @param alignment Arena array alignment. It must be at least an alignment of @p std::max_align_t.
		/// @param reserve Reserve size.
		[[nodiscard("Pure constructor")]]
		explicit Arena(std::size_t alignment, std::size_t reserve = 0uz);
		[[nodiscard("Pure constructor")]]
		Arena(const Arena& other);
		[[nodiscard("Pure constructor")]]
		Arena(Arena&& other) noexcept = default;

		~Arena() noexcept = default;

		/// @brief Gets the alignment.
		/// @return Alignment.
		[[nodiscard("Pure function")]]
		std::size_t Alignment() const noexcept;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		/// @brief Gets the capacity.
		/// @return Capacity.
		[[nodiscard("Pure function")]]
		std::size_t Capacity() const noexcept;

		/// @brief Reserves memory.
		/// @param reserve Byte count to reserve.
		void Reserve(std::size_t reserve);
		/// @brief Realigns the arena.
		/// @param alignment New alignment.
		/// @note It can only increase the alignment.
		void Realign(std::size_t alignment);

		/// @brief Gets a marker.
		/// @details This marker can be used later to free the arena to a current point.
		/// @return Marker.
		[[nodiscard("Pure function")]]
		Marker GetMarker() const noexcept;

		/// @brief Gets a data span.
		/// @tparam T Data type.
		/// @param slice Data slice.
		/// @return Data span.
		template<ArenaCompatible T> [[nodiscard("Pure function")]]
		std::span<T> Span(const Slice<T>& slice) noexcept;
		/// @brief Gets a data span.
		/// @tparam T Data type.
		/// @param slice Data slice.
		/// @return Data span.
		template<ArenaCompatible T> [[nodiscard("Pure function")]]
		std::span<const T> Span(const Slice<T>& slice) const noexcept;

		/// @brief Gets the data pointer.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		std::byte* Data() noexcept;
		/// @brief Gets the data pointer.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		const std::byte* Data() const noexcept;

		/// @brief Allocates new data.
		/// @param alignment Data alignment. It must be power of two and can't be more than the arena alignment.
		/// @param size Data size.
		/// @param count Data count.
		/// @return Data slice.
		[[nodiscard("Weird call")]]
		Slice<std::byte> Allocate(std::size_t alignment, std::size_t size, std::size_t count);
		/// @brief Allocates new data.
		/// @tparam T Data type.
		/// @param count Data count.
		/// @return Data slice.
		template<ArenaCompatible T> [[nodiscard("Weird call")]]
		Slice<T> Allocate(std::size_t count);

		/// @brief Frees all the data.
		void Free() noexcept;
		/// @brief Frees data to the @p marker point.
		/// @param marker Marker.
		void Free(Marker marker) noexcept;

		Arena& operator =(const Arena& other);
		Arena& operator =(Arena&& other) noexcept = default;

	private:
		/// @brief Data deleter.
		struct DataDeleter final
		{
			std::size_t alignment; ///< Data alignment.

			void operator ()(std::byte* ptr) const noexcept;
		};

		/// @brief Creates data array.
		/// @param alignment Data alignment.
		/// @param size Data size.
		/// @return Data array.
		[[nodiscard("Pure function")]]
		static std::unique_ptr<std::byte[], DataDeleter> CreateData(std::size_t alignment, std::size_t size);
		/// @brief Allocates new data.
		/// @param alignment Data alignment. It must be power of two and can't be more than the arena alignment.
		/// @param size Data size.
		/// @param count Data count.
		/// @return Data slice.
		[[nodiscard("Weird call")]]
		Slice<std::byte> AllocateRaw(std::size_t alignment, std::size_t size, std::size_t count);

		std::unique_ptr<std::byte[], DataDeleter> data; ///< Data array.
		std::size_t capacity; ///< Data capacity.
		std::size_t size; ///< Data size.
	};
}

namespace PonyEngine::Memory
{
	Arena::Arena(const std::size_t alignment, const std::size_t reserve)
	{
		const std::size_t actualAlignment = std::bit_ceil(std::max(alignment, alignof(std::max_align_t)));
		data = CreateData(actualAlignment, reserve);
		capacity = reserve;
		size = 0uz;
	}

	Arena::Arena(const Arena& other) :
		Arena(other.Alignment(), other.Size())
	{
		std::memcpy(data.get(), other.Data(), Capacity());
		size = Capacity();
	}

	std::size_t Arena::Alignment() const noexcept
	{
		return data.get_deleter().alignment;
	}

	std::size_t Arena::Size() const noexcept
	{
		return size;
	}

	std::size_t Arena::Capacity() const noexcept
	{
		return capacity;
	}

	void Arena::Reserve(const std::size_t reserve)
	{
		if (reserve <= capacity)
		{
			return;
		}

		std::unique_ptr<std::byte[], DataDeleter> newData = CreateData(Alignment(), reserve);
		std::memcpy(newData.get(), data.get(), size);
		data = std::move(newData);
		capacity = reserve;
	}

	void Arena::Realign(const std::size_t alignment)
	{
		if (alignment <= Alignment())
		{
			return;
		}

		std::unique_ptr<std::byte[], DataDeleter> newData = CreateData(alignment, capacity);
		std::memcpy(newData.get(), data.get(), size);
		data = std::move(newData);
	}

	Arena::Marker Arena::GetMarker() const noexcept
	{
		return Marker{.index = size};
	}

	template<ArenaCompatible T>
	std::span<T> Arena::Span(const Slice<T>& slice) noexcept
	{
		assert((slice.byteOffset + sizeof(T) * slice.objectCount <= size) && "Out of range.");
		return std::span<T>(reinterpret_cast<T*>(&data[slice.byteOffset]), slice.objectCount);
	}

	template<ArenaCompatible T>
	std::span<const T> Arena::Span(const Slice<T>& slice) const noexcept
	{
		assert((slice.byteOffset + sizeof(T) * slice.objectCount <= size) && "Out of range.");
		return std::span<const T>(reinterpret_cast<const T*>(&data[slice.byteOffset]), slice.objectCount);
	}

	std::byte* Arena::Data() noexcept
	{
		return data.get();
	}

	const std::byte* Arena::Data() const noexcept
	{
		return data.get();
	}

	Arena::Slice<std::byte> Arena::Allocate(const std::size_t alignment, const std::size_t size, const std::size_t count)
	{
		if (alignment > Alignment()) [[unlikely]]
		{
			throw std::invalid_argument("Alignment of allocation is greater than alignment of arena");
		}
		if (!std::has_single_bit(alignment)) [[unlikely]]
		{
			throw std::invalid_argument("Alignment is not power of two");
		}
		if (size < alignment) [[unlikely]]
		{
			throw std::invalid_argument("Size doesn't match alignment");
		}

		return AllocateRaw(alignment, size, count);
	}

	template<ArenaCompatible T>
	Arena::Slice<T> Arena::Allocate(const std::size_t count)
	{
		if (alignof(T) > Alignment()) [[unlikely]]
		{
			throw std::invalid_argument("Alignment of allocation is greater than alignment of arena");
		}

		const Slice<std::byte> byteSlice = AllocateRaw(alignof(T), sizeof(T), count);
		return Slice<T>{.byteOffset = byteSlice.byteOffset, .objectCount = count};
	}

	void Arena::Free() noexcept
	{
		size = 0uz;
	}

	void Arena::Free(const Marker marker) noexcept
	{
		assert(marker.index <= size && "Out of range.");
		size = marker.index;
	}

	Arena& Arena::operator =(const Arena& other)
	{
		Arena buffer = other;
		return *this = std::move(buffer);
	}

	void Arena::DataDeleter::operator ()(std::byte* const ptr) const noexcept
	{
		operator delete[](ptr, std::align_val_t{alignment});
	}

	std::unique_ptr<std::byte[], Arena::DataDeleter> Arena::CreateData(const std::size_t alignment, const std::size_t size)
	{
		return std::unique_ptr<std::byte[], DataDeleter>(static_cast<std::byte*>(operator new[](size, std::align_val_t{alignment})), DataDeleter{.alignment = alignment});
	}

	Arena::Slice<std::byte> Arena::AllocateRaw(const std::size_t alignment, const std::size_t size, const std::size_t count)
	{
		const std::size_t byteCount = size * count;
		if (byteCount == 0uz)
		{
			return Slice<std::byte>{};
		}

		const std::size_t offset = Math::Align(this->size, alignment);
		const std::size_t newSize = offset + byteCount;
		if (newSize > capacity)
		{
			Reserve(std::bit_ceil(newSize));
		}

		this->size = newSize;

		return Slice<std::byte>{.byteOffset = offset, .objectCount = byteCount};
	}
}
