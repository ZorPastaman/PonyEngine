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

import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Debug::Log
{
	TEST_CLASS(ConsoleSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			PonyEngine::Debug::Log::ISubLogger* const consoleSubLogger = PonyEngine::Debug::Log::CreateConsoleSubLogger();
			Assert::IsNotNull(consoleSubLogger);
			PonyEngine::Debug::Log::DestroyConsoleSubLogger(consoleSubLogger);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Debug::Log::ISubLogger* const consoleSubLogger = PonyEngine::Debug::Log::CreateConsoleSubLogger();
			Assert::AreEqual("PonyEngine::Debug::Log::ConsoleSubLogger", consoleSubLogger->GetName());
			PonyEngine::Debug::Log::DestroyConsoleSubLogger(consoleSubLogger);
		}

		TEST_METHOD(LogTest)
		{
			const char* const message = "Message!";
			const std::exception exception("Exception");
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(5691338));
			const std::size_t frameCount = 84136;

			PonyEngine::Debug::Log::ISubLogger* const consoleSubLogger = PonyEngine::Debug::Log::CreateConsoleSubLogger();

			std::ostringstream verboseStream;
			std::streambuf* const coutBuffer = std::cout.rdbuf(verboseStream.rdbuf());
			const PonyEngine::Debug::Log::LogEntry verboseLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Verbose);
			consoleSubLogger->Log(verboseLogEntry);
			Assert::AreEqual(verboseLogEntry.ToString() + '\n', verboseStream.str());

			std::ostringstream debugStream;
			std::cout.rdbuf(debugStream.rdbuf());
			const PonyEngine::Debug::Log::LogEntry debugLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Debug);
			consoleSubLogger->Log(debugLogEntry);
			Assert::AreEqual(debugLogEntry.ToString() + '\n', debugStream.str());

			std::ostringstream infoStream;
			std::cout.rdbuf(infoStream.rdbuf());
			const PonyEngine::Debug::Log::LogEntry infoLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Info);
			consoleSubLogger->Log(infoLogEntry);
			Assert::AreEqual(infoLogEntry.ToString() + '\n', infoStream.str());

			std::ostringstream warningStream;
			std::streambuf* const clogBuffer = std::clog.rdbuf(warningStream.rdbuf());
			const PonyEngine::Debug::Log::LogEntry warningLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Warning);
			consoleSubLogger->Log(warningLogEntry);
			Assert::AreEqual(warningLogEntry.ToString() + '\n', warningStream.str());

			std::ostringstream errorStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());
			const PonyEngine::Debug::Log::LogEntry errorLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Error);
			consoleSubLogger->Log(errorLogEntry);
			Assert::AreEqual(errorLogEntry.ToString() + '\n', errorStream.str());

			std::ostringstream exceptionStream;
			std::cerr.rdbuf(exceptionStream.rdbuf());
			const PonyEngine::Debug::Log::LogEntry exceptionLogEntry(message, &exception, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Exception);
			consoleSubLogger->Log(exceptionLogEntry);
			Assert::AreEqual(exceptionLogEntry.ToString() + '\n', exceptionStream.str());

			std::cout.rdbuf(coutBuffer);
			std::clog.rdbuf(clogBuffer);
			std::cerr.rdbuf(cerrBuffer);
;			PonyEngine::Debug::Log::DestroyConsoleSubLogger(consoleSubLogger);
		}
	};
}
