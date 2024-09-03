/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <type_traits>

import PonyDebug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LoggerTests)
	{
		class TestSubLogger : public PonyDebug::Log::ISubLogger
		{
		public:
			const char* expectedMessage;
			const std::exception* expectedException;
			std::size_t expectedFrameCount;
			PonyDebug::Log::LogType expectedLogType;
			bool expectMessages;
			std::size_t count = 0;

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}

			virtual void Log(const PonyDebug::Log::LogEntry& logEntry) noexcept override
			{
				Assert::IsTrue(expectMessages);
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedMessage), reinterpret_cast<std::uintptr_t>(logEntry.Message()));
				Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException), reinterpret_cast<std::uintptr_t>(logEntry.Exception()));
				Assert::AreEqual(expectedFrameCount, logEntry.FrameCount());
				Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logEntry.LogType()));
				++count;
			}
		};

		TEST_METHOD(CreateTest)
		{
			const PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams());
			Assert::IsNotNull(logger.logger.get());
		}

		TEST_METHOD(LogTest)
		{
			const auto message = "Message!";
			const auto exception = std::exception("Exception");
			constexpr std::size_t frameCount = 84136;
			const auto logInput = PonyDebug::Log::LogInput(message, frameCount);

			TestSubLogger testSubLogger;
			const PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams());
			logger.logger->AddSubLogger(testSubLogger);
			testSubLogger.expectedMessage = message;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedFrameCount = frameCount;
			testSubLogger.expectMessages = true;
			testSubLogger.expectedLogType = PonyDebug::Log::LogType::Info;
			logger.logger->Log(PonyDebug::Log::LogType::Info, logInput);
			Assert::AreEqual(std::size_t{1}, testSubLogger.count);

			testSubLogger.expectedException = &exception;
			testSubLogger.expectedLogType = PonyDebug::Log::LogType::Exception;
			logger.logger->LogException(exception, logInput);
			Assert::AreEqual(std::size_t{2}, testSubLogger.count);

			logger.logger->RemoveSubLogger(testSubLogger);
			testSubLogger.expectMessages = false;
			logger.logger->Log(PonyDebug::Log::LogType::Info, logInput);
			Assert::AreEqual(std::size_t{2}, testSubLogger.count);
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams());
			Assert::AreEqual("PonyDebug::Log::Logger", logger.logger->Name());
		}
	};
}
