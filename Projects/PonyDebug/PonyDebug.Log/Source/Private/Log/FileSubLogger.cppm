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
		std::unique_ptr<std::ofstream> logFile; ///< Log file stream.
	};
}

namespace PonyDebug::Log
{
	FileSubLogger::FileSubLogger(const FileSubLoggerParams& params)
	{
		PONY_CONSOLE(LogType::Info, "Create log file stream at '{}'.", params.logPath.string());
		logFile = std::make_unique<std::ofstream>(params.logPath);
		PONY_CONSOLE(LogType::Info, "Log file stream created.");

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
}
