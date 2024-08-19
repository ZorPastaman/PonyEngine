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
import <iostream>;
import <string>;

import PonyEngine.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(ConsoleSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			const PonyEngine::Log::ConsoleSubLoggerData consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
			Assert::IsNotNull(consoleSubLogger.subLogger.get());
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyEngine::Log::ConsoleSubLoggerData consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
			Assert::AreEqual("PonyEngine::Log::ConsoleSubLogger", consoleSubLogger.subLogger->Name());
		}

		TEST_METHOD(LogTest)
		{
			auto message = "Message!";
			const auto exception = std::exception("Exception");
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(5691338));
			constexpr std::size_t frameCount = 84136;

			const PonyEngine::Log::ConsoleSubLoggerData consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();

			std::ostringstream verboseStream;
			std::streambuf* const coutBuffer = std::cout.rdbuf(verboseStream.rdbuf());
			const PonyEngine::Log::LogEntry verboseLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Verbose);
			consoleSubLogger.subLogger->Log(verboseLogEntry);
			Assert::AreEqual(verboseLogEntry.ToString(), verboseStream.str().c_str());

			std::ostringstream debugStream;
			std::cout.rdbuf(debugStream.rdbuf());
			const PonyEngine::Log::LogEntry debugLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Debug);
			consoleSubLogger.subLogger->Log(debugLogEntry);
			Assert::AreEqual(debugLogEntry.ToString(), debugStream.str().c_str());

			std::ostringstream infoStream;
			std::cout.rdbuf(infoStream.rdbuf());
			const PonyEngine::Log::LogEntry infoLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Info);
			consoleSubLogger.subLogger->Log(infoLogEntry);
			Assert::AreEqual(infoLogEntry.ToString(), infoStream.str().c_str());

			std::ostringstream warningStream;
			std::streambuf* const clogBuffer = std::clog.rdbuf(warningStream.rdbuf());
			const PonyEngine::Log::LogEntry warningLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Warning);
			consoleSubLogger.subLogger->Log(warningLogEntry);
			Assert::AreEqual(warningLogEntry.ToString(), warningStream.str().c_str());

			std::ostringstream errorStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());
			const PonyEngine::Log::LogEntry errorLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Error);
			consoleSubLogger.subLogger->Log(errorLogEntry);
			Assert::AreEqual(errorLogEntry.ToString(), errorStream.str().c_str());

			std::ostringstream exceptionStream;
			std::cerr.rdbuf(exceptionStream.rdbuf());
			const PonyEngine::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, PonyEngine::Log::LogType::Exception);
			consoleSubLogger.subLogger->Log(exceptionLogEntry);
			Assert::AreEqual(exceptionLogEntry.ToString(), exceptionStream.str().c_str());

			std::cout.rdbuf(coutBuffer);
			std::clog.rdbuf(clogBuffer);
			std::cerr.rdbuf(cerrBuffer);
		}
	};
}
