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
import <stdexcept>;

import :Buffer;

export namespace PonyBase::Container
{
	template<typename T>
	class BufferView final
	{
	public:
		[[nodiscard("Pure constructor")]]
		BufferView() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit BufferView(class Buffer* buffer);
		[[nodiscard("Pure constructor")]]
		BufferView(const BufferView& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		BufferView(BufferView&& other) noexcept = default;

		~BufferView() noexcept = default;

		[[nodiscard("Pure function")]]
		static std::uint32_t Stride() noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t Count() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t Size() const noexcept;
		[[nodiscard("Pure function")]]
		T* Data();
		[[nodiscard("Pure function")]]
		const T* Data() const;
		[[nodiscard("Pure function")]]
		class Buffer* Buffer() noexcept;
		[[nodiscard("Pure function")]]
		const class Buffer* Buffer() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsEmpty() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<T> Span() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const T> Span() const noexcept;

		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		T& operator [](std::size_t index) noexcept;
		[[nodiscard("Pure operator")]]
		const T& operator [](std::size_t index) const noexcept;

		BufferView& operator =(const BufferView& other) noexcept = default;
		BufferView& operator =(BufferView&& other) noexcept = default;

	private:
		class Buffer* buffer;
	};
}

namespace PonyBase::Container
{
	template<typename T>
	BufferView<T>::BufferView(class Buffer* const buffer) :
		buffer{buffer}
	{
		if (this->buffer && this->buffer->Stride() != Stride()) [[unlikely]]
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
	std::uint32_t BufferView<T>::Size() const noexcept
	{
		return Stride() * Count();
	}

	template<typename T>
	T* BufferView<T>::Data()
	{
		return buffer ? buffer->Data() : nullptr;
	}

	template<typename T>
	const T* BufferView<T>::Data() const
	{
		return buffer ? buffer->Data() : nullptr;
	}

	template<typename T>
	class Buffer* BufferView<T>::Buffer() noexcept
	{
		return buffer;
	}

	template<typename T>
	const class Buffer* BufferView<T>::Buffer() const noexcept
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
		return buffer ? buffer->Span<T>() : std::span<T>();
	}

	template<typename T>
	std::span<const T> BufferView<T>::Span() const noexcept
	{
		return buffer ? buffer->Span<T>() : std::span<T>();
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

		return buffer->Get<T>(index);
	}

	template<typename T>
	const T& BufferView<T>::operator [](const std::size_t index) const noexcept
	{
		assert(buffer && "The buffer is nullptr.");

		return buffer->Get<T>(index);
	}
}
