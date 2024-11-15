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
import <stdexcept>;
import <string_view>;

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
		virtual std::string_view Name() const noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

		static constexpr std::string_view StaticName = "PonyDebug::Log::FileSubLogger"; ///< Class name.

	private:
		std::ofstream logFile; ///< Log file stream.
	};
}

namespace PonyDebug::Log
{
	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		logFile(logPath)
	{
		PONY_CONSOLE(LogType::Debug, "Log file stream created at path '{}'.", logPath.string());

		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::runtime_error(SafeFormat("Failed to open log file at path '{}'.", logPath.string()));
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

	std::string_view FileSubLogger::Name() const noexcept
	{
		return StaticName;
	}
}
