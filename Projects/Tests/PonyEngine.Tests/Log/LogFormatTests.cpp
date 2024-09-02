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

import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogFormatTests)
	{
		TEST_METHOD(LogFormatTest)
		{
			constexpr auto logType = PonyEngine::Log::LogType::Info;
			constexpr auto timePoint = std::chrono::time_point < std::chrono::system_clock>(std::chrono::seconds(8901124));
			constexpr std::size_t frameCount = 763;
			const auto message = "Message!";
			const auto secondMessage = "Second message.";

			Assert::AreEqual(std::format("[{}] {}\n", ToString(logType), message), PonyEngine::Log::LogFormat(logType, message));
			Assert::AreEqual(std::format("[{}] [{:%F %R:%OS UTC} ({})] {}\n", ToString(logType), timePoint, frameCount, message), PonyEngine::Log::LogFormat(logType, message, timePoint, frameCount));
			Assert::AreEqual(std::format("[{}] {} - {}\n", ToString(logType), message, secondMessage), PonyEngine::Log::LogFormat(logType, message, secondMessage));
			Assert::AreEqual(std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n", ToString(logType), timePoint, frameCount, message, secondMessage), PonyEngine::Log::LogFormat(logType, message, secondMessage, timePoint, frameCount));
		}
	};
}
