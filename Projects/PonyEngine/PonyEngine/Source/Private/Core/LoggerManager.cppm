/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include <Debug/Log/LogMacro.h>

export module PonyEngine.Core.Implementation:LoggerManager;

import <exception>;
import <format>;
import <iostream>;
import <utility>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Factories;
import PonyEngine.Debug.Log.Implementation;

namespace PonyEngine::Core
{
	/// @brief Holder of a logger and predefined sub-loggers.
	export class LoggerManager final
	{
	public:
		/// @brief Creates a logger manager.
		/// @param subLoggerFactories Sub-logger factories.
		/// @param engine Engine that owns the manager.
		[[nodiscard("Pure constructor")]]
		LoggerManager(const std::vector<Debug::Log::ISubLoggerFactory*>& subLoggerFactories, IEngine& engine);
		LoggerManager(const LoggerManager&) = delete;
		[[nodiscard("Pure constructor")]]
		inline LoggerManager(LoggerManager&&) noexcept = default;

		~LoggerManager() noexcept;

		/// @brief Gets a logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		inline Debug::Log::ILogger& GetLogger() const noexcept;

		LoggerManager& operator =(const LoggerManager&) = delete;
		inline LoggerManager& operator =(LoggerManager&& other) noexcept = default;

	private:
		std::vector<std::pair<Debug::Log::ISubLogger*, Debug::Log::ISubLoggerFactory*>> m_subLoggers; /// @brief Pairs of a sub-logger and a sub-logger factory that was used to create the sub-logger.
		Debug::Log::ILogger* const m_logger; /// @brief Logger.
	};

	LoggerManager::LoggerManager(const std::vector<Debug::Log::ISubLoggerFactory*>& subLoggerFactories, IEngine& engine) :
		m_logger{Debug::Log::CreateLogger(engine)}
	{
		PONY_CONSOLE(Debug::Log::LogType::Info, "Logger created.");
		PONY_CONSOLE(Debug::Log::LogType::Info, "Create sub-loggers.");

		for (Debug::Log::ISubLoggerFactory* const factory : subLoggerFactories)
		{
			assert((factory != nullptr));
			PONY_CONSOLE(Debug::Log::LogType::Info, std::format("Create '{}'.", factory->GetSubLoggerName()).c_str());
			Debug::Log::ISubLogger* const subLogger = factory->Create(engine);
			assert((subLogger != nullptr));
			m_subLoggers.push_back(std::pair(subLogger, factory));
			m_logger->AddSubLogger(subLogger);
			PONY_CONSOLE(Debug::Log::LogType::Info, std::format("'{}' created.", subLogger->GetName()).c_str());
		}

		PONY_CONSOLE(Debug::Log::LogType::Info, "Sub-loggers created.");
	}

	LoggerManager::~LoggerManager() noexcept
	{
		PONY_CONSOLE(Debug::Log::LogType::Info, "Destroy sub-loggers.");

		for (std::vector<std::pair<Debug::Log::ISubLogger*, Debug::Log::ISubLoggerFactory*>>::const_reverse_iterator it = m_subLoggers.crbegin(); it != m_subLoggers.crend(); ++it)
		{
			Debug::Log::ISubLogger* const subLogger = it->first;
			Debug::Log::ISubLoggerFactory* const factory = it->second;
			PONY_CONSOLE(Debug::Log::LogType::Info, std::format("Destroy '{}'.", subLogger->GetName()).c_str());

			try
			{
				m_logger->RemoveSubLogger(subLogger);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE(Debug::Log::LogType::Exception, std::format("{} - {}.", e.what(), "On removing a sub-logger").c_str());
			}

			factory->Destroy(subLogger);
			PONY_CONSOLE(Debug::Log::LogType::Info, std::format("'{}' destroyed", factory->GetSubLoggerName()));
		}

		PONY_CONSOLE(Debug::Log::LogType::Info, "Sub-loggers destroyed.");

		PONY_CONSOLE(Debug::Log::LogType::Info, "Destroy a logger.");
		DestroyLogger(m_logger);
		PONY_CONSOLE(Debug::Log::LogType::Info, "Logger destroyed.");
	}

	inline Debug::Log::ILogger& LoggerManager::GetLogger() const noexcept
	{
		return *m_logger;
	}
}
