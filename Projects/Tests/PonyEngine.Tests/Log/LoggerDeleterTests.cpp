/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Log.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LoggerDeleterTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			virtual void Log(const PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}

			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class LoggerDestroyer final : public PonyEngine::Log::ILoggerDestroyer
		{
		public:
			PonyEngine::Log::ILogger* lastLogger = nullptr;

			virtual void Destroy(PonyEngine::Log::ILogger* logger) noexcept override
			{
				lastLogger = logger;
			}
		};

		TEST_METHOD(ConstructorTest)
		{
			auto loggerDestroyer = LoggerDestroyer();
			const auto loggerDeleter = PonyEngine::Log::LoggerDeleter(loggerDestroyer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&loggerDestroyer), reinterpret_cast<std::uintptr_t>(&loggerDeleter.LoggerDestroyer()));
		}

		TEST_METHOD(DeleteTest)
		{
			const auto logger = new EmptyLogger();
			auto loggerDestroyer = LoggerDestroyer();
			const auto loggerDeleter = PonyEngine::Log::LoggerDeleter(loggerDestroyer);
			loggerDeleter(logger);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(logger), reinterpret_cast<std::uintptr_t>(loggerDestroyer.lastLogger));

			delete logger;
		}
	};
}
