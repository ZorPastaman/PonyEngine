/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File:FileParams;

import :FileAccess;
import :FileFlag;
import :FileOpenMode;

export namespace PonyEngine::File
{
	/// @brief File parameters.
	struct FileParams final
	{
		FileAccess access = FileAccess::None; ///< File access mode.
		FileOpenMode openMode = FileOpenMode::None; ///< File open mode.
		FileFlag flags = FileFlag::None; ///< File flags.

		/// @brief Gets default read parameters {.access = Read, .openMode = None, .flags = None}.
		/// @return Default read parameters.
		[[nodiscard("Pure function")]]
		static constexpr const FileParams& Read() noexcept;
		/// @brief Gets default write parameters {.access = Write, .openMode = None, .flags = None}.
		/// @return Default write parameters.
		[[nodiscard("Pure function")]]
		static constexpr const FileParams& Write() noexcept;
		/// @brief Gets default write parameters with truncating {.access = Write, .openMode = Truncate, .flags = None}.
		/// @return Default write parameters with truncating.
		[[nodiscard("Pure function")]]
		static constexpr const FileParams& WriteTruncate() noexcept;
	};
}

namespace PonyEngine::File
{
	constexpr const FileParams& FileParams::Read() noexcept
	{
		static constexpr auto ReadParams = FileParams{.access = FileAccess::Read};
		return ReadParams;
	}

	constexpr const FileParams& FileParams::Write() noexcept
	{
		static constexpr auto WriteParams = FileParams{.access = FileAccess::Write};
		return WriteParams;
	}

	constexpr const FileParams& FileParams::WriteTruncate() noexcept
	{
		static constexpr auto WriteParams = FileParams{.access = FileAccess::Write, .openMode = FileOpenMode::Truncate};
		return WriteParams;
	}
}
