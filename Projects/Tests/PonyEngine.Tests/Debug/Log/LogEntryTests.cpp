/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <chrono>;
import <cstddef>;
import <cstdint>;
import <exception>;
import <type_traits>;

import PonyEngine.Debug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Debug::Log
{
	TEST_CLASS(LogEntryTests)
	{
	public:
		TEST_METHOD(ConstructorTest)
		{
			const char* const message = "Message";
			const std::exception exception("Exception");
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(450780));
			const std::size_t frameCount = 98407;
			const PonyEngine::Debug::Log::LogType logType = PonyEngine::Debug::Log::LogType::Warning;
			const PonyEngine::Debug::Log::LogType exceptionLogType = PonyEngine::Debug::Log::LogType::Exception;

			const PonyEngine::Debug::Log::LogEntry logEntry(message, nullptr, timePoint, frameCount, logType);
			Assert::AreEqual(message, logEntry.GetMessage());
			Assert::IsNull(logEntry.GetException());
			Assert::IsTrue(timePoint == logEntry.GetTimePoint());
			Assert::AreEqual(frameCount, logEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logEntry.GetLogType()));

			const PonyEngine::Debug::Log::LogEntry pureExceptionLogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			Assert::IsNull(pureExceptionLogEntry.GetMessage());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(pureExceptionLogEntry.GetException()));
			Assert::IsTrue(timePoint == pureExceptionLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, pureExceptionLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(pureExceptionLogEntry.GetLogType()));

			const PonyEngine::Debug::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			Assert::AreEqual(message, logEntry.GetMessage());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(exceptionLogEntry.GetException()));
			Assert::IsTrue(timePoint == exceptionLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, exceptionLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(exceptionLogEntry.GetLogType()));
		}
	};
}
