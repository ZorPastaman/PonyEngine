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

export module PonyEngine.Log.Implementation:FileSubLogger;

import <filesystem>;
import <fstream>;
import <stdexcept>;

import PonyEngine.Log;
import PonyEngine.StringUtility;

export namespace PonyEngine::Log
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

		static constexpr auto StaticName = "PonyEngine::Log::FileSubLogger"; ///< Class name.

	private:
		std::ofstream logFile; ///< Log file stream.
	};
}

namespace PonyEngine::Log
{
	/// @brief Creates a log file stream.
	/// @param logPath Log file path.
	/// @return Created log file stream.
	[[nodiscard("Pure function")]]
	std::ofstream CreateLogFileStream(const std::filesystem::path& logPath);

	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		logFile{CreateLogFileStream(logPath)}
	{
		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error("The log file isn't open.");
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
				PONY_CONSOLE_E(e, "On closing the log file.");
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
			PONY_CONSOLE_E(e, "On writing to the log file.");
		}
	}

	const char* FileSubLogger::Name() const noexcept
	{
		return StaticName;
	}

	std::ofstream CreateLogFileStream(const std::filesystem::path& logPath)
	{
		PONY_CONSOLE(LogType::Debug, "Create log file stream at the path '{}'.", Utility::ConvertToString(logPath.c_str()));
		auto logFile = std::ofstream(logPath);
		PONY_CONSOLE(LogType::Debug, "Log file stream created.");

		return logFile;
	}
}
