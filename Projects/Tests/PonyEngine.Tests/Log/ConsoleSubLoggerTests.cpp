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

import PonyEngine.Log;
import PonyEngine.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(ConsoleSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			PonyEngine::Log::ISubLogger* const consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
			Assert::IsNotNull(consoleSubLogger);
			PonyEngine::Log::DestroyConsoleSubLogger(consoleSubLogger);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Log::ISubLogger* const consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();
			Assert::AreEqual("PonyEngine::Log::ConsoleSubLogger", consoleSubLogger->GetName());
			PonyEngine::Log::DestroyConsoleSubLogger(consoleSubLogger);
		}

		TEST_METHOD(LogTest)
		{
			const char* const message = "Message!";
			const std::exception exception("Exception");
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(5691338));
			const std::size_t frameCount = 84136;

			PonyEngine::Log::ISubLogger* const consoleSubLogger = PonyEngine::Log::CreateConsoleSubLogger();

			std::ostringstream verboseStream;
			std::streambuf* const coutBuffer = std::cout.rdbuf(verboseStream.rdbuf());
			const PonyEngine::Log::LogEntry verboseLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Verbose);
			consoleSubLogger->Log(verboseLogEntry);
			Assert::AreEqual(verboseLogEntry.ToString() + '\n', verboseStream.str());

			std::ostringstream debugStream;
			std::cout.rdbuf(debugStream.rdbuf());
			const PonyEngine::Log::LogEntry debugLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Debug);
			consoleSubLogger->Log(debugLogEntry);
			Assert::AreEqual(debugLogEntry.ToString() + '\n', debugStream.str());

			std::ostringstream infoStream;
			std::cout.rdbuf(infoStream.rdbuf());
			const PonyEngine::Log::LogEntry infoLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Info);
			consoleSubLogger->Log(infoLogEntry);
			Assert::AreEqual(infoLogEntry.ToString() + '\n', infoStream.str());

			std::ostringstream warningStream;
			std::streambuf* const clogBuffer = std::clog.rdbuf(warningStream.rdbuf());
			const PonyEngine::Log::LogEntry warningLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Warning);
			consoleSubLogger->Log(warningLogEntry);
			Assert::AreEqual(warningLogEntry.ToString() + '\n', warningStream.str());

			std::ostringstream errorStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());
			const PonyEngine::Log::LogEntry errorLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Error);
			consoleSubLogger->Log(errorLogEntry);
			Assert::AreEqual(errorLogEntry.ToString() + '\n', errorStream.str());

			std::ostringstream exceptionStream;
			std::cerr.rdbuf(exceptionStream.rdbuf());
			const PonyEngine::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, PonyEngine::Log::LogType::Exception);
			consoleSubLogger->Log(exceptionLogEntry);
			Assert::AreEqual(exceptionLogEntry.ToString() + '\n', exceptionStream.str());

			std::cout.rdbuf(coutBuffer);
			std::clog.rdbuf(clogBuffer);
			std::cerr.rdbuf(cerrBuffer);
;			PonyEngine::Log::DestroyConsoleSubLogger(consoleSubLogger);
		}
	};
}
