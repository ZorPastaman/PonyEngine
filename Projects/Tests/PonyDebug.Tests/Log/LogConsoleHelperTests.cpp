/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#ifndef PONY_LOG_VERBOSE
#define PONY_LOG_VERBOSE
#endif
#ifndef PONY_LOG_DEBUG
#define PONY_LOG_DEBUG
#endif
#ifndef PONY_LOG_INFO
#define PONY_LOG_INFO
#endif
#ifndef PONY_LOG_WARNING
#define PONY_LOG_WARNING
#endif
#ifndef PONY_LOG_ERROR
#define PONY_LOG_ERROR
#endif
#ifndef PONY_LOG_EXCEPTION
#define PONY_LOG_EXCEPTION
#endif
#ifndef PONY_CONSOLE_LOG
#define PONY_CONSOLE_LOG
#endif
#include "PonyDebug/Log/Log.h"

#include <cstdint>
#include <format>
#include <iostream>
#include <string>

import PonyDebug.Log;

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
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Verbose, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Verbose, message), verboseStream.str());

			std::ostringstream verboseMacroStream;
			std::cout.rdbuf(verboseMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Verbose, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Verbose, message), verboseMacroStream.str());

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			std::ostringstream verboseFormatStream;
			std::cout.rdbuf(verboseFormatStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Verbose, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Verbose, std::format(format, formatArg).c_str()), verboseFormatStream.str());

			std::ostringstream verboseFormatMacroStream;
			std::cout.rdbuf(verboseFormatMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Verbose, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Verbose, std::format(format, formatArg).c_str()), verboseFormatMacroStream.str());

			std::ostringstream debugStream;
			std::cout.rdbuf(debugStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Debug, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Debug, message), debugStream.str());

			std::ostringstream debugMacroStream;
			std::cout.rdbuf(debugMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Debug, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Debug, message), debugMacroStream.str());

			std::ostringstream debugFormatStream;
			std::cout.rdbuf(debugFormatStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Debug, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Debug, std::format(format, formatArg).c_str()), debugFormatStream.str());

			std::ostringstream debugFormatMacroStream;
			std::cout.rdbuf(debugFormatMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Debug, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Debug, std::format(format, formatArg).c_str()), debugFormatMacroStream.str());

			std::ostringstream infoStream;
			std::cout.rdbuf(infoStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Info, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Info, message), infoStream.str());

			std::ostringstream infoMacroStream;
			std::cout.rdbuf(infoMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Info, message), infoMacroStream.str());

			std::ostringstream infoFormatStream;
			std::cout.rdbuf(infoFormatStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Info, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Info, std::format(format, formatArg).c_str()), infoFormatStream.str());

			std::ostringstream infoFormatMacroStream;
			std::cout.rdbuf(infoFormatMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Info, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Info, std::format(format, formatArg).c_str()), infoFormatMacroStream.str());

			std::ostringstream warningStream;
			std::streambuf* const clogBuffer = std::clog.rdbuf(warningStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Warning, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Warning, message), warningStream.str());

			std::ostringstream warningMacroStream;
			std::clog.rdbuf(warningMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Warning, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Warning, message), warningMacroStream.str());

			std::ostringstream warningFormatStream;
			std::clog.rdbuf(warningFormatStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Warning, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Warning, std::format(format, formatArg).c_str()), warningFormatStream.str());

			std::ostringstream warningFormatMacroStream;
			std::clog.rdbuf(warningFormatMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Warning, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Warning, std::format(format, formatArg).c_str()), warningFormatMacroStream.str());

			std::ostringstream errorStream;
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Error, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Error, message), errorStream.str());

			std::ostringstream errorMacroStream;
			std::cerr.rdbuf(errorMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Error, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Error, message), errorMacroStream.str());

			std::ostringstream errorFormatStream;
			std::cerr.rdbuf(errorFormatStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Error, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Error, std::format(format, formatArg).c_str()), errorFormatStream.str());

			std::ostringstream errorFormatMacroStream;
			std::cerr.rdbuf(errorFormatMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Error, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Error, std::format(format, formatArg).c_str()), errorFormatMacroStream.str());

			std::ostringstream exceptionStream;
			std::cerr.rdbuf(exceptionStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Exception, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, message), exceptionStream.str());

			std::ostringstream exceptionMacroStream;
			std::cerr.rdbuf(exceptionMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Exception, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, message), exceptionMacroStream.str());

			std::ostringstream exceptionFormatStream;
			std::cerr.rdbuf(exceptionFormatStream.rdbuf());
			PonyDebug::Log::LogToConsole(PonyDebug::Log::LogType::Exception, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, std::format(format, formatArg).c_str()), exceptionFormatStream.str());

			std::ostringstream exceptionFormatMacroStream;
			std::cerr.rdbuf(exceptionFormatMacroStream.rdbuf());
			PONY_CONSOLE(PonyDebug::Log::LogType::Exception, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, std::format(format, formatArg).c_str()), exceptionFormatMacroStream.str());

			std::ostringstream infoIfMacroStream;
			std::cout.rdbuf(infoIfMacroStream.rdbuf());
			PONY_CONSOLE_IF(true, PonyDebug::Log::LogType::Info, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Info, message), infoIfMacroStream.str());

			std::ostringstream infoIfFalseMacroStream;
			std::cout.rdbuf(infoIfFalseMacroStream.rdbuf());
			PONY_CONSOLE_IF(false, PonyDebug::Log::LogType::Info, message);
			Assert::AreEqual("", infoIfFalseMacroStream.str().c_str());

			std::ostringstream infoIfFormatMacroStream;
			std::cout.rdbuf(infoIfFormatMacroStream.rdbuf());
			PONY_CONSOLE_IF(true, PonyDebug::Log::LogType::Info, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Info, std::format(format, formatArg).c_str()), infoIfFormatMacroStream.str());

			std::ostringstream infoIfFalseFormatMacroStream;
			std::cout.rdbuf(infoIfFalseFormatMacroStream.rdbuf());
			PONY_CONSOLE_IF(false, PonyDebug::Log::LogType::Info, format, formatArg);
			Assert::AreEqual("", infoIfFalseFormatMacroStream.str().c_str());

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
			PonyDebug::Log::LogExceptionToConsole(exception);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what()), exceptionStream.str());

			std::ostringstream exceptionMacroStream;
			std::cerr.rdbuf(exceptionMacroStream.rdbuf());
			PONY_CONSOLE_E_S(exception);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what()), exceptionMacroStream.str());

			std::ostringstream exceptionWithMessageStream;
			std::cerr.rdbuf(exceptionWithMessageStream.rdbuf());
			PonyDebug::Log::LogExceptionToConsole(exception, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), message), exceptionWithMessageStream.str());

			std::ostringstream exceptionWithMessageMacroStream;
			std::cerr.rdbuf(exceptionWithMessageMacroStream.rdbuf());
			PONY_CONSOLE_E(exception, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), message), exceptionWithMessageMacroStream.str());

			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			std::ostringstream exceptionWithFormatStream;
			std::cerr.rdbuf(exceptionWithFormatStream.rdbuf());
			PonyDebug::Log::LogExceptionToConsole(exception, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), std::format(format, formatArg).c_str()), exceptionWithFormatStream.str());

			std::ostringstream exceptionWithFormatMacroStream;
			std::cerr.rdbuf(exceptionWithFormatMacroStream.rdbuf());
			PONY_CONSOLE_E(exception, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), std::format(format, formatArg).c_str()), exceptionWithFormatMacroStream.str());

			std::ostringstream exceptionIfMacroStream;
			std::cerr.rdbuf(exceptionIfMacroStream.rdbuf());
			PONY_CONSOLE_E_S_IF(true, exception);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what()), exceptionIfMacroStream.str());

			std::ostringstream exceptionIfFalseMacroStream;
			std::cerr.rdbuf(exceptionIfFalseMacroStream.rdbuf());
			PONY_CONSOLE_E_S_IF(false, exception);
			Assert::AreEqual("", exceptionIfFalseMacroStream.str().c_str());

			std::ostringstream exceptionIfWithMessageMacroStream;
			std::cerr.rdbuf(exceptionIfWithMessageMacroStream.rdbuf());
			PONY_CONSOLE_E_IF(true, exception, message);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), message), exceptionIfWithMessageMacroStream.str());

			std::ostringstream exceptionIfFalseWithMessageMacroStream;
			std::cerr.rdbuf(exceptionIfFalseWithMessageMacroStream.rdbuf());
			PONY_CONSOLE_E_IF(false, exception, message);
			Assert::AreEqual("", exceptionIfFalseWithMessageMacroStream.str().c_str());

			std::ostringstream exceptionIfWithFormatMacroStream;
			std::cerr.rdbuf(exceptionIfWithFormatMacroStream.rdbuf());
			PONY_CONSOLE_E_IF(true, exception, format, formatArg);
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), std::format(format, formatArg).c_str()), exceptionIfWithFormatMacroStream.str());

			std::ostringstream exceptionIfFalseWithFormatMacroStream;
			std::cerr.rdbuf(exceptionIfFalseWithFormatMacroStream.rdbuf());
			PONY_CONSOLE_E_IF(false, exception, format, formatArg);
			Assert::AreEqual("", exceptionIfFalseWithFormatMacroStream.str().c_str());

			std::cerr.rdbuf(cerrBuffer);
		}

		TEST_METHOD(ChooseConsoleStreamTest)
		{
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cout), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::Verbose)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cout), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::Debug)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cout), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::Info)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::clog), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::Warning)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::Error)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::Exception)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::None)));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&std::cerr), reinterpret_cast<std::uintptr_t>(&PonyDebug::Log::ChooseConsoleStream(PonyDebug::Log::LogType::All)));
		}

		TEST_METHOD(SafeFormatTest)
		{
			const auto format = "Format {}.";
			const auto formatArg = "Format arg";
			Assert::AreEqual(std::format(format, formatArg), PonyDebug::Log::SafeFormat(format, formatArg));
		}
	};
}
