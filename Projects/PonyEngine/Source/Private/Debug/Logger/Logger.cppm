/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Logger;

import <vector>;
import <utility>;
import <chrono>;
import <format>;
import <cassert>;
import <algorithm>;
import <iostream>;

import PonyEngine.Debug.ILogger;
import PonyEngine.IEngineView;

namespace PonyEngine::Debug
{
	/// <summary>
	/// Default logger. It formats logs and sends them to its logger entries.
	/// </summary>
	export class Logger final : public ILogger
	{
	public:
		/// <param name="engine">Engine that the logger is owned by.</param>
		Logger(IEngineView* engine);
		Logger(const Logger&) = delete;
		Logger(Logger&& other);

		virtual ~Logger() = default;

		virtual void Log(const std::string& message) const noexcept override;

		virtual void LogWarning(const std::string& message) const noexcept override;

		virtual void LogError(const std::string& message) const noexcept override;

		virtual void LogException(const std::exception& exception) const noexcept override;

		virtual void AddLoggerEntry(ILoggerEntryView* loggerEntry) override;

		virtual void RemoveLoggerEntry(ILoggerEntryView* loggerEntry) override;

	private:
		std::string FormatLog(const std::string& logType, const std::string& message) const noexcept;

		std::vector<ILoggerEntryView*> m_loggerEntries;

		IEngineView* m_engine;
	};

	Logger::Logger(IEngineView* engine) :
		m_loggerEntries{},
		m_engine{engine}
	{
		assert((engine != nullptr));
	}

	Logger::Logger(Logger&& other) :
		m_loggerEntries(std::move(other.m_loggerEntries)),
		m_engine{other.m_engine}
	{
	}

	void Logger::Log(const std::string& message) const noexcept
	{
		const std::string formattedLog = FormatLog("Info", message);

		for (ILoggerEntryView* const entry : m_loggerEntries)
		{
			entry->Log(formattedLog);
		}
	}

	void Logger::LogWarning(const std::string& message) const noexcept
	{
		const std::string formattedLog = FormatLog("Warning", message);

		for (ILoggerEntryView* const entry : m_loggerEntries)
		{
			entry->LogWarning(formattedLog);
		}
	}

	void Logger::LogError(const std::string& message) const noexcept
	{
		const std::string formattedLog = FormatLog("Error", message);

		for (ILoggerEntryView* const entry : m_loggerEntries)
		{
			entry->LogError(formattedLog);
		}
	}

	void Logger::LogException(const std::exception& exception) const noexcept
	{
		const std::string formattedLog = FormatLog("Exception", exception.what());

		for (ILoggerEntryView* const entry : m_loggerEntries)
		{
			entry->LogException(formattedLog, exception);
		}
	}

	void Logger::AddLoggerEntry(ILoggerEntryView* const loggerEntry)
	{
		assert((loggerEntry != nullptr));
		m_loggerEntries.push_back(loggerEntry);
	}

	void Logger::RemoveLoggerEntry(ILoggerEntryView* const loggerEntry)
	{
		const std::vector<ILoggerEntryView*>::iterator position = std::find(m_loggerEntries.begin(), m_loggerEntries.end(), loggerEntry);

		if (position != m_loggerEntries.end())
		{
			m_loggerEntries.erase(position);
		}
	}

	// TODO: category, source location, stacktrace (with c++ 23)

	std::string Logger::FormatLog(const std::string& logType, const std::string& message) const noexcept
	{
		try
		{
			const std::chrono::time_point now = std::chrono::system_clock::now();
			return std::format("[{}] [{:%F %R:%OS UTC} ({})] {}.", logType, now, m_engine->GetFrameCount(), message);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << " on formatting log." << std::endl;
			return std::string();
		}
	}
}
