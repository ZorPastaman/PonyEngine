/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngineTests.TestLoggerEntry;

import PonyEngine.Debug.ILoggerEntry;

namespace PonyEngineTests
{
	export class TestLoggerEntry : public PonyEngine::Debug::ILoggerEntry
	{
	public:
		TestLoggerEntry(bool* logResult, bool* warningResult, bool* errorResult, bool* exceptionResult) noexcept;
		TestLoggerEntry(const TestLoggerEntry&) = delete;
		TestLoggerEntry(TestLoggerEntry&&) = delete;

		virtual ~TestLoggerEntry() = default;

		virtual void Log(const std::string& log) const noexcept override;

		virtual void LogWarning(const std::string& log) const noexcept override;

		virtual void LogError(const std::string& log) const noexcept override;

		virtual void LogException(const std::string& log, const std::exception& exception) const noexcept override;

	private:
		bool* m_logResult;
		bool* m_warningResult;
		bool* m_errorResult;
		bool* m_exceptionResult;
	};

	TestLoggerEntry::TestLoggerEntry(bool* logResult, bool* warningResult, bool* errorResult, bool* exceptionResult) noexcept :
		m_logResult(logResult),
		m_warningResult(warningResult),
		m_errorResult(errorResult),
		m_exceptionResult(exceptionResult)
	{
	}

	void TestLoggerEntry::Log(const std::string& log) const noexcept
	{
		*m_logResult = true;
	}

	void TestLoggerEntry::LogWarning(const std::string& log) const noexcept
	{
		*m_warningResult = true;
	}

	void TestLoggerEntry::LogError(const std::string& log) const noexcept
	{
		*m_errorResult = true;
	}

	void TestLoggerEntry::LogException(const std::string& log, const std::exception& exception) const noexcept
	{
		*m_exceptionResult = true;
	}
}
