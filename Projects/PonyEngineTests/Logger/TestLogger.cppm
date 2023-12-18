/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngineTests.TestLogger;

import <string>;
import <exception>;

import PonyEngine.IEngineView;
import PonyEngine.Debug.ILogger;
import PonyEngine.Debug.ILoggerEntryView;

namespace PonyEngineTests
{
	export class TestLogger : public PonyEngine::Debug::ILogger
	{
	public:
		TestLogger(PonyEngine::IEngineView* engine) noexcept;

		virtual ~TestLogger() noexcept = default;

		virtual void Log(const std::string& message) const noexcept;

		virtual void LogWarning(const std::string& message) const noexcept;

		virtual void LogError(const std::string& message) const noexcept;

		virtual void LogException(const std::exception& exception) const noexcept;

		virtual void AddLoggerEntry(PonyEngine::Debug::ILoggerEntryView* loggerEntry);

		virtual void RemoveLoggerEntry(PonyEngine::Debug::ILoggerEntryView* loggerEntry);

		PonyEngine::IEngineView* GetEngine() const noexcept;

	private:
		PonyEngine::IEngineView* m_engine;
	};

	TestLogger::TestLogger(PonyEngine::IEngineView* engine) noexcept :
		m_engine(engine)
	{
	}

	void TestLogger::Log(const std::string& message) const noexcept
	{
	}

	void TestLogger::LogWarning(const std::string& message) const noexcept
	{
	}

	void TestLogger::LogError(const std::string& message) const noexcept
	{
	}

	void TestLogger::LogException(const std::exception& exception) const noexcept
	{
	}

	void TestLogger::AddLoggerEntry(PonyEngine::Debug::ILoggerEntryView* loggerEntry)
	{
	}

	void TestLogger::RemoveLoggerEntry(PonyEngine::Debug::ILoggerEntryView* loggerEntry)
	{
	}

	PonyEngine::IEngineView* TestLogger::GetEngine() const noexcept
	{
		return m_engine;
	}
}
