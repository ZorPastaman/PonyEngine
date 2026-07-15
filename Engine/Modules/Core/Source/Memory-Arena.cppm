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

export namespace PonyEngine::Memory
{
	/// @brief Arena memory.
	class Arena final
	{
	public:
		/// @brief Marker. Used to rewind an arena to previous point.
		struct Marker final
		{
			std::size_t mark = 0uz; ///< Mark to rewind to.
		};

		/// @brief Arena scope. Automatically rewinds it on its destruction.
		class Scope final
		{
		public:
			[[nodiscard("Pure constructor")]]
			Scope() noexcept;
			/// @brief Creates a scope.
			/// @param arena Arena.
			/// @param marker Marker to rewind to.
			[[nodiscard("Pure constructor")]]
			Scope(class Arena& arena, const Marker& marker) noexcept;
			Scope(const Scope&) = delete;
			[[nodiscard("Pure constructor")]]
			Scope(Scope&& other) noexcept;

			~Scope() noexcept;

			/// @brief Gets the arena.
			/// @return Arena. May be nullptr.
			[[nodiscard("Pure function")]]
			const class Arena* Arena() const noexcept;
			/// @brief Gets the marker.
			/// @return Marker.
			[[nodiscard("Pure function")]]
			struct Marker Marker() const noexcept;

			/// @brief Releases the scope with rewinding the arena.
			void Release() noexcept;
			/// @brief Releases the scope without rewinding the arena.
			void Forget() noexcept;

			Scope& operator =(const Scope&) = default;
			Scope& operator =(Scope&& other) noexcept;

		private:
			class Arena* arena; ///< Arena.
			struct Marker marker; ///< Marker.
		};

		/// @brief Creates an arena.
		/// @param buffer Buffer.
		[[nodiscard("Pure constructor")]]
		explicit Arena(std::span<std::byte> buffer) noexcept;
		[[nodiscard("Pure constructor")]]
		Arena(const Arena&) = delete;
		[[nodiscard("Pure constructor")]]
		Arena(Arena&&) = delete;

		~Arena() noexcept = default;

		/// @brief Gets the data.
		/// @return Data.
		[[nodiscard("Pure function")]]
		std::byte* Data() noexcept;
		/// @brief Gets the data.
		/// @return Data.
		[[nodiscard("Pure function")]]
		const std::byte* Data() const noexcept;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		/// @brief Gets the capacity.
		/// @return Capacity.
		[[nodiscard("Pure function")]]
		std::size_t Capacity() const noexcept;

		/// @brief Gets a current marker.
		/// @return Marker.
		[[nodiscard("Pure function")]]
		Marker GetMarker() const noexcept;
		/// @brief Gets a current scope.
		/// @return Scope.
		[[nodiscard("Pure function")]]
		Scope GetScope() noexcept;
		/// @brief Rewinds the arena to the marker.
		/// @param marker Marker to rewind to.
		void Rewind(Marker marker = Marker{}) noexcept;

		/// @brief Allocates a memory for an object.
		/// @param objectAlignment Object alignment.
		/// @param objectSize Object size.
		/// @return Object place.
		void* AllocateObject(std::size_t objectAlignment, std::size_t objectSize);
		/// @brief Allocates a memory for an object.
		/// @tparam T Object type.
		/// @return Object place.
		template<typename T>
		T* AllocateObject();
		/// @brief Allocates a memory for an object and creates it there.
		/// @tparam T Object type.
		/// @tparam Args Object constructor argument types.
		/// @param args Object constructor arguments.
		/// @return Object.
		template<typename T, typename... Args> requires std::constructible_from<T, Args...>
		T* CreateObject(Args&&... args);

		/// @brief Allocates a memory for an array.
		/// @param objectAlignment Array element alignment.
		/// @param objectSize Array element size.
		/// @param count Array element count.
		/// @return Array place.
		void* AllocateArray(std::size_t objectAlignment, std::size_t objectSize, std::size_t count);
		/// @brief Allocates a memory for an array.
		/// @tparam T Array element type.
		/// @param count Array element count.
		/// @return Array place.
		template<typename T>
		std::span<T> AllocateArray(std::size_t count);
		/// @brief Allocates a memory for an array and creates its elements there.
		/// @tparam T Array element type.
		/// @tparam Args Array element constructor argument types.
		/// @param count Array element count.
		/// @param args Array element constructor arguments.
		/// @return Array.
		template<typename T, typename... Args> requires std::constructible_from<T, Args...>
		std::span<T> CreateArray(std::size_t count, Args&&... args);

		Arena& operator =(const Arena&) = delete;
		Arena& operator =(Arena&&) = delete;

	private:
		std::span<std::byte> buffer; ///< Memory buffer.
		std::size_t size; ///< Data size.
	};
}

namespace PonyEngine::Memory
{
	Arena::Scope::Scope() noexcept :
		arena{nullptr}
	{
	}

	Arena::Scope::Scope(class Arena& arena, const struct Marker& marker) noexcept :
		arena{&arena},
		marker(marker)
	{
	}

	Arena::Scope::Scope(Scope&& other) noexcept :
		arena{other.arena},
		marker(other.marker)
	{
		other.Forget();
	}

	Arena::Scope::~Scope() noexcept
	{
		Release();
	}

	const class Arena* Arena::Scope::Arena() const noexcept
	{
		return arena;
	}

	struct Arena::Marker Arena::Scope::Marker() const noexcept
	{
		return marker;
	}

	void Arena::Scope::Release() noexcept
	{
		if (arena)
		{
			arena->Rewind(marker);
			Forget();
		}
	}

	void Arena::Scope::Forget() noexcept
	{
		arena = nullptr;
	}

	Arena::Scope& Arena::Scope::operator =(Scope&& other) noexcept
	{
		Release();
		arena = other.arena;
		other.Forget();
		return *this;
	}

	Arena::Arena(const std::span<std::byte> buffer) noexcept :
		buffer(buffer),
		size{0uz}
	{
	}

	std::byte* Arena::Data() noexcept
	{
		return buffer.data();
	}

	const std::byte* Arena::Data() const noexcept
	{
		return buffer.data();
	}

	std::size_t Arena::Size() const noexcept
	{
		return size;
	}

	std::size_t Arena::Capacity() const noexcept
	{
		return buffer.size();
	}

	Arena::Marker Arena::GetMarker() const noexcept
	{
		return Marker{.mark = size};
	}

	Arena::Scope Arena::GetScope() noexcept
	{
		return Scope(*this, GetMarker());
	}

	void Arena::Rewind(const Marker marker) noexcept
	{
		assert(marker.mark <= size && "Invalid rewind call.");
		size = marker.mark;
	}

	void* Arena::AllocateObject(const std::size_t objectAlignment, const std::size_t objectSize)
	{
		void* pointer = buffer.data() + size;
		std::size_t space = buffer.size() - size;
		if (!std::align(objectAlignment, objectSize, pointer, space)) [[unlikely]]
		{
			throw std::bad_alloc();
		}

		size = buffer.size() - space + objectSize;

		return pointer;
	}

	template<typename T>
	T* Arena::AllocateObject()
	{
		return static_cast<T*>(AllocateObject(alignof(T), sizeof(T)));
	}

	template<typename T, typename... Args> requires std::constructible_from<T, Args...>
	T* Arena::CreateObject(Args&&... args)
	{
		const std::size_t prevSize = size;
		T* const object = AllocateObject<T>();

		try
		{
			return std::construct_at(object, std::forward<Args>(args)...);
		}
		catch (...)
		{
			size = prevSize;
			throw;
		}
	}

	void* Arena::AllocateArray(const std::size_t objectAlignment, const std::size_t objectSize, const std::size_t count)
	{
		return AllocateObject(objectAlignment, objectSize * count);
	}

	template<typename T>
	std::span<T> Arena::AllocateArray(const std::size_t count)
	{
		return std::span<T>(static_cast<T*>(AllocateArray(alignof(T), sizeof(T), count)), count);
	}

	template<typename T, typename... Args> requires std::constructible_from<T, Args...>
	std::span<T> Arena::CreateArray(const std::size_t count, Args&&... args)
	{
		const std::size_t prevSize = size;
		const std::span<T> array = AllocateArray<T>(count);

		std::size_t constructed = 0uz;
		try
		{
			for (; constructed < count; ++constructed)
			{
				std::construct_at(&array[constructed], std::forward<Args>(args)...);
			}
		}
		catch (...)
		{
			while (constructed-- > 0uz)
			{
				std::destroy_at(&array[constructed]);
			}

			size = prevSize;
			throw;
		}

		return array;
	}
}
