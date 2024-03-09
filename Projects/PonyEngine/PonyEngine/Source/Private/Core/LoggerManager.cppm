/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:LoggerManager;

import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Factories;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Debug.Log.Factories.Implementation;

namespace PonyEngine::Core
{
	export class LoggerManager final
	{
	public:
		LoggerManager(std::vector<Debug::Log::ISubLoggerFactory*> subLoggerFactories, IEngine& engine);
		~LoggerManager();

		Debug::Log::ILogger& GetLogger() const noexcept;

	private:
		Debug::Log::ILogger* const m_logger;
		std::vector<Debug::Log::ISubLogger*> m_subLoggers;
		std::vector<Debug::Log::ISubLoggerFactory*> m_subLoggerFactories;
	};

	LoggerManager::LoggerManager(std::vector<Debug::Log::ISubLoggerFactory*> subLoggerFactories, IEngine& engine) :
		m_logger{Debug::Log::CreateLogger(engine)}
	{
		for (Debug::Log::ISubLoggerFactory* const factory : subLoggerFactories)
		{
			Debug::Log::ISubLogger* subLogger = factory->Create(engine);
			m_subLoggers.push_back(subLogger);
			m_subLoggerFactories.push_back(factory);
			m_logger->AddSubLogger(subLogger);
		}
	}

	LoggerManager::~LoggerManager()
	{
		for (size_t i = 0, count = m_subLoggers.size(); i < count; ++i)
		{
			m_logger->RemoveSubLogger(m_subLoggers[i]);
			m_subLoggerFactories[i]->Destroy(m_subLoggers[i]);
		}

		DestroyLogger(m_logger);
	}

	Debug::Log::ILogger& LoggerManager::GetLogger() const noexcept
	{
		return *m_logger;
	}
}
