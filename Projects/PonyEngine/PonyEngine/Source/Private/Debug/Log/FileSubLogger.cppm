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

import :IEngineSubLogger;

namespace PonyEngine::Debug::Log
{
	/// @brief Sub-logger that logs to a file.
	export class FileSubLogger final : public IEngineSubLogger
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
		virtual const std::string& GetName() const noexcept override;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		/// @brief Move assignment.
		/// @param other Move source.
		/// @return @a This.
		inline FileSubLogger& operator =(FileSubLogger&& other) noexcept;

	private:
		std::ofstream m_logFile; /// @brief log file stream.
	};

	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		m_logFile(logPath)
	{
		if (!m_logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error("Log file isn't opened.");
		}
	}

	FileSubLogger::FileSubLogger(FileSubLogger&& other) :
		m_logFile(std::move(other.m_logFile))
	{
		if (!m_logFile.is_open()) [[unlikely]]
		{
			throw std::logic_error("Log file isn't opened.");
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
				PONY_CEXC(e, "On closing a log file.");
			}
		}
	}

	const std::string& FileSubLogger::GetName() const noexcept
	{
		static const std::string name = "PonyEngine::Debug::Log::FileSubLogger";
		return name;
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			m_logFile << logEntry << std::endl;
		}
		catch (const std::exception& e)
		{
			PONY_CEXC(e, "On writing to a log file.");
		}
	}

	inline FileSubLogger& FileSubLogger::operator =(FileSubLogger&& other) noexcept
	{
		m_logFile = std::move(other.m_logFile);

		return *this;
	}
}
