/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.File.Impl.Windows:FileHandle;

import std;

import PonyEngine.Log;

import :FileUtility;
import :ServiceContext;

export namespace PonyEngine::File
{
	/// @brief File handle.
	class FileHandle final
	{
	public:
		/// @brief Creates a file handle.
		/// @param context Service context.
		/// @param path File path.
		/// @param params File parameters.
		[[nodiscard("Pure constructor")]]
		FileHandle(const ServiceContext& context, const std::filesystem::path& path, FileParams params);
		FileHandle(const FileHandle&) = delete;
		FileHandle(FileHandle&&) = delete;

		~FileHandle() noexcept;

		[[nodiscard("Pure function")]]
		HANDLE Handle() const noexcept;

		FileHandle& operator =(const FileHandle&) = delete;
		FileHandle& operator =(FileHandle&&) = delete;

	private:
		const ServiceContext* context; ///< Context.

		HANDLE fileHandle; ///< File handle.
	};
}

namespace PonyEngine::File
{
	/// @brief Create file function selector.
	/// @tparam CharT Path value type. Must be @p char or @p wchar_t.
	template<typename CharT>
	struct CreateFileSelector;
	template<>
	struct CreateFileSelector<char>
	{
		static constexpr auto Value = &CreateFileA; ///< @p CreateFileA.
	};
	template<>
	struct CreateFileSelector<wchar_t>
	{
		static constexpr auto Value = &CreateFileW; ///< @p CreateFileW.
	};

	FileHandle::FileHandle(const ServiceContext& context, const std::filesystem::path& path, const FileParams params) :
		context{&context}
	{
		PONY_LOG(this->context->LogService(), Log::LogType::Debug, "Opening file... Path: '{}'; Access: '{}'; OpenMode: '{}'; Flags: '{}'.",
			path.string(), params.access, params.openMode, params.flags);

		fileHandle = CreateFileSelector<std::filesystem::path::value_type>::Value(path.c_str(), ToDesiredAccess(params.access), 
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, ToCreationDisposition(params.access, params.openMode), ToFlags(params.flags), nullptr);
		if (fileHandle == INVALID_HANDLE_VALUE) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file: Error code = '0x{:X}'", GetLastError()));
		}

		PONY_LOG(this->context->LogService(), Log::LogType::Debug, "Opening file done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fileHandle));

		this->context->IncrementFileCount();
	}

	FileHandle::~FileHandle() noexcept
	{
		PONY_LOG(context->LogService(), Log::LogType::Debug, "Closing file... Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fileHandle));

		if (!CloseHandle(fileHandle)) [[unlikely]]
		{
			PONY_LOG(context->LogService(), Log::LogType::Error, "Failed to close file. Error code: '0x{:X}'.", GetLastError());
		}

		PONY_LOG(context->LogService(), Log::LogType::Debug, "Closing file done.");

		context->DecrementFileCount();
	}

	HANDLE FileHandle::Handle() const noexcept
	{
		return fileHandle;
	}
}
