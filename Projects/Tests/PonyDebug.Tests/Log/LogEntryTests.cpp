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
#include <cstdint>
#include <exception>
#include <string>
#include <type_traits>

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogEntryTests)
	{
	public:
		TEST_METHOD(ConstructorTest)
		{
			const auto message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::size_t frameCount = 98407;
			constexpr auto logType = PonyDebug::Log::LogType::Warning;
			constexpr auto exceptionLogType = PonyDebug::Log::LogType::Exception;

			auto logEntry = PonyDebug::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			Assert::AreEqual(message, logEntry.Message());
			Assert::IsNull(logEntry.Exception());
			Assert::IsTrue(timePoint == logEntry.TimePoint());
			Assert::AreEqual(frameCount, logEntry.FrameCount().value());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logEntry.LogType()));

			const auto pureExceptionLogEntry = PonyDebug::Log::LogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			Assert::IsNull(pureExceptionLogEntry.Message());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(pureExceptionLogEntry.Exception()));
			Assert::IsTrue(timePoint == pureExceptionLogEntry.TimePoint());
			Assert::AreEqual(frameCount, pureExceptionLogEntry.FrameCount().value());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(pureExceptionLogEntry.LogType()));

			const auto exceptionLogEntry = PonyDebug::Log::LogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			Assert::AreEqual(message, logEntry.Message());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(exceptionLogEntry.Exception()));
			Assert::IsTrue(timePoint == exceptionLogEntry.TimePoint());
			Assert::AreEqual(frameCount, exceptionLogEntry.FrameCount().value());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(exceptionLogEntry.LogType()));
		}

		TEST_METHOD(ToStringTest)
		{
			const auto message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::size_t frameCount = 98407;
			constexpr auto logType = PonyDebug::Log::LogType::Warning;
			constexpr auto exceptionLogType = PonyDebug::Log::LogType::Exception;

			const auto logEntry = PonyDebug::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			const std::string logEntryString = logEntry.ToString();
			Assert::AreEqual("[Warning] [1970-01-06 05:13:00 UTC (98407)] Message.\n", logEntryString.c_str());
			std::ostringstream logEntrySs;
			logEntrySs << logEntry;
			Assert::AreEqual(logEntryString.c_str(), logEntrySs.str().c_str());

			const auto pureExceptionLogEntry = PonyDebug::Log::LogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			const std::string pureExceptionLogEntryString = pureExceptionLogEntry.ToString();
			Assert::AreEqual("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text.\n", pureExceptionLogEntryString.c_str());
			std::ostringstream pureExceptionLogEntrySs;
			pureExceptionLogEntrySs << pureExceptionLogEntry;
			Assert::AreEqual(pureExceptionLogEntryString.c_str(), pureExceptionLogEntrySs.str().c_str());

			const auto exceptionLogEntry = PonyDebug::Log::LogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			const std::string exceptionLogEntryString = exceptionLogEntry.ToString();
			Assert::AreEqual("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text. - Message.\n", exceptionLogEntryString.c_str());
			std::ostringstream exceptionLogEntrySs;
			exceptionLogEntrySs << exceptionLogEntry;
			Assert::AreEqual(exceptionLogEntryString.c_str(), exceptionLogEntrySs.str().c_str());

			const auto emptyLogEntry = PonyDebug::Log::LogEntry(nullptr, nullptr, timePoint, frameCount, logType);
			const std::string emptyLogEntryString = emptyLogEntry.ToString();
			Assert::AreEqual("[Warning] [1970-01-06 05:13:00 UTC (98407)] \n", emptyLogEntryString.c_str());
			std::ostringstream emptyLogEntrySs;
			emptyLogEntrySs << emptyLogEntry;
			Assert::AreEqual(emptyLogEntryString.c_str(), emptyLogEntrySs.str().c_str());
		}
	};
}
