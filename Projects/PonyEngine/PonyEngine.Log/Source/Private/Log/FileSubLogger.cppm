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
import <iostream>;
import <stdexcept>;
import <string>;

import PonyEngine.Log;

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
		virtual const char* GetName() const noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Log::FileSubLogger"; ///< Class name.

	private:
		std::ofstream logFile; ///< log file stream.
	};
}

namespace PonyEngine::Log
{
	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		logFile(logPath)
	{
		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error("Log file isn't open.");
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
				PONY_CONSOLE(LogType::Exception, std::format("{} - On closing the log file.", e.what()).c_str());
			}
		}
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			logFile << logEntry << std::endl;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - On writing to the log file.", e.what()).c_str());
		}
	}

	const char* FileSubLogger::GetName() const noexcept
	{
		return StaticName;
	}
}
