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

import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Debug::Log
{
	TEST_CLASS(LoggerTests)
	{
		class TestSubLogger : public PonyEngine::Debug::Log::ISubLogger
		{
		public:
			const char* expectedMessage;
			const std::exception* expectedException;
			std::size_t expectedFrameCount;
			PonyEngine::Debug::Log::LogType expectedLogType;
			bool expectMessages;

			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override
			{
				return "";
			}

			virtual void Log(const PonyEngine::Debug::Log::LogEntry& logEntry) noexcept override
			{
				Assert::IsTrue(expectMessages);
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedMessage), reinterpret_cast<std::uintptr_t>(logEntry.GetMessage()));
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException), reinterpret_cast<std::uintptr_t>(logEntry.GetException()));
				Assert::AreEqual(expectedFrameCount, logEntry.GetFrameCount());
				Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logEntry.GetLogType()));
			}
		};

		TEST_METHOD(CreateTest)
		{
			PonyEngine::Debug::Log::ILogger* const logger = PonyEngine::Debug::Log::CreateLogger();
			Assert::IsNotNull(logger);
			PonyEngine::Debug::Log::DestroyLogger(logger);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Debug::Log::ILogger* const logger = PonyEngine::Debug::Log::CreateLogger();
			Assert::AreEqual("PonyEngine::Debug::Logger", logger->GetName());
			PonyEngine::Debug::Log::DestroyLogger(logger);
		}

		TEST_METHOD(LogTest)
		{
			const char* const message = "Message!";
			const std::exception exception("Exception");
			const std::size_t frameCount = 84136;
			const PonyEngine::Debug::Log::LogInput logInput(message, frameCount);

			TestSubLogger testSubLogger;
			PonyEngine::Debug::Log::ILogger* const logger = PonyEngine::Debug::Log::CreateLogger();
			logger->AddSubLogger(&testSubLogger);
			testSubLogger.expectedMessage = message;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedFrameCount = frameCount;
			testSubLogger.expectMessages = true;
			testSubLogger.expectedLogType = PonyEngine::Debug::Log::LogType::Info;
			logger->Log(PonyEngine::Debug::Log::LogType::Info, logInput);

			testSubLogger.expectedException = &exception;
			testSubLogger.expectedLogType = PonyEngine::Debug::Log::LogType::Exception;
			logger->LogException(exception, logInput);

			logger->RemoveSubLogger(&testSubLogger);
			testSubLogger.expectMessages = false;
			logger->Log(PonyEngine::Debug::Log::LogType::Info, logInput);

			PonyEngine::Debug::Log::DestroyLogger(logger);
		}
	};
}
