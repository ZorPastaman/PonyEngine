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

import PonyEngine.Log;
import PonyEngine.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(FileSubLoggerTests)
	{
		const std::filesystem::path testLogPath = "TestLog.log";

		TEST_METHOD(CreateTest)
		{
			PonyEngine::Log::ISubLogger* const fileSubLogger = PonyEngine::Log::CreateFileSubLogger(testLogPath);
			Assert::IsNotNull(fileSubLogger);
			PonyEngine::Log::DestroyFileSubLogger(fileSubLogger);
			std::filesystem::remove(testLogPath);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Log::ISubLogger* const fileSubLogger = PonyEngine::Log::CreateFileSubLogger(testLogPath);
			Assert::AreEqual("PonyEngine::Log::FileSubLogger", fileSubLogger->GetName());
			PonyEngine::Log::DestroyFileSubLogger(fileSubLogger);
			std::filesystem::remove(testLogPath);
		}

		TEST_METHOD(LogTest)
		{
			PonyEngine::Log::ISubLogger* const fileSubLogger = PonyEngine::Log::CreateFileSubLogger(testLogPath);
			const char* const message = "Message!";
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(5691338));
			const std::size_t frameCount = 84136;
			const PonyEngine::Log::LogEntry infoLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Log::LogType::Info);
			fileSubLogger->Log(infoLogEntry);
			PonyEngine::Log::DestroyFileSubLogger(fileSubLogger);

			std::ifstream logFile(testLogPath);
			std::string line;
			std::getline(logFile, line);
			Assert::AreEqual(infoLogEntry.ToString(), line);
			logFile.close();

			std::filesystem::remove(testLogPath);
		}
	};
}
