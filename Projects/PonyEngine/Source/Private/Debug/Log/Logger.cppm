/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <chrono>

export module PonyEngine.Debug.Log.Logger;

import <cassert>;
import <exception>;
import <iostream>;
import <vector>;

import PonyEngine.IEngineView;
import PonyEngine.Debug.Log.ILogger;
import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogEntry;
import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
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

		virtual void Log(LogType logType, const std::string& message) noexcept override;

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

	private:
		std::vector<ISubLogger*> m_subLoggers;

		IEngineView* m_engine;
	};

	Logger::Logger(IEngineView* engine) :
		m_subLoggers{},
		m_engine{engine}
	{
		assert((engine != nullptr));
	}

	Logger::Logger(Logger&& other) :
		m_subLoggers(std::move(other.m_subLoggers)),
		m_engine{other.m_engine}
	{
	}

	void Logger::Log(LogType logType, const std::string& message) noexcept
	{
		try
		{
			LogEntry logEntry(message, std::chrono::system_clock::now(), m_engine->GetFrameCount(), logType);

			for (ISubLogger* subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << " on writing to log.";
		}
	}

	void Logger::AddSubLogger(ISubLogger* const subLogger)
	{
		assert((subLogger != nullptr));
		m_subLoggers.push_back(subLogger);
	}

	void Logger::RemoveSubLogger(ISubLogger* subLogger)
	{
		const std::vector<ISubLogger*>::iterator position = std::find(m_subLoggers.begin(), m_subLoggers.end(), subLogger);

		if (position != m_subLoggers.end())
		{
			m_subLoggers.erase(position);
		}
	}
}
