/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Container:Buffer;

import <cstddef>;
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
		Buffer(std::size_t stride, std::size_t count);
		/// @brief Creates a buffer.
		/// @param params Buffer parameters.
		[[nodiscard("Pure constructor")]]
		explicit Buffer(const BufferParams& params);
		/// @brief Creates a buffer and copies the @p data into it.
		/// @param stride Element size.
		/// @param data Data to copy from. If its size isn't a multiple of the @p stride, the trail is ignored.
		[[nodiscard("Pure constructor")]]
		Buffer(std::size_t stride, std::span<const std::byte> data);
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
		static Buffer Create(std::size_t count);
		/// @brief Creates a buffer and initializes it with a copy of the @p span.
		/// @tparam T Element type.
		/// @param span Data source.
		/// @return Created buffer.
		template<typename T> [[nodiscard("Pure function")]]
		static Buffer Create(std::span<const T> span);

		~Buffer() noexcept = default;

		/// @brief Gets the element size.
		/// @return Element size.
		[[nodiscard("Pure function")]]
		std::size_t Stride() const noexcept;
		/// @brief Gets the element count.
		/// @return Element count.
		[[nodiscard("Pure function")]]
		std::size_t Count() const noexcept;
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
		/// @tparam T Object type. Its size must be a factor of @p Stride.
		/// @param index Object index.
		/// @return Object.
		template<typename T> [[nodiscard("Pure function")]]
		T& Get(std::size_t index);
		/// @brief Gets a part of the buffer as an objects of type @p T.
		/// @tparam T Object type. Its size must be a factor of @p Stride.
		/// @param index Object index.
		/// @return Object.
		template<typename T> [[nodiscard("Pure function")]]
		const T& Get(std::size_t index) const;

		/// @brief Gets a raw span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<std::byte> Span() noexcept; // TODO: Add tests for new functions.
		/// @brief Gets a raw span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> Span() const noexcept;
		/// @brief Gets a buffer as a span of type @p T.
		/// @tparam T Object type. Its size must be a factor of @p Stride.
		/// @return Span.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<T> Span();
		/// @brief Gets a buffer as a span of type @p T.
		/// @tparam T Object type. Its size must be a factor of @p Stride.
		/// @return Span.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Span() const;
		/// @brief Gets a raw span.
		/// @param strideIndex Stride index.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<std::byte> Span(std::size_t strideIndex) noexcept;
		/// @brief Gets a raw span.
		/// @param strideIndex Stride index.
		/// @return Span.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> Span(std::size_t strideIndex) const noexcept;
		/// @brief Gets a buffer stride as a span of type @p T.
		/// @tparam T Object type. Its size must be a factor of @p Stride.
		/// @param strideIndex Stride index.
		/// @return Span.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<T> Span(std::size_t strideIndex);
		/// @brief Gets a buffer stride as a span of type @p T.
		/// @tparam T Object type. Its size must be a factor of @p Stride.
		/// @param strideIndex Stride index.
		/// @return Span.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Span(std::size_t strideIndex) const;

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
		std::size_t stride; ///< Element size.
		std::size_t count; ///< Element count.
		std::unique_ptr<std::byte[]> data; ///< Data.
	};
}

namespace PonyBase::Container
{
	Buffer::Buffer(const std::size_t stride, const std::size_t count) :
		stride{stride},
		count{count},
		data(std::make_unique<std::byte[]>(Size()))
	{
	}

	Buffer::Buffer(const BufferParams& params) :
		Buffer(params.stride, params.count)
	{
	}

	Buffer::Buffer(const std::size_t stride, const std::span<const std::byte> data) :
		stride{stride},
		count{data.size() / stride},
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
	Buffer Buffer::Create(const std::size_t count)
	{
		return Buffer(sizeof(T), count);
	}

	template<typename T>
	Buffer Buffer::Create(const std::span<const T> span)
	{
		auto buffer = Create<T>(span.size());
		std::memcpy(buffer.Data(), span.data(), buffer.Size());

		return buffer;
	}

	std::size_t Buffer::Stride() const noexcept
	{
		return stride;
	}

	std::size_t Buffer::Count() const noexcept
	{
		return count;
	}

	std::size_t Buffer::Size() const noexcept
	{
		return stride * count;
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
	T& Buffer::Get(const std::size_t index)
	{
		if (sizeof(T) > stride || stride % sizeof(T)) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect type.");
		}
		if (index > Size() / sizeof(T)) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}

		return reinterpret_cast<T*>(data.get())[index];
	}

	template<typename T>
	const T& Buffer::Get(std::size_t index) const
	{
		if (sizeof(T) > stride || stride % sizeof(T)) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect type.");
		}
		if (index > Size() / sizeof(T)) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}

		return reinterpret_cast<const T*>(data.get())[index];
	}

	std::span<std::byte> Buffer::Span() noexcept
	{
		return std::span(data.get(), Size());
	}

	std::span<const std::byte> Buffer::Span() const noexcept
	{
		return std::span(data.get(), Size());
	}

	template<typename T>
	std::span<T> Buffer::Span()
	{
		if (sizeof(T) > stride || stride % sizeof(T)) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect type.");
		}

		return std::span<T>(reinterpret_cast<T*>(data.get()), Size() / sizeof(T));
	}

	template<typename T>
	std::span<const T> Buffer::Span() const
	{
		if (sizeof(T) > stride || stride % sizeof(T)) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect type.");
		}

		return std::span<const T>(reinterpret_cast<const T*>(data.get()), Size() / sizeof(T));
	}

	std::span<std::byte> Buffer::Span(const std::size_t strideIndex) noexcept
	{
		return std::span(data.get() + strideIndex * stride, stride);
	}

	std::span<const std::byte> Buffer::Span(const std::size_t strideIndex) const noexcept
	{
		return std::span(data.get() + strideIndex * stride, stride);
	}

	template <typename T>
	std::span<T> Buffer::Span(const std::size_t strideIndex) // TODO: Update tests
	{
		if (strideIndex >= count) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}
		if (sizeof(T) > stride || stride % sizeof(T)) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect type.");
		}

		return std::span<T>(reinterpret_cast<T*>(data.get() + strideIndex * stride), stride);
	}

	template <typename T>
	std::span<const T> Buffer::Span(const std::size_t strideIndex) const
	{
		if (strideIndex >= count) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}
		if (sizeof(T) > stride || stride % sizeof(T)) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect type.");
		}

		return std::span<T>(reinterpret_cast<const T*>(data.get() + strideIndex * stride), stride);
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
