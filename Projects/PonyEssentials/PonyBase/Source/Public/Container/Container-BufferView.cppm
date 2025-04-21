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

export module PonyBase.Container:BufferView;

import <cstddef>;
import <cstdint>;
import <span>;
import <type_traits>;

import :Buffer;

export namespace PonyBase::Container
{
	/// @brief Buffer wrapper that allows to work with it as an array of a specific type.
	/// @tparam T Data type.
	template<typename T>
	class BufferView final
	{
	public:
		using BufferType = std::conditional_t<std::is_const_v<T>, const Buffer, Buffer>; ///< Buffer type.

		/// @brief Creates an empty buffer view that doesn't point to any buffer.
		[[nodiscard("Pure constructor")]]
		BufferView() noexcept = default;
		/// @brief Creates a buffer view for the @p buffer.
		/// @param buffer Target buffer.
		[[nodiscard("Pure constructor")]]
		explicit BufferView(BufferType& buffer);
		[[nodiscard("Pure constructor")]]
		BufferView(const BufferView& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		BufferView(BufferView&& other) noexcept = default;

		~BufferView() noexcept = default;

		/// @brief Gets the element size.
		/// @return Element size.
		[[nodiscard("Pure function")]]
		static std::uint32_t Stride() noexcept;
		/// @brief Gets the element count.
		/// @return Element count.
		[[nodiscard("Pure function")]]
		std::uint32_t Count() const noexcept;
		/// @brief Gets the buffer size.
		/// @return Buffer size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		/// @brief Gets the buffer data.
		/// @return Buffer data.
		[[nodiscard("Pure function")]]
		T* Data() noexcept;
		/// @brief Gets the buffer data.
		/// @return Buffer data.
		[[nodiscard("Pure function")]]
		const T* Data() const noexcept;
		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		BufferType* Buffer() noexcept;
		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const BufferType* Buffer() const noexcept;

		/// @brief Is the view empty?
		/// @return @a True if it's empty; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsEmpty() const noexcept;

		/// @brief Gets the span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<T> Span() noexcept;
		/// @brief Gets the span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<const T> Span() const noexcept;

		/// @brief @a True if the buffer isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets the object by the @p index.
		/// @param index Object index.
		/// @return Object.
		[[nodiscard("Pure operator")]]
		T& operator [](std::size_t index) noexcept;
		/// @brief Gets the object by the @p index.
		/// @param index Object index.
		/// @return Object.
		[[nodiscard("Pure operator")]]
		const T& operator [](std::size_t index) const noexcept;

		BufferView& operator =(const BufferView& other) noexcept = default;
		BufferView& operator =(BufferView&& other) noexcept = default;

	private:
		BufferType* buffer; ///< Buffer.
	};
}

namespace PonyBase::Container
{
	template<typename T>
	BufferView<T>::BufferView(BufferType& buffer) :
		buffer{&buffer}
	{
		if (this->buffer->Stride() != Stride()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer view is incompatible with buffer.");
		}
	}

	template<typename T>
	std::uint32_t BufferView<T>::Stride() noexcept
	{
		return sizeof(T);
	}

	template<typename T>
	std::uint32_t BufferView<T>::Count() const noexcept
	{
		return buffer ? buffer->Count() : 0u;
	}

	template<typename T>
	std::size_t BufferView<T>::Size() const noexcept
	{
		return static_cast<std::size_t>(Stride()) * Count();
	}

	template<typename T>
	T* BufferView<T>::Data() noexcept
	{
		return buffer ? reinterpret_cast<T*>(buffer->Data()) : nullptr;
	}

	template<typename T>
	const T* BufferView<T>::Data() const noexcept
	{
		return buffer ? reinterpret_cast<const T*>(buffer->Data()) : nullptr;
	}

	template<typename T>
	typename BufferView<T>::BufferType* BufferView<T>::Buffer() noexcept
	{
		return buffer;
	}

	template<typename T>
	const typename BufferView<T>::BufferType* BufferView<T>::Buffer() const noexcept
	{
		return buffer;
	}

	template<typename T>
	bool BufferView<T>::IsEmpty() const noexcept
	{
		return !buffer || buffer->IsEmpty();
	}

	template<typename T>
	std::span<T> BufferView<T>::Span() noexcept
	{
		return buffer ? buffer->template Span<T>() : std::span<T>();
	}

	template<typename T>
	std::span<const T> BufferView<T>::Span() const noexcept
	{
		return buffer ? buffer->template Span<T>() : std::span<T>();
	}

	template<typename T>
	BufferView<T>::operator bool() const noexcept
	{
		return buffer && static_cast<bool>(buffer);
	}

	template<typename T>
	T& BufferView<T>::operator [](const std::size_t index) noexcept
	{
		assert(buffer && "The buffer is nullptr.");

		return buffer->template Get<T>(index);
	}

	template<typename T>
	const T& BufferView<T>::operator [](const std::size_t index) const noexcept
	{
		assert(buffer && "The buffer is nullptr.");

		return buffer->template Get<T>(index);
	}
}
