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

export module PonyEngine.File.Impl.Windows:File;

import std;

import PonyEngine.Application;
import PonyEngine.File.Impl;
import PonyEngine.Log;

import :FileUtility;
import :ServiceContext;
import :Worker;

export namespace PonyEngine::File
{
	/// @brief File.
	class File final : public IFile, public std::enable_shared_from_this<File>
	{
	public:
		/// @brief Opens a file.
		/// @param context Context.
		/// @param path File path
		/// @param params File parameters.
		[[nodiscard("Pure constructor")]]
		File(const ServiceContext& context, const std::filesystem::path& path, FileParams params);
		File(const File&) = delete;
		File(File&&) = delete;

		~File() noexcept;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual FileAccess Access() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual FileFlag Flags() const noexcept override;

		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params) override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params) override;

		File& operator =(const File&) = delete;
		File& operator =(File&&) = delete;

	private:
		/// @brief Opens a file.
		/// @param path File path.
		/// @param params File parameters.
		/// @return File handle.
		[[nodiscard("Pure function")]]
		HANDLE OpenFile(const std::filesystem::path& path, FileParams params) const;

		const ServiceContext* context; ///< Context.

		FileInfo fileInfo; ///< File info.
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

	File::File(const ServiceContext& context, const std::filesystem::path& path, const FileParams params) :
		context{&context},
		fileInfo(path, params.access, params.flags),
		fileHandle(OpenFile(path, params))
	{
		try
		{
			this->context->Worker().AssociateFile(fileHandle, *this);
		}
		catch (...)
		{
			if (!CloseHandle(fileHandle)) [[unlikely]]
			{
				PONY_LOG(this->context->LogService(), Log::LogType::Error, "Failed to close file. Error code: '0x{:X}'.", GetLastError());
			}
			throw;
		}

		this->context->IncrementFileCount();
	}

	File::~File() noexcept
	{
		if (!CloseHandle(fileHandle)) [[unlikely]]
		{
			PONY_LOG(this->context->LogService(), Log::LogType::Error, "Failed to close file. Error code: '0x{:X}'.", GetLastError());
		}

		this->context->DecrementFileCount();
	}

	const std::filesystem::path& File::Path() const noexcept
	{
		return fileInfo.Path();
	}

	FileAccess File::Access() const noexcept
	{
		return fileInfo.Access();
	}

	FileFlag File::Flags() const noexcept
	{
		return fileInfo.Flags();
	}

	std::shared_ptr<IReadRequest> File::Read(const ReadParams& params)
	{
		fileInfo.ValidateRead();
		return context->Worker().MakeRequest(fileHandle, shared_from_this(), params);
	}

	std::shared_ptr<IWriteRequest> File::Write(const WriteParams& params)
	{
		fileInfo.ValidateWrite();
		return context->Worker().MakeRequest(fileHandle, shared_from_this(), params);
	}

	HANDLE File::OpenFile(const std::filesystem::path& path, FileParams params) const
	{
		PONY_LOG(context->LogService(), Log::LogType::Info, "Creating file... Path: '{}'; Access: '{}'; OpenMode: '{}'; Flags: '{}'.",
			path.string(), params.access, params.openMode, params.flags);

		const HANDLE file = CreateFileSelector<std::filesystem::path::value_type>::Value(path.c_str(), ToDesiredAccess(params.access), FILE_SHARE_READ, nullptr,
			ToCreationDisposition(params.access, params.openMode), FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | ToFlags(params.flags), nullptr);
		if (file == INVALID_HANDLE_VALUE) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file: Error code = '0x{:X}'", GetLastError()));
		}

		PONY_LOG(context->LogService(), Log::LogType::Info, "Creating file done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(file));

		return file;
	}
}
