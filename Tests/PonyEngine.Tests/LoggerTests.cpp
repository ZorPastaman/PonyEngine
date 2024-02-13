/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <chrono>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <fstream>
#include <type_traits>

#include "CppUnitTest.h"

import PonyEngine.Core;
import PonyEngine.Debug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PonyEngineTests
{
	TEST_CLASS(LoggerTests)
	{
		class TestSubLogger : public PonyEngine::Debug::Log::ISubLogger
		{
		public:
			std::string* expectedMessage = nullptr;
			std::exception* expectedException = nullptr;
			std::chrono::time_point<std::chrono::system_clock> expectedStartPoint{};
			std::size_t expectedFrame = 0;
			PonyEngine::Debug::Log::LogType expectedLogType = PonyEngine::Debug::Log::LogType::None;

			bool checkData = false;

			bool* onLog = nullptr;

			virtual ~TestSubLogger() = default;

			virtual void Log(const PonyEngine::Debug::Log::LogEntry& logEntry) noexcept override
			{
				if (checkData)
				{
					Assert::AreEqual(*expectedMessage, logEntry.message);
					Assert::AreEqual(reinterpret_cast<std::uintptr_t>(expectedException), reinterpret_cast<std::uintptr_t>(logEntry.exception));
					Assert::IsTrue(expectedStartPoint <= logEntry.timePoint && logEntry.timePoint <= std::chrono::system_clock::now());
					Assert::AreEqual(expectedFrame, logEntry.frameCount);
					Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logEntry.logType));
				}

				if (onLog != nullptr)
				{
					*onLog = true;
				}
			}
		};

		std::string logFilePath = "Test.log";

		bool HasText(std::ifstream& file, std::string& text)
		{
			std::string line;

			while (std::getline(file, line))
			{
				if (line.find(text) != std::string::npos)
				{
					return true;
				}
			}

			return false;
		}

		TEST_METHOD(LogFileTest)
		{
			std::string logText = "It's a test log!";

			PonyEngine::Core::EngineParams engineParamsNoLog;
			engineParamsNoLog.loggerParams.logFilePath = logFilePath;
			engineParamsNoLog.loggerParams.addLogFileSubLogger = false;
			auto engine = PonyEngine::Core::CreateEngine(engineParamsNoLog);
			engine->GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, logText);
			Assert::IsFalse(std::filesystem::exists(logFilePath));
			PonyEngine::Core::DestroyEngine(engine);

			PonyEngine::Core::EngineParams engineParamsWithLog;
			engineParamsWithLog.loggerParams.logFilePath = logFilePath;
			engine = PonyEngine::Core::CreateEngine(engineParamsWithLog);
			engine->GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, logText);
			Assert::IsTrue(std::filesystem::exists(logFilePath));
			std::ifstream logFile(logFilePath);
			Assert::IsTrue(HasText(logFile, logText));
			logFile.close();

			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(AddRemoveLoggerTest)
		{
			bool onLog = false;
			TestSubLogger testSubLogger;
			testSubLogger.onLog = &onLog;

			auto engine = PonyEngine::Core::CreateEngine();
			engine->GetLogger().AddSubLogger(&testSubLogger);
			engine->GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "Any string");
			Assert::IsTrue(onLog);
			onLog = false;
			engine->GetLogger().RemoveSubLogger(&testSubLogger);
			engine->GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "Any string");
			Assert::IsFalse(onLog);
			PonyEngine::Core::DestroyEngine(engine);

			PonyEngine::Core::EngineParams engineParams;
			engineParams.loggerParams.subLoggers.push_back(&testSubLogger);
			engine = PonyEngine::Core::CreateEngine(engineParams);
			engine->GetLogger().Log(PonyEngine::Debug::Log::LogType::Info, "Any string");
			Assert::IsTrue(onLog);
			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD(SubLoggerTest)
		{
			bool onLog = false;
			TestSubLogger testSubLogger;
			testSubLogger.checkData = true;
			testSubLogger.onLog = &onLog;

			auto engine = PonyEngine::Core::CreateEngine();
			engine->GetLogger().AddSubLogger(&testSubLogger);

			std::string message = "Test log Verbose";
			auto logType = PonyEngine::Debug::Log::LogType::Verbose;
			testSubLogger.expectedMessage = &message;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedStartPoint = std::chrono::system_clock::now();
			testSubLogger.expectedFrame = engine->GetFrameCount();
			testSubLogger.expectedLogType = logType;
			engine->GetLogger().Log(logType, message);

			engine->Tick();
			message = "Test log Debug";
			logType = PonyEngine::Debug::Log::LogType::Debug;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedStartPoint = std::chrono::system_clock::now();
			testSubLogger.expectedFrame = engine->GetFrameCount();
			testSubLogger.expectedLogType = logType;
			engine->GetLogger().Log(logType, message);

			engine->Tick();
			message = "Test log Info";
			logType = PonyEngine::Debug::Log::LogType::Info;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedStartPoint = std::chrono::system_clock::now();
			testSubLogger.expectedFrame = engine->GetFrameCount();
			testSubLogger.expectedLogType = logType;
			engine->GetLogger().Log(logType, message);

			engine->Tick();
			message = "Test log Warning";
			logType = PonyEngine::Debug::Log::LogType::Warning;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedStartPoint = std::chrono::system_clock::now();
			testSubLogger.expectedFrame = engine->GetFrameCount();
			testSubLogger.expectedLogType = logType;
			engine->GetLogger().Log(logType, message);

			engine->Tick();
			message = "Test log Error";
			logType = PonyEngine::Debug::Log::LogType::Error;
			testSubLogger.expectedException = nullptr;
			testSubLogger.expectedStartPoint = std::chrono::system_clock::now();
			testSubLogger.expectedFrame = engine->GetFrameCount();
			testSubLogger.expectedLogType = logType;
			engine->GetLogger().Log(logType, message);

			engine->Tick();
			message = "Test log Exception";
			logType = PonyEngine::Debug::Log::LogType::Exception;
			std::exception e;
			testSubLogger.expectedException = &e;
			testSubLogger.expectedStartPoint = std::chrono::system_clock::now();
			testSubLogger.expectedFrame = engine->GetFrameCount();
			testSubLogger.expectedLogType = logType;
			engine->GetLogger().LogException(e, message);
			
			engine->GetLogger().RemoveSubLogger(&testSubLogger);

			PonyEngine::Core::DestroyEngine(engine);
		}

		TEST_METHOD_CLEANUP(LoggerCleanUp)
		{
			std::filesystem::remove(logFilePath);
		}
	};
}
