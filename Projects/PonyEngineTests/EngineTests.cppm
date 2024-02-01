/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.EntryPoint;
import PonyEngine.IEngine;
import PonyEngine.EngineParams;
import PonyEngine.Debug.ILoggerView;

import PonyEngineTests.TestLoggerFactory;
import PonyEngineTests.TestLoggerEntry;
import PonyEngineTests.TestLoggerEntryFactory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(EngineTests)
	{
	public:
		TEST_METHOD(TickFrameCount)
		{
			PonyEngine::IEngine* const engine = PonyEngine::CreateEngine();

			for (size_t i = 0; i < 1000; ++i)
			{
				// Before tick
				size_t expected = i;
				size_t actual = engine->GetFrameCount();
				Assert::AreEqual(expected, actual);

				// After tick
				engine->Tick();
				++expected;
				actual = engine->GetFrameCount();
				Assert::AreEqual(expected, actual);
			}

			delete engine;
		}

		TEST_METHOD(LoggerFactory)
		{
			TestLoggerFactory* const loggerFactory = new TestLoggerFactory();

			PonyEngine::EngineParams params;
			params.loggerParams.loggerFactory = loggerFactory;
			PonyEngine::IEngine* const engine = PonyEngine::CreateEngineWithParams(params);

			PonyEngine::Debug::ILoggerView* expected = loggerFactory->GetLogger();
			PonyEngine::Debug::ILoggerView* actual = engine->GetLogger();
			Assert::AreEqual(reinterpret_cast<uintptr_t>(expected), reinterpret_cast<uintptr_t>(actual));

			delete loggerFactory;
			delete engine;
		}

		TEST_METHOD(LoggerEntry)
		{
			bool log, warning, error, exception;
			log = warning = error = exception = false;
			TestLoggerEntry* const loggerEntry = new TestLoggerEntry(&log, &warning, &error, &exception);

			PonyEngine::EngineParams params;
			params.loggerParams.subLoggers.push_back(loggerEntry);
			PonyEngine::IEngine* const engine = PonyEngine::CreateEngineWithParams(params);

			log = warning = error = exception = false;

			engine->GetLogger()->Log("Log");
			Assert::IsTrue(log);

			engine->GetLogger()->LogWarning("Warning");
			Assert::IsTrue(warning);

			engine->GetLogger()->LogError("Error");
			Assert::IsTrue(error);

			std::exception except;
			engine->GetLogger()->LogException(except);
			Assert::IsTrue(exception);

			delete engine;
			delete loggerEntry;
		}

		TEST_METHOD(RuntimeLoggerEntry)
		{
			bool log, warning, error, exception;
			log = warning = error = exception = false;
			TestLoggerEntry* const loggerEntry = new TestLoggerEntry(&log, &warning, &error, &exception);

			PonyEngine::IEngine* const engine = PonyEngine::CreateEngine();
			engine->GetLogger()->AddLoggerEntry(loggerEntry);

			engine->GetLogger()->Log("Log");
			Assert::IsTrue(log);

			engine->GetLogger()->LogWarning("Warning");
			Assert::IsTrue(warning);

			engine->GetLogger()->LogError("Error");
			Assert::IsTrue(error);

			std::exception except;
			engine->GetLogger()->LogException(except);
			Assert::IsTrue(exception);

			log = warning = error = exception = false;
			engine->GetLogger()->RemoveLoggerEntry(loggerEntry);

			engine->GetLogger()->Log("Log");
			Assert::IsFalse(log);

			engine->GetLogger()->LogWarning("Warning");
			Assert::IsFalse(warning);

			engine->GetLogger()->LogError("Error");
			Assert::IsFalse(error);

			engine->GetLogger()->LogException(except);
			Assert::IsFalse(exception);

			delete engine;
			delete loggerEntry;
		}

		TEST_METHOD(EngineLoggerEntry)
		{
			bool log, warning, error, exception;
			log = warning = error = exception = false;
			TestLoggerEntryFactory* const loggerEntryFactory = new TestLoggerEntryFactory(&log, &warning, &error, &exception);

			PonyEngine::EngineParams params;
			params.loggerParams.subLoggerFactories.push_back(loggerEntryFactory);
			PonyEngine::IEngine* const engine = PonyEngine::CreateEngineWithParams(params);
			delete loggerEntryFactory;

			log = warning = error = exception = false;

			engine->GetLogger()->Log("Log");
			Assert::IsTrue(log);

			engine->GetLogger()->LogWarning("Warning");
			Assert::IsTrue(warning);

			engine->GetLogger()->LogError("Error");
			Assert::IsTrue(error);

			std::exception except;
			engine->GetLogger()->LogException(except);
			Assert::IsTrue(exception);

			delete engine;
		}
	};
}
