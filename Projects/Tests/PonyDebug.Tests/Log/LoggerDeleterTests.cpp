/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyDebug.Log.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LoggerDeleterTests)
	{
		class EmptyLogger final : public PonyDebug::Log::ILogger
		{
		public:
			virtual void Log(const PonyDebug::Log::LogType, const PonyDebug::Log::LogInput&) noexcept override
			{
			}

			virtual void LogException(const std::exception&, const PonyDebug::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyDebug::Log::ISubLogger&) override
			{
			}

			virtual void RemoveSubLogger(PonyDebug::Log::ISubLogger&) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class LoggerDestroyer final : public PonyDebug::Log::ILoggerDestroyer
		{
		public:
			PonyDebug::Log::ILogger* lastLogger = nullptr;

			virtual void Destroy(PonyDebug::Log::ILogger* logger) noexcept override
			{
				lastLogger = logger;
			}
		};

		TEST_METHOD(ConstructorTest)
		{
			auto loggerDestroyer = LoggerDestroyer();
			const auto loggerDeleter = PonyDebug::Log::LoggerDeleter(loggerDestroyer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&loggerDestroyer), reinterpret_cast<std::uintptr_t>(loggerDeleter.LoggerDestroyer()));

			PonyDebug::Log::LoggerDeleter copiedLoggerDeleter = loggerDeleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&loggerDestroyer), reinterpret_cast<std::uintptr_t>(copiedLoggerDeleter.LoggerDestroyer()));

			const PonyDebug::Log::LoggerDeleter movedLoggerDeleter = std::move(copiedLoggerDeleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&loggerDestroyer), reinterpret_cast<std::uintptr_t>(movedLoggerDeleter.LoggerDestroyer()));
		}

		TEST_METHOD(DeleteTest)
		{
			const auto logger = new EmptyLogger();
			auto loggerDestroyer = LoggerDestroyer();
			const auto loggerDeleter = PonyDebug::Log::LoggerDeleter(loggerDestroyer);
			loggerDeleter(logger);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(logger), reinterpret_cast<std::uintptr_t>(loggerDestroyer.lastLogger));

			delete logger;
		}

		TEST_METHOD(AssignmentTest)
		{
			auto loggerDestroyer = LoggerDestroyer();
			auto anotherLoggerDestroyer = LoggerDestroyer();
			auto loggerDeleter = PonyDebug::Log::LoggerDeleter(loggerDestroyer);

			auto copiedLoggerDeleter = PonyDebug::Log::LoggerDeleter(anotherLoggerDestroyer);
			copiedLoggerDeleter = loggerDeleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&loggerDestroyer), reinterpret_cast<std::uintptr_t>(copiedLoggerDeleter.LoggerDestroyer()));

			auto movedLoggerDeleter = PonyDebug::Log::LoggerDeleter(anotherLoggerDestroyer);
			movedLoggerDeleter = std::move(loggerDeleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&loggerDestroyer), reinterpret_cast<std::uintptr_t>(movedLoggerDeleter.LoggerDestroyer()));
		}
	};
}
