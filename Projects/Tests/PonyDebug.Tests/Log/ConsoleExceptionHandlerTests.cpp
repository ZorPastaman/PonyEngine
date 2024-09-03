/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

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
			Assert::AreEqual(PonyDebug::Log::LogFormat(PonyDebug::Log::LogType::Exception, exception.what()), exceptionStream.str());

			std::cerr.rdbuf(cerrBuffer);
		}
	};
}
