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

export module PonyBase.Container:Buffer;

import <cstddef>;
import <cstdint>;
import <cstring>;
import <memory>;
import <span>;
import <stdexcept>;
import <utility>;

import :BufferParams;

export namespace PonyBase::Container
{
	/// @brief Buffer container. It contains a fixed-size heap of bytes.
	class Buffer final
	{
	public:
		/// @brief Creates a nullptr buffer.
		[[nodiscard("Pure constructor")]]
		Buffer() noexcept = default;
		/// @brief Creates a buffer.
		/// @param stride Element size.
		/// @param count Element count.
		[[nodiscard("Pure constructor")]]
		Buffer(std::uint32_t stride, std::uint32_t count);
		/// @brief Creates a buffer.
		/// @param params Buffer parameters.
		[[nodiscard("Pure constructor")]]
		explicit Buffer(const BufferParams& params);
		/// @brief Creates a buffer and copies the @p data into it.
		/// @param stride Element size.
		/// @param data Data to copy from. If its size isn't a multiple of the @p stride, the trail is ignored.
		[[nodiscard("Pure constructor")]]
		Buffer(std::uint32_t stride, std::span<const std::byte> data);
		/// @brief Creates a buffer and copies data from the @p other.
		/// @param other Copied buffer.
		[[nodiscard("Pure constructor")]]
		Buffer(const Buffer& other);
		[[nodiscard("Pure constructor")]]
		Buffer(Buffer&& other) noexcept = default;

		/// @brief Creates a buffer that can have elements of type @p T and count of the @p count.
		/// @tparam T Element type.
		/// @param count Element count.
		/// @return Created buffer.
		template<typename T> [[nodiscard("Pure function")]]
		static Buffer Create(std::uint32_t count);
		/// @brief Creates a buffer and initializes it with a copy of the @p span.
		/// @tparam T Element type.
		/// @param span Data source. The size can't exceed uint32 max value.
		/// @return Created buffer.
		template<typename T> [[nodiscard("Pure function")]]
		static Buffer Create(std::span<const T> span);

		~Buffer() noexcept = default;

		/// @brief Gets the element size.
		/// @return Element size.
		[[nodiscard("Pure function")]]
		std::uint32_t Stride() const noexcept;
		/// @brief Gets the element count.
		/// @return Element count.
		[[nodiscard("Pure function")]]
		std::uint32_t Count() const noexcept;
		/// @brief Gets the buffer size.
		/// @return Buffer size in bytes.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		/// @brief Gets the buffer data.
		/// @return Buffer data.
		[[nodiscard("Pure function")]]
		std::byte* Data() noexcept;
		/// @brief Gets the buffer data.
		/// @return Buffer data.
		[[nodiscard("Pure function")]]
		const std::byte* Data() const noexcept;

		/// @brief Is the buffer empty?
		/// @return @a True if it's empty; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsEmpty() const noexcept;

		/// @brief Gets a part of the buffer as an objects of type @p T.
		/// @tparam T Object type. Its size must be @ Stride().
		/// @param index Object index.
		/// @return Object.
		template<typename T> [[nodiscard("Pure function")]]
		T& Get(std::size_t index) noexcept;
		/// @brief Gets a part of the buffer as an objects of type @p T.
		/// @tparam T Object type. Its size must be @ Stride().
		/// @param index Object index.
		/// @return Object.
		template<typename T> [[nodiscard("Pure function")]]
		const T& Get(std::size_t index) const noexcept;

		/// @brief Gets a buffer as a span of type @p T.
		/// @tparam T Object type. Its size must be @ Stride().
		/// @return Span.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<T> Span() noexcept;
		/// @brief Gets a buffer as a span of type @p T.
		/// @tparam T Object type. Its size must be @ Stride().
		/// @return Span.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Span() const noexcept;

		/// @brief Copies data from the @p source.
		/// @param source Data source. Its stride and count must be the same as the stride and count if this buffer.
		void CopyFrom(const Buffer& source);

		/// @brief @a True if the buffer isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Copies the @p other into this.
		/// @param other Copy source.
		/// @return @a This.
		Buffer& operator =(const Buffer& other);
		Buffer& operator =(Buffer&& other) noexcept = default;

	private:
		std::uint32_t stride; ///< Element size.
		std::uint32_t count; ///< Element count.
		std::unique_ptr<std::byte[]> data; ///< Data.
	};
}

namespace PonyBase::Container
{
	Buffer::Buffer(const std::uint32_t stride, const std::uint32_t count) :
		stride{stride},
		count{count},
		data(std::make_unique<std::byte[]>(Size()))
	{
	}

	Buffer::Buffer(const BufferParams& params) :
		Buffer(params.stride, params.count)
	{
	}

	Buffer::Buffer(const std::uint32_t stride, const std::span<const std::byte> data) :
		stride{stride},
		count{static_cast<std::uint32_t>(data.size() / stride)},
		data(std::make_unique<std::byte[]>(Size()))
	{
		std::memcpy(this->data.get(), data.data(), Size());
	}

	Buffer::Buffer(const Buffer& other) :
		Buffer(other.stride, other.count)
	{
		std::memcpy(data.get(), other.data.get(), Size());
	}

	template<typename T>
	Buffer Buffer::Create(const std::uint32_t count)
	{
		return Buffer(sizeof(T), count);
	}

	template<typename T>
	Buffer Buffer::Create(const std::span<const T> span)
	{
		auto buffer = Create<T>(static_cast<std::uint32_t>(span.size()));
		std::memcpy(buffer.Data(), span.data(), buffer.Size());

		return buffer;
	}

	std::uint32_t Buffer::Stride() const noexcept
	{
		return stride;
	}

	std::uint32_t Buffer::Count() const noexcept
	{
		return count;
	}

	std::size_t Buffer::Size() const noexcept
	{
		return static_cast<std::size_t>(stride) * count;
	}

	std::byte* Buffer::Data() noexcept
	{
		return data.get();
	}

	const std::byte* Buffer::Data() const noexcept
	{
		return data.get();
	}

	bool Buffer::IsEmpty() const noexcept
	{
		return count == 0u;
	}

	template<typename T>
	T& Buffer::Get(const std::size_t index) noexcept
	{
		assert(sizeof(T) == stride && "Incorrect type.");

		return reinterpret_cast<T*>(data.get())[index];
	}

	template<typename T>
	const T& Buffer::Get(std::size_t index) const noexcept
	{
		assert(sizeof(T) == stride && "Incorrect type.");

		return reinterpret_cast<const T*>(data.get())[index];
	}

	template<typename T>
	std::span<T> Buffer::Span() noexcept
	{
		assert(sizeof(T) == stride && "Incorrect type.");

		return std::span<T>(reinterpret_cast<T*>(data.get()), count);
	}

	template<typename T>
	std::span<const T> Buffer::Span() const noexcept
	{
		assert(sizeof(T) == stride && "Incorrect type.");

		return std::span<const T>(reinterpret_cast<const T*>(data.get()), count);
	}

	void Buffer::CopyFrom(const Buffer& source)
	{
		if (stride != source.stride || count != source.count) [[unlikely]]
		{
			throw std::invalid_argument("Buffers are incompatible.");
		}

		std::memcpy(data.get(), source.data.get(), Size());
	}

	Buffer::operator bool() const noexcept
	{
		return static_cast<bool>(data);
	}

	Buffer& Buffer::operator =(const Buffer& other)
	{
		auto newData = std::make_unique<std::byte[]>(other.Size());
		std::memcpy(newData.get(), other.data.get(), other.Size());

		stride = other.stride;
		count = other.count;
		data = std::move(newData);

		return *this;
	}
}
