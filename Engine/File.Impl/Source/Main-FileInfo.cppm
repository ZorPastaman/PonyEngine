/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File.Impl:FileInfo;

import std;

import PonyEngine.File;

export namespace PonyEngine::File
{
	/// @brief File info.
	class FileInfo final
	{
	public:
		/// @brief Creates a file info.
		/// @param path File path.
		/// @param access File access.
		/// @param flags File flags.
		[[nodiscard("Pure constructor")]]
		FileInfo(const std::filesystem::path& path, FileAccess access, FileFlag flags);
		[[nodiscard("Pure constructor")]]
		FileInfo(const FileInfo& other) = default;
		[[nodiscard("Pure constructor")]]
		FileInfo(FileInfo&& other) noexcept = default;

		~FileInfo() noexcept = default;

		/// @brief Gets the file path.
		/// @return File path.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& Path() const noexcept;
		/// @brief Gets the file access.
		/// @return File access.
		[[nodiscard("Pure function")]]
		FileAccess Access() const noexcept;
		/// @brief Gets the file flags.
		/// @return File flags.
		[[nodiscard("Pure function")]]
		FileFlag Flags() const noexcept;

		/// @brief Validates if the read request is available.
		void ValidateRead() const;
		/// @brief Validates if the write request is available.
		void ValidateWrite() const;
		/// @brief Validates the file has the access.
		/// @param access Access to check.
		void ValidateAccess(FileAccess access) const;

		FileInfo& operator =(const FileInfo& other) = default;
		FileInfo& operator =(FileInfo&& other) noexcept = default;

	private:
		std::filesystem::path path; ///< File path.
		FileAccess access; ///< File access.
		FileFlag flags; ///< File flags.
	};
}

namespace PonyEngine::File
{
	FileInfo::FileInfo(const std::filesystem::path& path, const FileAccess access, const FileFlag flags) :
		path(path),
		access{access},
		flags{flags}
	{
	}

	const std::filesystem::path& FileInfo::Path() const noexcept
	{
		return path;
	}

	FileAccess FileInfo::Access() const noexcept
	{
		return access;
	}

	FileFlag FileInfo::Flags() const noexcept
	{
		return flags;
	}

	void FileInfo::ValidateRead() const
	{
		ValidateAccess(FileAccess::Read);
	}

	void FileInfo::ValidateWrite() const
	{
		ValidateAccess(FileAccess::Write);
	}

	void FileInfo::ValidateAccess(const FileAccess access) const
	{
#ifndef NDEBUG
		if (None(access, this->access)) [[unlikely]]
		{
			throw std::logic_error("Invalid access");
		}
#endif
	}
}
