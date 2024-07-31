/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstddef>;
import <cstdint>;
import <exception>;

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
			const char* lastMessage;
			const std::exception* lastException;
			std::size_t lastFrameCount;
			PonyEngine::Log::LogType lastLogType;

			virtual void Log(const PonyEngine::Log::LogType logType, const PonyEngine::Log::LogInput& logInput) noexcept override
			{
				lastMessage = logInput.message;
				lastFrameCount = logInput.frameCount;
				lastLogType = logType;
			}

			virtual void LogException(const std::exception& exception, const PonyEngine::Log::LogInput& logInput) noexcept override
			{
				lastMessage = logInput.message;
				lastFrameCount = logInput.frameCount;
				lastException = &exception;
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger* subLogger) override
			{
			}

			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger* subLogger) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}
		};

		class TimeManager final : public PonyEngine::Core::ITimeManager
		{
		public:
			std::size_t frameCount;

			[[nodiscard("Pure function")]]
			virtual std::size_t GetFrameCount() const noexcept override
			{
				return frameCount;
			}

			[[nodiscard("Pure function")]]
			virtual float GetTargetFrameTime() const noexcept override
			{
				return 0.f;
			}

			virtual void SetTargetFrameTime(float frameTime) noexcept override
			{
			}
		};

		class SystemManager final : public PonyEngine::Core::ISystemManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info& typeInfo) const noexcept override
			{
				return nullptr;
			}
		};

		class Engine final : public PonyEngine::Core::IEngine
		{
		public:
			EmptyLogger* logger;
			TimeManager* timeManager;

			SystemManager* systemManager;

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& GetLogger() const noexcept override
			{
				return *logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ITimeManager& GetTimeManager() const noexcept override
			{
				return *timeManager;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystemManager& GetSystemManager() const noexcept override
			{
				return *systemManager;
			}

			[[nodiscard("Pure function")]]
			virtual bool GetIsRunning() const noexcept override
			{
				return false;
			}

			[[nodiscard("Pure function")]]
			virtual int GetExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int exitCode) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
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
			Assert::AreEqual(message, logger.lastMessage);
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(PonyEngine::Log::LogType::Debug), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logger.lastLogType));
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
			Assert::IsNull(logger.lastMessage);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);

			logger.lastException = nullptr;
			logger.lastFrameCount = 0;
			PonyEngine::Core::LogExceptionToLogger(engine, exception, message);
			Assert::AreEqual(message, logger.lastMessage);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(logger.lastException));
			Assert::AreEqual(timeManager.frameCount, logger.lastFrameCount);
		}
	};
}