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
			const auto message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::size_t frameCount = 98407;
			constexpr auto logType = PonyEngine::Log::LogType::Warning;
			constexpr auto exceptionLogType = PonyEngine::Log::LogType::Exception;

			auto logEntry = PonyEngine::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			Assert::AreEqual(message, logEntry.GetMessage());
			Assert::IsNull(logEntry.GetException());
			Assert::IsTrue(timePoint == logEntry.GetTimePoint());
			Assert::AreEqual(frameCount, logEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logEntry.GetLogType()));

			const auto pureExceptionLogEntry = PonyEngine::Log::LogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			Assert::IsNull(pureExceptionLogEntry.GetMessage());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(pureExceptionLogEntry.GetException()));
			Assert::IsTrue(timePoint == pureExceptionLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, pureExceptionLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(pureExceptionLogEntry.GetLogType()));

			const auto exceptionLogEntry = PonyEngine::Log::LogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			Assert::AreEqual(message, logEntry.GetMessage());
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&exception), reinterpret_cast<std::uintptr_t>(exceptionLogEntry.GetException()));
			Assert::IsTrue(timePoint == exceptionLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, exceptionLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(exceptionLogType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(exceptionLogEntry.GetLogType()));

			auto copiedLogEntry = logEntry;
			Assert::AreEqual(message, copiedLogEntry.GetMessage());
			Assert::IsNull(copiedLogEntry.GetException());
			Assert::IsTrue(timePoint == copiedLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, copiedLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(copiedLogEntry.GetLogType()));

			auto movedLogEntry = std::move(logEntry);
			Assert::AreEqual(message, movedLogEntry.GetMessage());
			Assert::IsNull(movedLogEntry.GetException());
			Assert::IsTrue(timePoint == movedLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, movedLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(movedLogEntry.GetLogType()));
		}

		TEST_METHOD(ToStringTest)
		{
			const auto message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::size_t frameCount = 98407;
			constexpr auto logType = PonyEngine::Log::LogType::Warning;
			constexpr auto exceptionLogType = PonyEngine::Log::LogType::Exception;

			const auto logEntry = PonyEngine::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			const std::string logEntryString = logEntry.ToString();
			Assert::AreEqual("[Warning] [1970-01-06 05:13:00 UTC (98407)] Message.", logEntryString.c_str());
			std::ostringstream logEntrySs;
			logEntrySs << logEntry;
			Assert::AreEqual(logEntryString.c_str(), logEntrySs.str().c_str());

			const auto pureExceptionLogEntry = PonyEngine::Log::LogEntry(nullptr, &exception, timePoint, frameCount, exceptionLogType);
			const std::string pureExceptionLogEntryString = pureExceptionLogEntry.ToString();
			Assert::AreEqual("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text.", pureExceptionLogEntryString.c_str());
			std::ostringstream pureExceptionLogEntrySs;
			pureExceptionLogEntrySs << pureExceptionLogEntry;
			Assert::AreEqual(pureExceptionLogEntryString.c_str(), pureExceptionLogEntrySs.str().c_str());

			const auto exceptionLogEntry = PonyEngine::Log::LogEntry(message, &exception, timePoint, frameCount, exceptionLogType);
			const std::string exceptionLogEntryString = exceptionLogEntry.ToString();
			Assert::AreEqual("[Exception] [1970-01-06 05:13:00 UTC (98407)] Exception text. - Message.", exceptionLogEntryString.c_str());
			std::ostringstream exceptionLogEntrySs;
			exceptionLogEntrySs << exceptionLogEntry;
			Assert::AreEqual(exceptionLogEntryString.c_str(), exceptionLogEntrySs.str().c_str());
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto message = "Message.";
			const auto exception = std::exception("Exception text.");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450780));
			constexpr std::size_t frameCount = 98407;
			constexpr auto logType = PonyEngine::Log::LogType::Warning;

			auto logEntry = PonyEngine::Log::LogEntry(message, nullptr, timePoint, frameCount, logType);
			auto copiedLogEntry = PonyEngine::Log::LogEntry("Something", nullptr, std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450)), 123, PonyEngine::Log::LogType::Debug);
			copiedLogEntry = logEntry;
			Assert::AreEqual(message, copiedLogEntry.GetMessage());
			Assert::IsNull(copiedLogEntry.GetException());
			Assert::IsTrue(timePoint == copiedLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, copiedLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(copiedLogEntry.GetLogType()));

			auto movedLogEntry = PonyEngine::Log::LogEntry("Something", nullptr, std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(450)), 123, PonyEngine::Log::LogType::Debug);
			movedLogEntry = std::move(logEntry);
			Assert::AreEqual(message, movedLogEntry.GetMessage());
			Assert::IsNull(movedLogEntry.GetException());
			Assert::IsTrue(timePoint == movedLogEntry.GetTimePoint());
			Assert::AreEqual(frameCount, movedLogEntry.GetFrameCount());
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(logType), static_cast<std::underlying_type_t<PonyEngine::Log::LogType>>(movedLogEntry.GetLogType()));
		}
	};
}
