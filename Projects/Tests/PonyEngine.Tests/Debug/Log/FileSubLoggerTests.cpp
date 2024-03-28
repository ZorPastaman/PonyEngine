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

import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Debug::Log
{
	TEST_CLASS(FileSubLoggerTests)
	{
		const std::filesystem::path m_testLogPath = "TestLog.log";

		TEST_METHOD(CreateTest)
		{
			PonyEngine::Debug::Log::ISubLogger* const fileSubLogger = PonyEngine::Debug::Log::CreateFileSubLogger(m_testLogPath);
			Assert::IsNotNull(fileSubLogger);
			PonyEngine::Debug::Log::DestroyFileSubLogger(fileSubLogger);
			std::filesystem::remove(m_testLogPath);
		}

		TEST_METHOD(GetNameTest)
		{
			PonyEngine::Debug::Log::ISubLogger* const fileSubLogger = PonyEngine::Debug::Log::CreateFileSubLogger(m_testLogPath);
			Assert::AreEqual("PonyEngine::Debug::Log::FileSubLogger", fileSubLogger->GetName());
			PonyEngine::Debug::Log::DestroyFileSubLogger(fileSubLogger);
			std::filesystem::remove(m_testLogPath);
		}

		TEST_METHOD(LogTest)
		{
			PonyEngine::Debug::Log::ISubLogger* const fileSubLogger = PonyEngine::Debug::Log::CreateFileSubLogger(m_testLogPath);
			const char* const message = "Message!";
			const std::chrono::time_point<std::chrono::system_clock> timePoint(std::chrono::seconds(5691338));
			const std::size_t frameCount = 84136;
			const PonyEngine::Debug::Log::LogEntry infoLogEntry(message, nullptr, timePoint, frameCount, PonyEngine::Debug::Log::LogType::Info);
			fileSubLogger->Log(infoLogEntry);
			PonyEngine::Debug::Log::DestroyFileSubLogger(fileSubLogger);

			std::ifstream logFile(m_testLogPath);
			std::string line;
			std::getline(logFile, line);
			Assert::AreEqual(infoLogEntry.ToString(), line);
			logFile.close();

			std::filesystem::remove(m_testLogPath);
		}
	};
}
