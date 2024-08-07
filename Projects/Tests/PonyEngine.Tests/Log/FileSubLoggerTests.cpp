/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <chrono>;
import <cstddef>;
import <filesystem>;
import <fstream>;
import <string>;

import PonyEngine.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(FileSubLoggerTests)
	{
		std::filesystem::path testLogPath = "TestLog.log";

		TEST_METHOD(CreateTest)
		{
			PonyEngine::Log::FileSubLoggerUniquePtr fileSubLogger = PonyEngine::Log::CreateFileSubLogger(testLogPath);
			Assert::IsNotNull(fileSubLogger.get());
			fileSubLogger.reset();
			std::filesystem::remove(testLogPath);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Log::FileSubLoggerUniquePtr fileSubLogger = PonyEngine::Log::CreateFileSubLogger(testLogPath);
			Assert::AreEqual("PonyEngine::Log::FileSubLogger", fileSubLogger->Name());
			fileSubLogger.reset();
			std::filesystem::remove(testLogPath);
		}

		TEST_METHOD(LogTest)
		{
			PonyEngine::Log::FileSubLoggerUniquePtr fileSubLogger = PonyEngine::Log::CreateFileSubLogger(testLogPath);
			const auto message = "Message!";
			constexpr auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(5691338));
			constexpr std::size_t frameCount = 84136;
			const auto infoLogEntry = PonyEngine::Log::LogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Info);
			fileSubLogger->Log(infoLogEntry);
			fileSubLogger.reset();

			std::ifstream logFile(testLogPath);
			std::string line;
			std::getline(logFile, line);
			Assert::AreEqual(infoLogEntry.ToString(), (line + '\n').c_str());
			logFile.close();

			std::filesystem::remove(testLogPath);
		}
	};
}
