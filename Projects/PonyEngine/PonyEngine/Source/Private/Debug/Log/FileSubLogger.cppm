/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation:FileSubLogger;

import <filesystem>;
import <fstream>;
import <iostream>;
import <stdexcept>;
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
				std::cerr << e.what() << " on closing a log file.";
			}
		}
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			m_logFile << logEntry << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << " on writing to a log file.";
		}
	}

	inline FileSubLogger& FileSubLogger::operator =(FileSubLogger&& other) noexcept
	{
		m_logFile = std::move(other.m_logFile);

		return *this;
	}
}
