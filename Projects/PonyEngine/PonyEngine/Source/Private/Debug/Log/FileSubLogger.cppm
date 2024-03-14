/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Debug.Log.Implementation:FileSubLogger;

import <filesystem>;
import <fstream>;
import <iostream>;
import <stdexcept>;
import <string>;
import <utility>;

import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	/// @brief Sub-logger that logs to a file.
	export class FileSubLogger final : public ISubLogger
	{
	public:
		/// @brief Creates a @p FileSubLogger.
		/// @param logPath Path to a log file.
		[[nodiscard("Pure constructor")]]
		FileSubLogger(const std::filesystem::path& logPath);
		FileSubLogger(const FileSubLogger&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		FileSubLogger(FileSubLogger&& other);

		virtual ~FileSubLogger() noexcept;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetName() const noexcept override;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		inline FileSubLogger& operator =(FileSubLogger&& other) noexcept = default;

		static const char* const Name;

	private:
		std::ofstream m_logFile; /// @brief log file stream.
	};

	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		m_logFile(logPath)
	{
		if (!m_logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error("Log file isn't open.");
		}
	}

	FileSubLogger::FileSubLogger(FileSubLogger&& other) :
		m_logFile(std::move(other.m_logFile))
	{
		if (!m_logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error("Log file isn't open.");
		}
	}

	FileSubLogger::~FileSubLogger() noexcept
	{
		if (m_logFile.is_open())
		{
			try
			{
				m_logFile.close();
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE(LogType::Exception, std::format("{} - {}.", e.what(), "On closing a log file"));
			}
		}
	}

	inline const char* FileSubLogger::GetName() const noexcept
	{
		return Name;
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			m_logFile << logEntry << std::endl;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - {}.", e.what(), "On writing to a log file"));
		}
	}

	const char* const FileSubLogger::Name = "PonyEngine::Debug::Log::FileSubLogger";
}
