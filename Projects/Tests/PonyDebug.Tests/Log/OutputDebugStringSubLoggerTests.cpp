/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyDebug.Log.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(OutputDebugStringSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			const PonyDebug::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyDebug::Log::CreateOutputDebugStringSubLogger(PonyDebug::Log::OutputDebugStringSubLoggerParams());
			Assert::IsNotNull(outputDebugStringSubLogger.subLogger.get());
		}

		// Skip log test 'cause it's too complicated to do it here. And manual tests of it are easy.
	};
}
