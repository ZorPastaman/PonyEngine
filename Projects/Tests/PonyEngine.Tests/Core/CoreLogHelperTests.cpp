/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#ifndef PONY_LOG_VERBOSE
#define PONY_LOG_VERBOSE
#endif
#ifndef PONY_LOG_DEBUG
#define PONY_LOG_DEBUG
#endif
#ifndef PONY_LOG_INFO
#define PONY_LOG_INFO
#endif
#ifndef PONY_LOG_WARNING
#define PONY_LOG_WARNING
#endif
#ifndef PONY_LOG_ERROR
#define PONY_LOG_ERROR
#endif
#ifndef PONY_LOG_EXCEPTION
#define PONY_LOG_EXCEPTION
#endif
#ifndef PONY_CONSOLE_LOG
#define PONY_CONSOLE_LOG
#endif
#include "PonyEngine/Log/EngineLog.h"

import <cstddef>;
import <cstdint>;
import <format>;
import <exception>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(LogHelperTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			std::string lastMessage;
			const std::exception* lastException;
			std::size_t lastFrameCount;
			PonyEngine::Log::LogType lastLogType;

			virtual void Log(const PonyEngine::Log::LogType logType, const PonyEngine::Log::LogInput& logInput) noexcept override
			{
				lastMessage = logInput.message ? logInput.message : "";
				lastFrameCount = logInput.frameCount;
				lastLogType = logType;
			}

			virtual void LogException(const std::exception& exception, const PonyEngine::Log::LogInput& logInput) noexcept override
			{
				lastMessage = logInput.message ? logInput.message : "";
				lastFrameCount = logInput.frameCount;
				lastException = &exception;
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger*) override
			{
			}

			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger*) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class TimeManager final : public PonyEngine::Core::ITimeManager
		{
		public:
			std::size_t frameCount;

			[[nodiscard("Pure function")]]
			virtual std::size_t FrameCount() const noexcept override
			{
				return frameCount;
			}

			[[nodiscard("Pure function")]]
			virtual float TargetFrameTime() const noexcept override
			{
				return 0.f;
			}

			virtual void TargetFrameTime(float) noexcept override
			{
			}
		};

		class SystemManager final : public PonyEngine::Core::ISystemManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info&) const noexcept override
			{
				return nullptr;
			}
		};

		class Engine final : public PonyEngine::Core::IEngine
		{
		public:
			EmptyLogger* logger;
			LogHelperTests::TimeManager* timeManager;

			LogHelperTests::SystemManager* systemManager;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& Logger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ITimeManager& TimeManager() const noexcept override
			{
				return *timeManager;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystemManager& SystemManager() const noexcept override
			{
				return *systemManager;
			}

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override
			{
				return false;
			}

			[[nodiscard("Pure function")]]
			virtual int ExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		TEST_METHOD(LogToLoggerTest)
		{
			auto logger = EmptyLogger();
			auto timeManager = TimeManager();
			auto engine = Engine();
			engine.logger = &logger;
			engine.timeManager = &timeManager;

			const auto message = "Message";
			timeManager.frameCount = 14;
			PonyEngine::Core::LogToLogger(engine, PonyEngine::Log::LogType::Debug, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			logger.lastMessage = "";
			logger.lastFrameCount = 22;
			logger.lastLogType = PonyEngine::Log::LogType::Info;
			PONY_LOG(&engine, PonyEngine::Log::LogType::Debug, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			logger.lastMessage = "";
			logger.lastFrameCount = 22;
			logger.lastLogType = PonyEngine::Log::LogType::Info;
			PonyEngine::Core::LogToLogger(engine, PonyEngine::Log::LogType::Debug, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			logger.lastMessage = "";
			logger.lastFrameCount = 22;
			logger.lastLogType = PonyEngine::Log::LogType::Info;
			PONY_LOG(&engine, PonyEngine::Log::LogType::Debug, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			logger.lastMessage = "";
			logger.lastFrameCount = 22;
			logger.lastLogType = PonyEngine::Log::LogType::Info;
			PONY_LOG_IF(true, &engine, PonyEngine::Log::LogType::Debug, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));

			logger.lastMessage = "";
			logger.lastFrameCount = 22;
			logger.lastLogType = PonyEngine::Log::LogType::Info;
			PONY_LOG_IF(false, &engine, PonyEngine::Log::LogType::Debug, message);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(std::size_t{22}, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Info), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));
		}

		TEST_METHOD(LogExceptionToLogger)
		{
			auto logger = EmptyLogger();
			auto timeManager = TimeManager();
			auto engine = Engine();
			engine.logger = &logger;
			engine.timeManager = &timeManager;

			const auto message = "Message";
			const auto exception = std::exception("Exception");
			timeManager.frameCount = 14;
			PonyEngine::Core::LogExceptionToLogger(engine, exception);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_S(&engine, exception);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PonyEngine::Core::LogExceptionToLogger(engine, exception, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E(&engine, exception, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			PonyEngine::Core::LogExceptionToLogger(engine, exception, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E(&engine, exception, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_S_IF(true, &engine, exception);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_S_IF(false, &engine, exception);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::IsNull(logger.lastException);
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_IF(true, &engine, exception, message);
			Assert::AreEqual(message, logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_IF(false, &engine, exception, message);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::IsNull(logger.lastException);
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_IF(true, &engine, exception, format, formatArg);
			Assert::AreEqual(std::format(format, formatArg).c_str(), logger.lastMessage.c_str());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastMessage = "";
			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PONY_LOG_E_IF(false, &engine, exception, format, formatArg);
			Assert::AreEqual("", logger.lastMessage.c_str());
			Assert::IsNull(logger.lastException);
			Assert::AreEqual(std::size_t{0}, logger.lastFrameCount);
		}
	};
}