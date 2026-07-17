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

export module PonyEngine.Application.Impl:LoggerManager;

import std;

import PonyEngine.Log;

import :EmptyLogger;
import :ThreadManager;

export namespace PonyEngine::Application
{
	/// @brief Logger manager.
	class LoggerManager final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit LoggerManager(const ThreadManager& threadManager) noexcept;
		LoggerManager(const LoggerManager&) = delete;
		LoggerManager(LoggerManager&&) = delete;

		~LoggerManager() noexcept;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		Log::ILogger& Logger() noexcept;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		const Log::ILogger& Logger() const noexcept;

		/// @brief Checks if the engine has a set logger.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasLogger() const noexcept;
		/// @brief Sets the logger.
		/// @param logger Logger to set.
		void SetLogger(Log::ILogger& logger);
		/// @brief Unsets the logger.
		/// @param logger Logger to unset.
		void UnsetLogger(const Log::ILogger& logger);

		LoggerManager& operator =(const LoggerManager&) = delete;
		LoggerManager& operator =(LoggerManager&&) = delete;

	private:
		const ThreadManager* threadManager; ///< Thread manager.

		EmptyLogger emptyLogger; ///< Empty logger.
		Log::ILogger* logger; ///< Current logger.
	};
}

namespace PonyEngine::Application
{
	LoggerManager::LoggerManager(const ThreadManager& threadManager) noexcept :
		threadManager{&threadManager},
		logger{&emptyLogger}
	{
	}

	LoggerManager::~LoggerManager() noexcept
	{
		assert(!HasLogger() && "The custom logger wasn't unset.");
	}

	Log::ILogger& LoggerManager::Logger() noexcept
	{
		return *logger;
	}

	const Log::ILogger& LoggerManager::Logger() const noexcept
	{
		return *logger;
	}

	bool LoggerManager::HasLogger() const noexcept
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return logger != &emptyLogger;
	}

	void LoggerManager::SetLogger(Log::ILogger& logger)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (HasLogger()) [[unlikely]]
		{
			throw std::logic_error("Logger was already added");
		}
#endif

		this->logger = &logger;
	}

	void LoggerManager::UnsetLogger(const Log::ILogger& logger)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != threadManager->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (this->logger != &logger) [[unlikely]]
		{
			throw std::logic_error("Another logger is set");
		}
#endif

		this->logger = &emptyLogger;
	}
}
