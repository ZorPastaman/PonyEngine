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

import <cmath>;
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
	class Buffer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Buffer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Buffer(std::uint32_t stride, std::uint32_t count);
		[[nodiscard("Pure constructor")]]
		explicit Buffer(const BufferParams& params);
		[[nodiscard("Pure constructor")]]
		Buffer(std::uint32_t stride, std::span<const std::byte> data);
		[[nodiscard("Pure constructor")]]
		Buffer(const Buffer& other);
		[[nodiscard("Pure constructor")]]
		Buffer(Buffer&& other) noexcept = default;

		template<typename T> [[nodiscard("Pure function")]]
		static Buffer Create(std::uint32_t objectCount);
		template<typename T> [[nodiscard("Pure function")]]
		static Buffer Create(std::span<const T> span);

		~Buffer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::uint32_t Stride() const noexcept;
		[[nodiscard("Pure function")]]
		std::uint32_t Count() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		[[nodiscard("Pure function")]]
		std::byte* Data() noexcept;
		[[nodiscard("Pure function")]]
		const std::byte* Data() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsEmpty() const noexcept;

		template<typename T> [[nodiscard("Pure function")]]
		T& Get(std::size_t index) noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		const T& Get(std::size_t index) const noexcept;

		template<typename T> [[nodiscard("Pure function")]]
		std::span<T> Span() noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Span() const noexcept;

		void CopyFrom(const Buffer& source);

		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		Buffer& operator =(const Buffer& other) noexcept;
		Buffer& operator =(Buffer&& other) noexcept = default;

	private:
		std::uint32_t stride;
		std::uint32_t count;
		std::unique_ptr<std::byte[]> data;
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
	Buffer Buffer::Create(const std::uint32_t objectCount)
	{
		return Buffer(sizeof(T), objectCount);
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

	Buffer& Buffer::operator =(const Buffer& other) noexcept
	{
		auto newData = std::make_unique<std::byte[]>(other.Size());
		std::memcpy(newData.get(), other.data.get(), other.Size());

		stride = other.stride;
		count = other.count;
		data = std::move(newData);

		return *this;
	}
}
