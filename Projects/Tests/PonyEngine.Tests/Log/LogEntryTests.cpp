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
import <string>;
import <type_traits>;

import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogEntryTests)
	{
	public:
		TEST_METHOD(ConstructorTest)
		{
			const char* const message = "Message.";
			const std::exception exception("Exception text.");
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(450780));
			const std::size_t frameCount = 98407;
			const PonyEngine::Log::LogType logType = PonyEngine::Log::LogType::Warning;
			const PonyEngine::Log::LogType exceptionLogType = PonyEngine::Log::LogType::Exception;

			const PonyEngine::Log::LogEntry logEntry(message, nullptr, timePoint, frameCount, logType);
			Assert::AreEqual(message, logEntry.GetMessage());
			Assert::IsNull(logEntry.GetException());
			Assert::IsTrue(timePoint == logEntry.GetTimePoint());
			Assert::AreEqual(frameCount, logEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logEntry.GetLogType()));

			const PonyEngine::Log::LogEntry pureExceptionLogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			Assert::IsNull(pureExceptionLogEntry.GetMessage());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(pureExceptionLogEntry.GetException()));
			Assert::IsTrue(timePoint == pureExceptionLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, pureExceptionLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(pureExceptionLogEntry.GetLogType()));

			const PonyEngine::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			Assert::AreEqual(message, logEntry.GetMessage());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(exceptionLogEntry.GetException()));
			Assert::IsTrue(timePoint == exceptionLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, exceptionLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(exceptionLogEntry.GetLogType()));
		}

		TEST_METHOD(ToStringTest)
		{
			const char* const message = "Message.";
			const std::exception exception("Exception text.");
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(450780));
			const std::size_t frameCount = 98407;
			const PonyEngine::Log::LogType logType = PonyEngine::Log::LogType::Warning;
			const PonyEngine::Log::LogType exceptionLogType = PonyEngine::Log::LogType::Exception;

			const PonyEngine::Log::LogEntry logEntry(message, nullptr, timePoint, frameCount, logType);
			const std::string logEntryString = logEntry.ToString();
			Assert::AreEqual("[Warning] [1970-01-06 05:13:00 UTC (98407)] Message.", logEntryString.c_str());
			std::ostringstream logEntrySS;
			logEntrySS << logEntry;
			Assert::AreEqual(logEntryString.c_str(), logEntrySS.str().c_str());

			const PonyEngine::Log::LogEntry pureExceptionLogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			const std::string pureExceptionLogEntryString = pureExceptionLogEntry.ToString();
			Assert::AreEqual("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text.", pureExceptionLogEntryString.c_str());
			std::ostringstream pureExceptionLogEntrySS;
			pureExceptionLogEntrySS << pureExceptionLogEntry;
			Assert::AreEqual(pureExceptionLogEntryString.c_str(), pureExceptionLogEntrySS.str().c_str());

			const PonyEngine::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			const std::string exceptionLogEntryString = exceptionLogEntry.ToString();
			Assert::AreEqual("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text. - Message.", exceptionLogEntryString.c_str());
			std::ostringstream exceptionLogEntrySS;
			exceptionLogEntrySS << exceptionLogEntry;
			Assert::AreEqual(exceptionLogEntryString.c_str(), exceptionLogEntrySS.str().c_str());
		}
	};
}
