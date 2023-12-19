/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.LogFileLoggerEntry;

import <filesystem>;
import <fstream>;
import <iostream>;

import PonyEngine.Debug.ILoggerEntry;

namespace PonyEngine::Debug
{
	/// <summary>
	/// Logger entry that logs to a file.
	/// </summary>
	export class LogFileLoggerEntry final : public ILoggerEntry
	{
	public:
		/// <param name="logPath">Path to a log file.</param>
		LogFileLoggerEntry(const std::filesystem::path& logPath);
		LogFileLoggerEntry(const LogFileLoggerEntry&) = delete;
		LogFileLoggerEntry(LogFileLoggerEntry&& other);

		virtual ~LogFileLoggerEntry();

		virtual void Log(const std::string& log) noexcept override;

		virtual void LogWarning(const std::string& log) noexcept override;

		virtual void LogError(const std::string& log) noexcept override;

		virtual void LogException(const std::string& log, const std::exception& exception) noexcept override;

	private:
		inline void LogToFile(const std::string& log) noexcept;

		std::ofstream m_logFile;
	};

	LogFileLoggerEntry::LogFileLoggerEntry(const std::filesystem::path& logPath) :
		m_logFile(logPath)
	{
		if (!m_logFile.is_open())
		{
			std::cerr << logPath << " isn't open. Logs won't be written to file!" << std::endl;
		}
	}

	LogFileLoggerEntry::LogFileLoggerEntry(LogFileLoggerEntry&& other) :
		m_logFile(std::move(other.m_logFile))
	{
		if (!m_logFile.is_open())
		{
			std::cerr << "Moved non-opened logFile. Logs won't be written to file!" << std::endl;
		}
	}

	LogFileLoggerEntry::~LogFileLoggerEntry()
	{
		m_logFile.close();
	}

	void LogFileLoggerEntry::Log(const std::string& log) noexcept
	{
		LogToFile(log);
	}

	void LogFileLoggerEntry::LogWarning(const std::string& log) noexcept
	{
		LogToFile(log);
	}

	void LogFileLoggerEntry::LogError(const std::string& log) noexcept
	{
		LogToFile(log);
	}

	void LogFileLoggerEntry::LogException(const std::string& log, const std::exception& exception) noexcept
	{
		LogToFile(log);
	}

	void LogFileLoggerEntry::LogToFile(const std::string& log) noexcept
	{
		try
		{
			if (m_logFile.is_open())
			{
				m_logFile << log << std::endl;
			}
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << " on writing to a log file.";
		}
	}
}
