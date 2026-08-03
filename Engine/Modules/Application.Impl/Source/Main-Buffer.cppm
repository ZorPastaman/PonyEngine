/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:Buffer;

import std;

import PonyEngine.Application;
import PonyEngine.Container;
import PonyEngine.Math;

export namespace PonyEngine::Application
{
	/// @brief Buffer.
	class Buffer final : public IBuffer
	{
	public:
		/// @brief Creates a buffer.
		/// @param buffer Buffer data.
		[[nodiscard("Pure constructor")]]
		explicit Buffer(std::vector<std::byte, Container::AlignedAllocator<std::byte>>&& buffer) noexcept;
		Buffer(const Buffer&) = delete;
		[[nodiscard("Pure constructor")]]
		Buffer(Buffer&& other) noexcept = default;

		~Buffer() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::span<std::byte> Span() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::byte> Span() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Alignment() const noexcept override;

		/// @brief Gets the buffer data.
		/// @return Buffer data.
		[[nodiscard("Pure function")]]
		std::vector<std::byte, Container::AlignedAllocator<std::byte>>& Data() noexcept;

		Buffer& operator =(const Buffer&) = delete;
		Buffer& operator =(Buffer&& other) noexcept = default;

	private:
		std::vector<std::byte, Container::AlignedAllocator<std::byte>> buffer; ///< Buffer data.
	};
}

namespace PonyEngine::Application
{
	Buffer::Buffer(std::vector<std::byte, Container::AlignedAllocator<std::byte>>&& buffer) noexcept :
		buffer(std::move(buffer))
	{
	}

	std::span<std::byte> Buffer::Span() noexcept
	{
		return buffer;
	}

	std::span<const std::byte> Buffer::Span() const noexcept
	{
		return buffer;
	}

	std::size_t Buffer::Size() const noexcept
	{
		return buffer.size();
	}

	std::size_t Buffer::Alignment() const noexcept
	{
		return buffer.get_allocator().Alignment();
	}

	std::vector<std::byte, Container::AlignedAllocator<std::byte>>& Buffer::Data() noexcept
	{
		return buffer;
	}
}
