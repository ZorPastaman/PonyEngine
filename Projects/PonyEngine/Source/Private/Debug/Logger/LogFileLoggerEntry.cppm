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

import PonyEngine.Debug.ILoggerEntry;

namespace PonyEngine::Debug
{
	export class LogFileLoggerEntry final : public ILoggerEntry
	{
	public:
		LogFileLoggerEntry(const std::filesystem::path& logPath) noexcept;
		LogFileLoggerEntry(const LogFileLoggerEntry&) = delete;
		LogFileLoggerEntry(LogFileLoggerEntry&&) = delete;

		virtual ~LogFileLoggerEntry() noexcept;

		virtual void Log(const std::string& log) noexcept override;

		virtual void LogWarning(const std::string& log) noexcept override;

		virtual void LogError(const std::string& log) noexcept override;

		virtual void LogException(const std::string& log, const std::exception& exception) noexcept override;

	private:
		std::ofstream m_logFile;
	};

	LogFileLoggerEntry::LogFileLoggerEntry(const std::filesystem::path& logPath) noexcept :
		m_logFile(logPath)
	{
	}

	LogFileLoggerEntry::~LogFileLoggerEntry() noexcept
	{
		m_logFile.close();
	}

	void LogFileLoggerEntry::Log(const std::string& log) noexcept
	{
		m_logFile << log << std::endl;
	}

	void LogFileLoggerEntry::LogWarning(const std::string& log) noexcept
	{
		m_logFile << log << std::endl;
	}

	void LogFileLoggerEntry::LogError(const std::string& log) noexcept
	{
		m_logFile << log << std::endl;
	}

	void LogFileLoggerEntry::LogException(const std::string& log, const std::exception& exception) noexcept
	{
		m_logFile << log << std::endl;
	}
}
