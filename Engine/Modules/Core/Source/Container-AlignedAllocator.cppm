/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Container:AlignedAllocator;

import std;

export namespace PonyEngine::Container
{
	/// @brief Aligned allocator.
	/// @tparam T Placed type.
	template<typename T>
	class AlignedAllocator
	{
	public:
		using value_type = T;
		using is_always_equal = std::false_type;
		using propagate_on_container_copy_assignment = std::false_type;
		using propagate_on_container_move_assignment = std::true_type;
		using propagate_on_container_swap = std::true_type;

		/// @brief Creates an aligned allocator.
		/// @param alignment Alignment.
		[[nodiscard("Pure constructor")]]
		explicit AlignedAllocator(std::size_t alignment);
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
		/// @param n Object count.
		void deallocate(T* p, std::size_t n) noexcept;

		AlignedAllocator& operator =(const AlignedAllocator& other) noexcept = default;
		AlignedAllocator& operator =(AlignedAllocator&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const AlignedAllocator& other) const noexcept = default;

	private:
		std::size_t alignment; ///< Alignment.
	};
}

namespace PonyEngine::Container
{
	template<typename T>
	AlignedAllocator<T>::AlignedAllocator(const std::size_t alignment) :
		alignment{alignment}
	{
		if (!std::has_single_bit(this->alignment)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid alignment");
		}
	}

	template<typename T>
	template<typename U>
	AlignedAllocator<T>::AlignedAllocator(const AlignedAllocator<U>& other) noexcept :
		alignment{other.Alignment()}
	{
	}

	template<typename T>
	std::size_t AlignedAllocator<T>::Alignment() const noexcept
	{
		return alignment;
	}

	template<typename T>
	T* AlignedAllocator<T>::allocate(const std::size_t n)
	{
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) [[unlikely]]
		{
			throw std::bad_array_new_length();
		}

		return static_cast<T*>(operator new[](n * sizeof(T), std::align_val_t{ alignment }));
	}

	template<typename T>
	void AlignedAllocator<T>::deallocate(T* const p, const std::size_t n) noexcept
	{
		operator delete[](p, n * sizeof(T), std::align_val_t{alignment});
	}
}
