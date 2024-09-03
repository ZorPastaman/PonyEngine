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
#include <iostream>
#include <string>

import PonyDebug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(ConsoleSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			const PonyDebug::Log::ConsoleSubLoggerData consoleSubLogger = PonyDebug::Log::CreateConsoleSubLogger(PonyDebug::Log::ConsoleSubLoggerParams());
			Assert::IsNotNull(consoleSubLogger.subLogger.get());
		}

		TEST_METHOD(LogTest)
		{
			auto message = "Message!";
			const auto exception = std::exception("Exception");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(5691338));
			constexpr std::size_t frameCount = 84136;

			const PonyDebug::Log::ConsoleSubLoggerData consoleSubLogger = PonyDebug::Log::CreateConsoleSubLogger(PonyDebug::Log::ConsoleSubLoggerParams());

			std::ostringstream verboseStream;
			std::streambuf* const coutBuffer = std::cout.rdbuf(verboseStream.rdbuf());
			const PonyDebug::Log::LogEntry verboseLogEntry(message, nullptr, timePoint, frameCount, PonyDebug::Log::LogType::Verbose);
			consoleSubLogger.subLogger->Log(verboseLogEntry);
			Assert::AreEqual(verboseLogEntry.ToString(), verboseStream.str().c_str());

			std::ostringstream debugStream;
			std::cout.rdbuf(debugStream.rdbuf());
			const PonyDebug::Log::LogEntry debugLogEntry(message, nullptr, timePoint, frameCount, PonyDebug::Log::LogType::Debug);
			consoleSubLogger.subLogger->Log(debugLogEntry);
			Assert::AreEqual(debugLogEntry.ToString(), debugStream.str().c_str());

			std::ostringstream infoStream;
			std::cout.rdbuf(infoStream.rdbuf());
			const PonyDebug::Log::LogEntry infoLogEntry(message, nullptr, timePoint, frameCount, PonyDebug::Log::LogType::Info);
			consoleSubLogger.subLogger->Log(infoLogEntry);
			Assert::AreEqual(infoLogEntry.ToString(), infoStream.str().c_str());

			std::ostringstream warningStream;
			std::streambuf* const clogBuffer = std::clog.rdbuf(warningStream.rdbuf());
			const PonyDebug::Log::LogEntry warningLogEntry(message, nullptr, timePoint, frameCount, PonyDebug::Log::LogType::Warning);
			consoleSubLogger.subLogger->Log(warningLogEntry);
			Assert::AreEqual(warningLogEntry.ToString(), warningStream.str().c_str());

			std::ostringstream errorStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());
			const PonyDebug::Log::LogEntry errorLogEntry(message, nullptr, timePoint, frameCount, PonyDebug::Log::LogType::Error);
			consoleSubLogger.subLogger->Log(errorLogEntry);
			Assert::AreEqual(errorLogEntry.ToString(), errorStream.str().c_str());

			std::ostringstream exceptionStream;
			std::cerr.rdbuf(exceptionStream.rdbuf());
			const PonyDebug::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, PonyDebug::Log::LogType::Exception);
			consoleSubLogger.subLogger->Log(exceptionLogEntry);
			Assert::AreEqual(exceptionLogEntry.ToString(), exceptionStream.str().c_str());

			std::cout.rdbuf(coutBuffer);
			std::clog.rdbuf(clogBuffer);
			std::cerr.rdbuf(cerrBuffer);
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyDebug::Log::ConsoleSubLoggerData consoleSubLogger = PonyDebug::Log::CreateConsoleSubLogger(PonyDebug::Log::ConsoleSubLoggerParams());
			Assert::AreEqual("PonyDebug::Log::ConsoleSubLogger", consoleSubLogger.subLogger->Name());
		}
	};
}
