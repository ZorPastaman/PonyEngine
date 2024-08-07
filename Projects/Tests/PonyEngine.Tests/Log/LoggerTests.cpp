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
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Log(const PonyEngine::Log::LogEntry& logEntry) noexcept override
			{
				Assert::IsTrue(expectMessages);
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedMessage), reinterpret_cast<std::uintptr_t>(logEntry.Message()));
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException), reinterpret_cast<std::uintptr_t>(logEntry.Exception()));
				Assert::AreEqual(expectedFrameCount, logEntry.FrameCount());
				Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logEntry.LogType()));
				++count;
			}
		};

		TEST_METHOD(CreateTest)
		{
			const PonyEngine::Log::LoggerUniquePtr logger = PonyEngine::Log::CreateLogger();
			Assert::IsNotNull(logger.get());
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyEngine::Log::LoggerUniquePtr logger = PonyEngine::Log::CreateLogger();
			Assert::AreEqual("PonyEngine::Log::Logger", logger->Name());
		}

		TEST_METHOD(LogTest)
		{
			const auto message = "Message!";
			const auto exception = std::exception("Exception");
			constexpr std::size_t frameCount = 84136;
			const auto logInput = PonyEngine::Log::LogInput(message, frameCount);

			TestSubLogger testSubLogger;
			const PonyEngine::Log::LoggerUniquePtr logger = PonyEngine::Log::CreateLogger();
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
		}
	};
}
