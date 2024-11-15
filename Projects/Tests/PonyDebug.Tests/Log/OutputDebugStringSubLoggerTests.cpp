/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <string_view>

import PonyDebug.Log.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(OutputDebugStringSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			const PonyDebug::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyDebug::Log::CreateOutputDebugStringSubLogger(PonyDebug::Log::OutputDebugStringSubLoggerParams());
			Assert::IsNotNull(outputDebugStringSubLogger.subLogger.Get());
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyDebug::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyDebug::Log::CreateOutputDebugStringSubLogger(PonyDebug::Log::OutputDebugStringSubLoggerParams());
			Assert::AreEqual(std::string_view("PonyDebug::Log::OutputDebugStringSubLogger"), outputDebugStringSubLogger.subLogger->Name());
		}

		// Skip log test 'cause it's too complicated to do it here. And manual tests of it are easy.
	};
}
