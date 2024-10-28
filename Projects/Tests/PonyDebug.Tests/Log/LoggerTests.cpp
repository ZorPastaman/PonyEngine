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
#include <string_view>
#include <type_traits>

#include "Mocks/SubLogger.h"

import PonyDebug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			const PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams());
			Assert::IsNotNull(logger.logger.Get());
		}

		TEST_METHOD(LogTest)
		{
			const auto message = "Message!";
			const auto exception = std::exception("Exception");
			constexpr std::size_t frameCount = 84136;
			const auto logInput = PonyDebug::Log::LogInput(message, frameCount);

			SubLogger testSubLogger;
			const PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams());
			logger.logger->AddSubLogger(testSubLogger);
			testSubLogger.expectedMessage = message;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedFrameCount = frameCount;
			testSubLogger.expectedLogType = PonyDebug::Log::LogType::Info;
			logger.logger->Log(PonyDebug::Log::LogType::Info, logInput);
			Assert::AreEqual(std::size_t{1}, testSubLogger.Version());

			testSubLogger.expectedException = &exception;
			testSubLogger.expectedLogType = PonyDebug::Log::LogType::Exception;
			logger.logger->LogException(exception, logInput);
			Assert::AreEqual(std::size_t{2}, testSubLogger.Version());

			logger.logger->RemoveSubLogger(testSubLogger);
			logger.logger->Log(PonyDebug::Log::LogType::Info, logInput);
			Assert::AreEqual(std::size_t{2}, testSubLogger.Version());
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyDebug::Log::LoggerData logger = PonyDebug::Log::CreateLogger(PonyDebug::Log::LoggerParams());
			Assert::AreEqual(std::string_view("PonyDebug::Log::Logger"), logger.logger->Name());
		}
	};
}
