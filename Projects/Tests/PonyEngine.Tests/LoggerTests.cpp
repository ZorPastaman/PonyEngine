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
import PonyEngine.Core.Implementation;
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

		TEST_METHOD(LogEntryTest)
		{
			std::string message = "Test";
			std::exception e("Some exception");
			auto timePoint = std::chrono::system_clock::now();
			std::size_t frame = 10;
			auto logType = PonyEngine::Debug::Log::LogType::Info;

			auto logEntry0 = PonyEngine::Debug::Log::LogEntry(message, nullptr, timePoint, frame, logType);
			std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {}.", PonyEngine::Debug::Log::ToString(logType, false), timePoint, frame, message);
			Assert::AreEqual(expected, logEntry0.ToString());
			std::ostringstream oss;
			oss << logEntry0;
			Assert::AreEqual(expected, oss.str());

			logType = PonyEngine::Debug::Log::LogType::Exception;

			std::string empty = "";
			auto logEntry1 = PonyEngine::Debug::Log::LogEntry(empty, &e, timePoint, frame, logType);
			expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {}.", PonyEngine::Debug::Log::ToString(logType, false), timePoint, frame, e.what());
			Assert::AreEqual(expected, logEntry1.ToString());
			oss = std::ostringstream();
			oss << logEntry1;
			Assert::AreEqual(expected, oss.str());

			auto logEntry2 = PonyEngine::Debug::Log::LogEntry(message, &e, timePoint, frame, logType);
			expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}.", PonyEngine::Debug::Log::ToString(logType, false), timePoint, frame, e.what(), message);
			Assert::AreEqual(expected, logEntry2.ToString());
			oss = std::ostringstream();
			oss << logEntry2;
			Assert::AreEqual(expected, oss.str());
		}

		TEST_METHOD(LogTypeTest)
		{
			auto logType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Warning | PonyEngine::Debug::Log::LogType::Error;
			std::string expected = "Debug | Warning | Error";
			Assert::AreEqual(expected, PonyEngine::Debug::Log::ToString(logType));
			std::ostringstream oss;
			oss << logType;
			Assert::AreNotEqual(expected, oss.str());

			expected += " (26)";
			Assert::AreEqual(expected, PonyEngine::Debug::Log::ToString(logType, true));
			Assert::AreEqual(expected, oss.str());

			auto expectedLogType = PonyEngine::Debug::Log::LogType::Verbose | PonyEngine::Debug::Log::LogType::Info | PonyEngine::Debug::Log::LogType::Exception;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(~logType));

			auto otherLogType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Info | PonyEngine::Debug::Log::LogType::Warning;
			expectedLogType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Warning;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logType & otherLogType));

			otherLogType = PonyEngine::Debug::Log::LogType::Info;
			expectedLogType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Info | PonyEngine::Debug::Log::LogType::Warning | PonyEngine::Debug::Log::LogType::Error;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logType | otherLogType));

			otherLogType = PonyEngine::Debug::Log::LogType::Debug | PonyEngine::Debug::Log::LogType::Info | PonyEngine::Debug::Log::LogType::Warning;
			expectedLogType = PonyEngine::Debug::Log::LogType::Info | PonyEngine::Debug::Log::LogType::Error;
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(expectedLogType), static_cast<std::underlying_type_t<PonyEngine::Debug::Log::LogType>>(logType ^ otherLogType));
		}

		TEST_METHOD_CLEANUP(LoggerCleanUp)
		{
			std::filesystem::remove(logFilePath);
		}
	};
}
