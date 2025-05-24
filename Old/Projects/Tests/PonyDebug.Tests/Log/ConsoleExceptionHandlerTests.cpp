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
#include <iostream>

import PonyDebug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(ConsoleExceptionHandlerTests)
	{
		TEST_METHOD(ExecuteTest)
		{
			const auto exceptionStream = std::ostringstream();
			std::streambuf* const cerrBuffer = std::cerr.rdbuf(exceptionStream.rdbuf());
			const auto exception = std::exception("Exception!");
			PonyDebug::Log::ConsoleExceptionHandler()(exception);
			std::string expectedString = PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what(), std::chrono::system_clock::now());
			std::string gottenString = exceptionStream.str();

			std::string expectedTypeSubstring = expectedString.substr(expectedString.find('['), expectedString.find(']') - expectedString.find('['));
			std::string gottenTypeSubstring = gottenString.substr(gottenString.find('['), gottenString.find(']') - gottenString.find('['));
			Assert::AreEqual(expectedTypeSubstring, gottenTypeSubstring);

			std::string expectedMessageSubstring = expectedString.substr(expectedString.rfind(']'), expectedString.size() - expectedString.rfind(']'));
			std::string gottenMessageSubstring = gottenString.substr(gottenString.rfind(']'), gottenString.size() - gottenString.rfind(']'));
			Assert::AreEqual(expectedMessageSubstring, gottenMessageSubstring);

			std::cerr.rdbuf(cerrBuffer);
		}
	};
}
