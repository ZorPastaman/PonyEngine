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
#include <string_view>
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
			constexpr std::string_view message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::int64_t frameCount = 98407;
			constexpr auto logType = PonyDebug::Log::LogType::Warning;
			constexpr auto exceptionLogType = PonyDebug::Log::LogType::Exception;

			auto logEntry = PonyDebug::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			Assert::AreEqual(message, logEntry.Message());
			Assert::IsNull(logEntry.Exception());
			Assert::IsTrue(timePoint == logEntry.TimePoint());
			Assert::AreEqual(frameCount, logEntry.FrameCount().value());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyDebug::Log::LogType>>(logEntry.LogType()));

			const auto pureExceptionLogEntry = PonyDebug::Log::LogEntry(std::string_view(), &exception, timePoint, frameCount, exceptionLogType);
			Assert::IsTrue(pureExceptionLogEntry.Message().empty());
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
			constexpr std::string_view message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::size_t frameCount = 98407;
			constexpr auto logType = PonyDebug::Log::LogType::Warning;
			constexpr auto exceptionLogType = PonyDebug::Log::LogType::Exception;

			const auto logEntry = PonyDebug::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			const std::string_view logEntryString = logEntry.ToString();
			Assert::AreEqual(std::string_view("[Warning] [1970-01-06 05:13:00 UTC (98407)] Message.\n"), logEntryString);
			std::ostringstream logEntrySs;
			logEntrySs << logEntry;
			Assert::AreEqual(logEntryString, std::string_view(logEntrySs.str()));

			const auto pureExceptionLogEntry = PonyDebug::Log::LogEntry(std::string_view(), &exception, timePoint, frameCount, exceptionLogType);
			const std::string_view pureExceptionLogEntryString = pureExceptionLogEntry.ToString();
			Assert::AreEqual(std::string_view("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text.\n"), pureExceptionLogEntryString);
			std::ostringstream pureExceptionLogEntrySs;
			pureExceptionLogEntrySs << pureExceptionLogEntry;
			Assert::AreEqual(pureExceptionLogEntryString, std::string_view(pureExceptionLogEntrySs.str()));

			const auto exceptionLogEntry = PonyDebug::Log::LogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			const std::string_view exceptionLogEntryString = exceptionLogEntry.ToString();
			Assert::AreEqual(std::string_view("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text. - Message.\n"), exceptionLogEntryString);
			std::ostringstream exceptionLogEntrySs;
			exceptionLogEntrySs << exceptionLogEntry;
			Assert::AreEqual(exceptionLogEntryString, std::string_view(exceptionLogEntrySs.str()));

			const auto emptyLogEntry = PonyDebug::Log::LogEntry(std::string_view(), nullptr, timePoint, frameCount, logType);
			const std::string_view emptyLogEntryString = emptyLogEntry.ToString();
			Assert::AreEqual(std::string_view("[Warning] [1970-01-06 05:13:00 UTC (98407)]\n"), emptyLogEntryString);
			std::ostringstream emptyLogEntrySs;
			emptyLogEntrySs << emptyLogEntry;
			Assert::AreEqual(emptyLogEntryString, std::string_view(emptyLogEntrySs.str()));
		}
	};
}
