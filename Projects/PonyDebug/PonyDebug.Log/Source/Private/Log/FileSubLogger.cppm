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

export module PonyDebug.Log.Detail:FileSubLogger;

import <exception>;
import <filesystem>;
import <fstream>;
import <memory>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger that logs to a file.
	class FileSubLogger final : public SubLogger
	{
	public:
		/// @brief Creates a @p FileSubLogger.
		/// @param params File sub-logger parameters.
		[[nodiscard("Pure constructor")]]
		explicit FileSubLogger(const FileSubLoggerParams& params);
		FileSubLogger(const FileSubLogger&) = delete;
		FileSubLogger(FileSubLogger&&) = delete;

		virtual ~FileSubLogger() noexcept override;

		virtual void Log(const LogEntry& logEntry) const noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

	private:
		/// @brief Creates a log file stream.
		/// @param logPath Log file path.
		/// @return Log file stream.
		[[nodiscard("Pure function")]]
		static std::unique_ptr<std::ofstream> CreateLogFileStream(const std::filesystem::path& logPath);

		std::unique_ptr<std::ofstream> logFile; ///< Log file stream.
	};
}

namespace PonyDebug::Log
{
	FileSubLogger::FileSubLogger(const FileSubLoggerParams& params) :
		logFile(CreateLogFileStream(params.logPath))
	{
		if (!logFile->is_open()) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to open log file at path '{}'.", params.logPath.string()));
		}
	}

	FileSubLogger::~FileSubLogger() noexcept
	{
		if (logFile->is_open())
		{
			try
			{
				logFile->close();
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On closing log file.");
			}
		}

		PONY_CONSOLE(LogType::Info, "Destroy log file stream.");
		logFile.reset();
		PONY_CONSOLE(LogType::Info, "Log file stream destroyed.");
	}

	void FileSubLogger::Log(const LogEntry& logEntry) const noexcept
	{
		try
		{
			*logFile << logEntry;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On writing to log file.");
		}
	}

	std::unique_ptr<std::ofstream> FileSubLogger::CreateLogFileStream(const std::filesystem::path& logPath)
	{
		PONY_CONSOLE(LogType::Info, "Create log file stream at '{}'.", logPath.string());
		auto logFileStream = std::make_unique<std::ofstream>(logPath);
		PONY_CONSOLE(LogType::Info, "Log file stream created.");

		return logFileStream;
	}
}
