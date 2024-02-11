/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.FileSubLogger;

import <filesystem>;
import <fstream>;
import <iostream>;
import <utility>;

import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogEntry;

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

		virtual ~FileSubLogger();

		virtual void Log(const LogEntry& logEntry) noexcept override;

	private:
		std::ofstream m_logFile; /// @brief log file stream.
	};

	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		m_logFile(logPath)
	{
		if (!m_logFile.is_open()) [[unlikely]]
		{
			std::cerr << logPath << " isn't open. Logs won't be written to file!" << std::endl;
		}
	}

	FileSubLogger::FileSubLogger(FileSubLogger&& other) :
		m_logFile(std::move(other.m_logFile))
	{
		if (!m_logFile.is_open()) [[unlikely]]
		{
			std::cerr << "Moved non-opened logFile. Logs won't be written to file!" << std::endl;
		}
	}

	FileSubLogger::~FileSubLogger()
	{
		if (m_logFile.is_open()) [[likely]]
		{
			m_logFile.close();
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
}
