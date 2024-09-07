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
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>

import PonyDebug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(FileSubLoggerTests)
	{
		std::filesystem::path testLogPath = "TestLog.log";

		TEST_METHOD(CreateTest)
		{
			const auto params = PonyDebug::Log::FileSubLoggerParams{.logPath = testLogPath};
			PonyDebug::Log::FileSubLoggerData fileSubLogger = PonyDebug::Log::CreateFileSubLogger(params);
			Assert::IsNotNull(fileSubLogger.subLogger.get());
			fileSubLogger.subLogger.reset();
			std::filesystem::remove(testLogPath);
		}

		TEST_METHOD(LogTest)
		{
			const auto params = PonyDebug::Log::FileSubLoggerParams{.logPath = testLogPath};
			PonyDebug::Log::FileSubLoggerData fileSubLogger = PonyDebug::Log::CreateFileSubLogger(params);
			const auto message = "Message!";
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(5691338));
			constexpr std::size_t frameCount = 84136;
			const auto infoLogEntry = PonyDebug::Log::LogEntry(message, nullptr, timePoint, frameCount, PonyDebug::Log::LogType::Info);
			fileSubLogger.subLogger->Log(infoLogEntry);
			fileSubLogger.subLogger.reset();

			std::ifstream logFile(testLogPath);
			std::string line;
			std::getline(logFile, line);
			Assert::AreEqual(infoLogEntry.ToString(), (line + '\n').c_str());
			logFile.close();

			std::filesystem::remove(testLogPath);
		}

		TEST_METHOD(GetNameTest)
		{
			const auto params = PonyDebug::Log::FileSubLoggerParams{.logPath = testLogPath};
			PonyDebug::Log::FileSubLoggerData fileSubLogger = PonyDebug::Log::CreateFileSubLogger(params);
			Assert::AreEqual("PonyDebug::Log::FileSubLogger", fileSubLogger.subLogger->Name());
			fileSubLogger.subLogger.reset();
			std::filesystem::remove(testLogPath);
		}
	};
}