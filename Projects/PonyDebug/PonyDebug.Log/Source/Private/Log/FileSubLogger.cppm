/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyDebug.Log.Implementation:FileSubLogger;

import <filesystem>;
import <fstream>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger that logs to a file.
	class FileSubLogger final : public ISubLogger
	{
	public:
		/// @brief Creates a @p FileSubLogger.
		/// @param logPath Path to a log file.
		[[nodiscard("Pure constructor")]]
		explicit FileSubLogger(const std::filesystem::path& logPath);
		FileSubLogger(const FileSubLogger&) = delete;
		FileSubLogger(FileSubLogger&&) = delete;

		~FileSubLogger() noexcept;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

		static constexpr auto StaticName = "PonyDebug::Log::FileSubLogger"; ///< Class name.

	private:
		std::ofstream logFile; ///< Log file stream.
	};
}

namespace PonyDebug::Log
{
	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		logFile(logPath)
	{
		PONY_CONSOLE(LogType::Debug, "Log file stream created at path '{}'.", PonyBase::Utility::ConvertToString(logPath.c_str()));

		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error(SafeFormat("Log file at path '{}' isn't open.", PonyBase::Utility::ConvertToString(logPath.c_str())));
		}
	}

	FileSubLogger::~FileSubLogger() noexcept
	{
		if (logFile.is_open())
		{
			try
			{
				logFile.close();
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On closing log file.");
			}
		}
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			logFile << logEntry;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On writing to log file.");
		}
	}

	const char* FileSubLogger::Name() const noexcept
	{
		return StaticName;
	}
}
