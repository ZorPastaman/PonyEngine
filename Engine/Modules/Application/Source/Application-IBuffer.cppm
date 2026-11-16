/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Application:IBuffer;

import std;

export namespace PonyEngine::Application
{
	/// @brief Buffer.
	class IBuffer
	{
		PONY_INTERFACE_BODY(IBuffer)

		/// @brief Gets the span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		virtual std::span<std::byte> Span() noexcept = 0;
		/// @brief Gets the span.
		/// @return Span.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Span() const noexcept = 0;

		/// @brief Gets the buffer size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
		/// @brief Gets the buffer alignment.
		/// @return Alignment.
		[[nodiscard("Pure function")]]
		virtual std::size_t Alignment() const noexcept = 0;

		/// @brief Ensures the buffer size.
		/// @param size Required size.
		/// @return @a True if the buffer was changed; @a false otherwise.
		/// @note The previously returned span may become invalid.
		virtual bool EnsureSize(std::size_t size) = 0;
	};
}
