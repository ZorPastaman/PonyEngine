/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstdint>;
import <iostream>;
import <string>;

import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LogConsoleHelperTests)
	{
		TEST_METHOD(LogToConsoleTest)
		{
			auto message = "Message to check.";

			std::ostringstream verboseStream;
			std::streambuf* const coutBuffer = std::cout.rdbuf(verboseStream.rdbuf());
			PonyEngine::Log::LogToConsole(PonyEngine::Log::LogType::Verbose, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Verbose, message), verboseStream.str());

			std::ostringstream debugStream;
			std::cout.rdbuf(debugStream.rdbuf());
			PonyEngine::Log::LogToConsole(PonyEngine::Log::LogType::Debug, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Debug, message), debugStream.str());

			std::ostringstream infoStream;
			std::cout.rdbuf(infoStream.rdbuf());
			PonyEngine::Log::LogToConsole(PonyEngine::Log::LogType::Info, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Info, message), infoStream.str());

			std::ostringstream warningStream;
			std::streambuf* const clogBuffer = std::clog.rdbuf(warningStream.rdbuf());
			PonyEngine::Log::LogToConsole(PonyEngine::Log::LogType::Warning, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Warning, message), warningStream.str());

			std::ostringstream errorStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());
			PonyEngine::Log::LogToConsole(PonyEngine::Log::LogType::Error, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Error, message), errorStream.str());

			std::ostringstream exceptionStream;
			std::cerr.rdbuf(exceptionStream.rdbuf());
			PonyEngine::Log::LogToConsole(PonyEngine::Log::LogType::Exception, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, message), exceptionStream.str());

			std::cout.rdbuf(coutBuffer);
			std::clog.rdbuf(clogBuffer);
			std::cerr.rdbuf(cerrBuffer);
		}

		TEST_METHOD(LogExceptionToConsoleTest)
		{
			auto message = "Message to check.";
			auto exception = std::exception("Exception to check.");

			std::ostringstream exceptionStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(exceptionStream.rdbuf());
			PonyEngine::Log::LogExceptionToConsole(exception);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, exception.what()), exceptionStream.str());

			std::ostringstream exceptionWithMessageStream;
			std::cerr.rdbuf(exceptionWithMessageStream.rdbuf());
			PonyEngine::Log::LogExceptionToConsole(exception, message);
			Assert::AreEqual(PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, exception.what(), message), exceptionWithMessageStream.str());

			std::cerr.rdbuf(cerrBuffer);
		}

		TEST_METHOD(ChooseConsoleStreamTest)
		{
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cout), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Verbose)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cout), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Debug)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cout), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Info)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::clog), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Warning)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Error)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Exception)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::None)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::All)));
		}
	};
}
