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
#include <format>
#include <string>
#include <string_view>

#include "Mocks/Logger.h"

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogHelperTests)
	{
		TEST_METHOD(LogToLoggerTest)
		{
			auto logger = Logger();

			constexpr std::string_view message = "Message";

			logger.expectedLogType = PonyDebug::Log::LogType::Info;
			logger.expectedMessage = message;
			PonyDebug::Log::LogToLogger(logger, PonyDebug::Log::LogType::Info, message);
			Assert::AreEqual(std::size_t{1}, logger.Version());

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			const std::string expectedFormat = std::format(format, formatArg);
			logger.expectedLogType = PonyDebug::Log::LogType::Warning;
			logger.expectedMessage = expectedFormat;
			PonyDebug::Log::LogToLogger(logger, PonyDebug::Log::LogType::Warning, format, formatArg);
			Assert::AreEqual(std::size_t{2}, logger.Version());
		}

		TEST_METHOD(LogExceptionToLoggerTest)
		{
			auto logger = Logger();

			constexpr std::string_view message = "Message";
			const auto exception = std::exception("Exception");

			logger.expectedException = &exception;
			PonyDebug::Log::LogExceptionToLogger(logger, exception);
			Assert::AreEqual(std::size_t{1}, logger.Version());

			logger.expectedMessage = message;
			PonyDebug::Log::LogExceptionToLogger(logger, exception, message);
			Assert::AreEqual(std::size_t{2}, logger.Version());

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			const std::string expectedFormat = std::format(format, formatArg);
			logger.expectedMessage = expectedFormat;
			PonyDebug::Log::LogExceptionToLogger(logger, exception, format, formatArg);
			Assert::AreEqual(std::size_t{3}, logger.Version());
		}
	};
}
