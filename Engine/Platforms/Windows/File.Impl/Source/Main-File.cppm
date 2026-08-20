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

import PonyEngine.File.Impl;
import PonyEngine.Log;

import :FileUtility;
import :ServiceContext;
import :Worker;

export namespace PonyEngine::File
{
	/// @brief File.
	class File final : public IFile
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
		virtual std::shared_ptr<IReadRequest> Read(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback) override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<IWriteRequest> Write(const WriteParams& params, std::move_only_function<void(const IWriteRequest&) noexcept> callback) override;

		File& operator =(const File&) = delete;
		File& operator =(File&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		HANDLE OpenFile(const std::filesystem::path& path, const FileParams params) const;
		void CloseFile() const noexcept;

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
			this->context->Worker().AssociateFile(fileHandle);
		}
		catch (...)
		{
			CloseFile();
			throw;
		}

		this->context->IncrementFileCount();
	}

	File::~File() noexcept
	{
		CloseFile();
		context->DecrementFileCount();
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

	std::shared_ptr<IReadRequest> File::Read(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback)
	{
		fileInfo.ValidateRead();
		return context->Worker().MakeRequest(params, std::move(callback), fileHandle);
	}

	std::shared_ptr<IWriteRequest> File::Write(const WriteParams& params, std::move_only_function<void(const IWriteRequest&) noexcept> callback)
	{
		fileInfo.ValidateWrite();
		return context->Worker().MakeRequest(params, std::move(callback), fileHandle);
	}

	HANDLE File::OpenFile(const std::filesystem::path& path, const FileParams params) const
	{
		PONY_LOG(context->LogService(), Log::LogType::Debug, "Opening file... Path: '{}'; Access: '{}'; OpenMode: '{}'; Flags: '{}'.",
			path.string(), params.access, params.openMode, params.flags);

		const HANDLE fileHandle = CreateFileSelector<std::filesystem::path::value_type>::Value(path.c_str(), ToDesiredAccess(params.access),
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, ToCreationDisposition(params.access, params.openMode), ToFlags(params.flags), nullptr);
		if (fileHandle == INVALID_HANDLE_VALUE) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create file: Error code = '0x{:X}'", GetLastError()));
		}

		PONY_LOG(context->LogService(), Log::LogType::Debug, "Opening file done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fileHandle));

		return fileHandle;
	}

	void File::CloseFile() const noexcept
	{
		PONY_LOG(context->LogService(), Log::LogType::Debug, "Closing file... Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fileHandle));

		if (!CloseHandle(fileHandle)) [[unlikely]]
		{
			PONY_LOG(context->LogService(), Log::LogType::Error, "Failed to close file. Error code: '0x{:X}'.", GetLastError());
		}

		PONY_LOG(context->LogService(), Log::LogType::Debug, "Closing file done.");
	}
}
