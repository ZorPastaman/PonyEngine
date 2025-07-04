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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.Main:Logger;

import std;

import PonyEngine.Application;
import PonyEngine.Core;
import PonyEngine.Log.Extension;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class Logger final : public Core::ILogger, private ILogger
	{
	public:
		/// @brief Creates a logger.
		/// @param application Application context.
		/// @param subLoggerFactories Sub-logger factories. The order of the factories may be changed.
		[[nodiscard("Pure constuctor")]]
		Logger(Application::IApplicationContext& application, std::span<ISubLoggerFactory*> subLoggerFactories);
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		~Logger() noexcept;

		virtual void Log(LogType logType, const LogInput& logInput) const noexcept override;
		virtual void Log(const std::exception& exception, const LogInput& logInput) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& PublicLogger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& PublicLogger() const noexcept override;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	private:
		/// @brief Logger context.
		class LoggerContext final : public ILoggerContext
		{
		public:
			/// @brief Creates a logger context.
			/// @param logger Logger.
			[[nodiscard("Pure constructor")]]
			explicit LoggerContext(Logger& logger) noexcept;
			LoggerContext(const LoggerContext&) = delete;
			LoggerContext(LoggerContext&&) = delete;

			~LoggerContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Application::IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Application::IApplicationContext& Application() const noexcept override;

			LoggerContext& operator =(const LoggerContext&) = delete;
			LoggerContext& operator =(LoggerContext&&) = delete;

		private:
			Logger* logger; ///< Logger.
		};

		/// @brief Initializes the logger.
		/// @param subLoggerFactories Sub-logger factories.
		void Initialize(std::span<ISubLoggerFactory*> subLoggerFactories);
		/// @brief Finalizes the logger.
		void Finalize() noexcept;

		/// @brief Begins the sub-loggers.
		/// @param count How many sub-loggers are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the sub-loggers.
		/// @param count How many sub-loggers to end.
		void End(std::size_t count) noexcept;

		/// @brief Logs the entry.
		/// @param logEntry Log entry to log.
		void Log(const LogEntry& logEntry) const noexcept;

		Application::IApplicationContext* application; ///< Application context.

		LoggerContext loggerContext; ///< Logger context.

		std::vector<std::shared_ptr<ISubLogger>> subLoggers; ///< Sub-loggers.
	};
}

namespace PonyEngine::Log
{
	Logger::Logger(Application::IApplicationContext& application, const std::span<ISubLoggerFactory*> subLoggerFactories) :
		application{&application},
		loggerContext(*this)
	{
		PONY_LOG(this->application->Logger(), LogType::Debug, "Sorting sub-logger factories.");
		std::ranges::sort(subLoggerFactories, [](const ISubLoggerFactory* const lhs, const ISubLoggerFactory* const rhs) noexcept { return lhs->Order() < rhs->Order(); });
		if constexpr (IsInMask(LogType::Warning, PONY_LOG_MASK))
		{
			for (std::size_t i = 0z; i < subLoggers.size(); ++i)
			{
				for (std::size_t j = i + 1z; j < subLoggers.size() && subLoggerFactories[i]->Order() == subLoggerFactories[j]->Order(); ++j)
				{
					PONY_LOG(this->application->Logger(), LogType::Warning, "'{}' and '{}' sub-loggers have the same order. It may cause unpredictable results.", 
						typeid(*subLoggerFactories[i]).name(), typeid(*subLoggerFactories[j]).name());
				}
			}
		}

		std::size_t subLoggerCount = 0;
		try
		{
			Initialize(subLoggerFactories);
			Begin(subLoggerCount);
		}
		catch (...)
		{
			End(subLoggerCount);
			Finalize();

			throw;
		}
	}

	Logger::~Logger() noexcept
	{
		End(subLoggers.size());
		Finalize();
	}

	void Logger::Log(const LogType logType, const LogInput& logInput) const noexcept
	{
		const auto logEntry = LogEntry(logInput.message, logInput.stacktrace, nullptr, std::chrono::system_clock::now(), logInput.frameCount, logType);
		Log(logEntry);
	}

	void Logger::Log(const std::exception& exception, const LogInput& logInput) const noexcept
	{
		const auto logEntry = LogEntry(logInput.message, logInput.stacktrace, &exception, std::chrono::system_clock::now(), logInput.frameCount, LogType::Exception);
		Log(logEntry);
	}

	Log::ILogger& Logger::PublicLogger() noexcept
	{
		return *this;
	}

	const Log::ILogger& Logger::PublicLogger() const noexcept
	{
		return *this;
	}

	Logger::LoggerContext::LoggerContext(Logger& logger) noexcept :
		logger{&logger}
	{
	}

	Application::IApplicationContext& Logger::LoggerContext::Application() noexcept
	{
		return *logger->application;
	}

	const Application::IApplicationContext& Logger::LoggerContext::Application() const noexcept
	{
		return *logger->application;
	}

	void Logger::Initialize(const std::span<ISubLoggerFactory*> subLoggerFactories)
	{
		PONY_LOG(this->application->Logger(), LogType::Info, "Creating sub-loggers...");
		subLoggers.reserve(subLoggerFactories.size());
		for (ISubLoggerFactory* const factory : subLoggerFactories)
		{
			try
			{
				PONY_LOG(this->application->Logger(), LogType::Info, "Creating sub-logger... Factory: '{}'.", typeid(*factory).name());
				std::shared_ptr<ISubLogger> subLogger = factory->CreateSubLogger(loggerContext);
				assert(subLogger && "The created sub-logger is nullptr!");
				PONY_LOG(this->application->Logger(), LogType::Info, "Creating sub-logger done. Sub-logger: '{}'.", typeid(*subLogger).name());
				subLoggers.push_back(std::move(subLogger));
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(this->application->Logger(), e, "On creating sub-logger. Factory: '{}'.", typeid(*factory).name());

				throw;
			}
			catch (...)
			{
				PONY_LOG(this->application->Logger(), LogType::Exception, "Unknown exception on creating sub-logger. Factory: '{}'.", typeid(*factory).name());

				throw;
			}
		}
		PONY_LOG(this->application->Logger(), LogType::Info, "Creating sub-loggers done.");
	}

	void Logger::Finalize() noexcept
	{
		PONY_LOG(this->application->Logger(), LogType::Info, "Releasing sub-loggers...");
		for (std::size_t i = subLoggers.size(); i-- > 0z; )
		{
			std::shared_ptr<ISubLogger>& subLogger = subLoggers[i];
			PONY_LOG(this->application->Logger(), LogType::Info, "Releasing '{}' sub-logger.", typeid(*subLogger).name());
			subLogger.reset();
		}
		PONY_LOG(this->application->Logger(), LogType::Info, "Releasing sub-loggers done.");
	}

	void Logger::Begin(std::size_t& count)
	{
		PONY_LOG(application->Logger(), LogType::Info, "Beginning sub-loggers...");
		for (const std::shared_ptr<ISubLogger>& subLogger : subLoggers)
		{
			try
			{
				PONY_LOG(application->Logger(), LogType::Info, "Beginning '{}' sub-logger.", typeid(*subLogger).name());
				subLogger->Begin();
				++count;
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On beginning '{}' sub-logger.", typeid(*subLogger).name());

				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), LogType::Exception, "Unknown exception on beginning '{}' sub-logger.", typeid(*subLogger).name());

				throw;
			}
		}
		PONY_LOG(application->Logger(), LogType::Info, "Beginning sub-loggers done.");
	}

	void Logger::End(const std::size_t count) noexcept
	{
		PONY_LOG(application->Logger(), LogType::Info, "Ending sub-loggers...");
		for (std::size_t i = count; i-- > 0z; )
		{
			const std::shared_ptr<ISubLogger>& subLogger = subLoggers[i];
			try
			{
				PONY_LOG(application->Logger(), LogType::Info, "Ending '{}' sub-logger.", typeid(*subLogger).name());
				subLogger->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On ending '{}' sub-logger.", typeid(*subLogger).name());
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), LogType::Exception, "Unknown exception on ending '{}' sub-logger.", typeid(*subLogger).name());
			}
		}
		PONY_LOG(application->Logger(), LogType::Info, "Ending sub-loggers done.");
	}

	void Logger::Log(const LogEntry& logEntry) const noexcept
	{
		for (const std::shared_ptr<ISubLogger>& subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}
}
