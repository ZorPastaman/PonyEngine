/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Log.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(OutputDebugStringSubLoggerTests)
	{
		TEST_METHOD(CreateTest)
		{
			const PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyEngine::Log::CreateOutputDebugStringSubLogger();
			Assert::IsNotNull(outputDebugStringSubLogger.subLogger.get());
		}

		TEST_METHOD(GetNameTest)
		{
			const PonyEngine::Log::OutputDebugStringSubLoggerData outputDebugStringSubLogger = PonyEngine::Log::CreateOutputDebugStringSubLogger();
			Assert::AreEqual("PonyEngine::Log::OutputDebugStringSubLogger", outputDebugStringSubLogger.subLogger->Name());
		}

		// Skip log test 'cause it's too complicated to do it here. And manual tests of it are easy.
	};
}
