/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <chrono>
#include <cstddef>
#include <format>

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogFormatTests)
	{
		TEST_METHOD(LogFormatTest)
		{
			constexpr auto logType = PonyDebug::Log::LogType::Info;
			constexpr auto timePoint = std::chrono::time_point < std::chrono::system_clock>(std::chrono::seconds(8901124));
			constexpr std::size_t frameCount = 763;
			const auto message = "Message!";
			const auto secondMessage = "Second message.";

			Assert::AreEqual(std::format("[{}] [{:%F %R:%OS UTC}] {}\n", ToString(logType), timePoint, message), PonyDebug::Log::LogFormat(logType, message, timePoint));
			Assert::AreEqual(std::format("[{}] [{:%F %R:%OS UTC} ({})] {}\n", ToString(logType), timePoint, frameCount, message), PonyDebug::Log::LogFormat(logType, message, timePoint, frameCount));
			Assert::AreEqual(std::format("[{}] [{:%F %R:%OS UTC}] {} - {}\n", ToString(logType), timePoint, message, secondMessage), PonyDebug::Log::LogFormat(logType, message, secondMessage, timePoint));
			Assert::AreEqual(std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n", ToString(logType), timePoint, frameCount, message, secondMessage), PonyDebug::Log::LogFormat(logType, message, secondMessage, timePoint, frameCount));
		}
	};
}
