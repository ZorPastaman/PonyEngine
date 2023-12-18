/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngineTests.TestLoggerEntryFactory;

import PonyEngine.Factories.IEngineFeatureFactory;
import PonyEngine.IEngineView;
import PonyEngine.Debug.ILoggerEntry;

import PonyEngineTests.TestLoggerEntry;

namespace PonyEngineTests
{
	export class TestLoggerEntryFactory : public PonyEngine::Factories::IEngineFeatureFactory<PonyEngine::Debug::ILoggerEntry>
	{
	public:
		TestLoggerEntryFactory(bool* log, bool* warning, bool* error, bool* exception) noexcept;
		TestLoggerEntryFactory(const TestLoggerEntryFactory&) = delete;
		TestLoggerEntryFactory(TestLoggerEntryFactory&&) = delete;

		virtual ~TestLoggerEntryFactory() noexcept = default;

		virtual PonyEngine::Debug::ILoggerEntry* Create(PonyEngine::IEngineView* engine) override;

	private:
		bool* m_log;
		bool* m_warning;
		bool* m_error;
		bool* m_exception;
	};

	TestLoggerEntryFactory::TestLoggerEntryFactory(bool* log, bool* warning, bool* error, bool* exception) noexcept :
		m_log(log),
		m_warning(warning),
		m_error(error),
		m_exception(exception)
	{
	}
	PonyEngine::Debug::ILoggerEntry* TestLoggerEntryFactory::Create(PonyEngine::IEngineView* engine)
	{
		return new TestLoggerEntry(m_log, m_warning, m_error, m_exception);
	}
}
