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
import <type_traits>;

import PonyEngine.Log;
import PonyEngine.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LoggerTests)
	{
		class TestSubLogger : public PonyEngine::Log::ISubLogger
		{
		public:
			const char* expectedMessage;
			const std::exception* expectedException;
			std::size_t expectedFrameCount;
			PonyEngine::Log::LogType expectedLogType;
			bool expectMessages;
			std::size_t count = 0;

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Log(const PonyEngine::Log::LogEntry& logEntry) noexcept override
			{
				Assert::IsTrue(expectMessages);
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedMessage), reinterpret_cast<std::uintptr_t>(logEntry.GetMessage()));
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException), reinterpret_cast<std::uintptr_t>(logEntry.GetException()));
				Assert::AreEqual(expectedFrameCount, logEntry.GetFrameCount());
				Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logEntry.GetLogType()));
				++count;
			}
		};

		TEST_METHOD(CreateTest)
		{
			PonyEngine::Log::ILogger* const logger = PonyEngine::Log::CreateLogger();
			Assert::IsNotNull(logger);
			PonyEngine::Log::DestroyLogger(logger);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Log::ILogger* const logger = PonyEngine::Log::CreateLogger();
			Assert::AreEqual("PonyEngine::Logger", logger->GetName());
			PonyEngine::Log::DestroyLogger(logger);
		}

		TEST_METHOD(LogTest)
		{
			const char* const message = "Message!";
			const std::exception exception("Exception");
			const std::size_t frameCount = 84136;
			const PonyEngine::Log::LogInput logInput(message, frameCount);

			TestSubLogger testSubLogger;
			PonyEngine::Log::ILogger* const logger = PonyEngine::Log::CreateLogger();
			logger->AddSubLogger(&testSubLogger);
			testSubLogger.expectedMessage = message;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedFrameCount = frameCount;
			testSubLogger.expectMessages = true;
			testSubLogger.expectedLogType = PonyEngine::Log::LogType::Info;
			logger->Log(PonyEngine::Log::LogType::Info, logInput);
			Assert::AreEqual(std::size_t{1}, testSubLogger.count);

			testSubLogger.expectedException = &exception;
			testSubLogger.expectedLogType = PonyEngine::Log::LogType::Exception;
			logger->LogException(exception, logInput);
			Assert::AreEqual(std::size_t{2}, testSubLogger.count);

			logger->RemoveSubLogger(&testSubLogger);
			testSubLogger.expectMessages = false;
			logger->Log(PonyEngine::Log::LogType::Info, logInput);
			Assert::AreEqual(std::size_t{2}, testSubLogger.count);

			PonyEngine::Log::DestroyLogger(logger);
		}
	};
}
