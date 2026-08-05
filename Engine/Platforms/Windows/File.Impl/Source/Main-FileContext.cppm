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

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.File.Impl.Windows:FileContext;

import std;

export namespace PonyEngine::File
{
	/// @brief File context.
	class FileContext final
	{
	public:
		/// @brief Creates a file context.
		/// @param fileHandle File handle.
		[[nodiscard("Pure constructor")]]
		explicit FileContext(HANDLE fileHandle) noexcept;
		FileContext(const FileContext&) = delete;
		FileContext(FileContext&&) = delete;

		~FileContext() noexcept = default;

		[[nodiscard("Pure function")]]
		HANDLE FileHandle() const noexcept;

		/// @brief Increments the request count.
		void IncrementRequestCount() const noexcept;
		/// @brief Decrements the request count.
		void DecrementRequestCount() const noexcept;

		/// @brief Validates that all the counts are zeroes.
		void EnsureZeroCounts() const noexcept;

		FileContext& operator =(const FileContext&) = delete;
		FileContext& operator =(FileContext&&) = delete;

	private:
		HANDLE fileHandle; ///< File handle.

#ifndef NDEBUG
		mutable std::atomic_size_t requestCount; ///< File count.
#endif
	};
}

namespace PonyEngine::File
{
	FileContext::FileContext(const HANDLE fileHandle) noexcept :
#ifndef NDEBUG
		requestCount(0uz),
#endif
		fileHandle{fileHandle}
	{
	}

	HANDLE FileContext::FileHandle() const noexcept
	{
		return fileHandle;
	}

	void FileContext::IncrementRequestCount() const noexcept
	{
#ifndef NDEBUG
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
#endif
	}

	void FileContext::DecrementRequestCount() const noexcept
	{
#ifndef NDEBUG
		const std::size_t prev = requestCount.fetch_sub(1uz, std::memory_order::relaxed);
		assert(prev != 0uz && "Invalid request count decrement.");
#endif
	}

	void FileContext::EnsureZeroCounts() const noexcept
	{
#ifndef NDEBUG
		assert(requestCount.load(std::memory_order::relaxed) == 0uz && "File request count is not zero.");
#endif
	}
}
