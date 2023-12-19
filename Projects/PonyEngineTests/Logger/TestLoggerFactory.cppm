/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngineTests.TestLoggerFactory;

import PonyEngine.Factories.IEngineFeatureFactory;
import PonyEngine.Debug.ILogger;

import PonyEngineTests.TestLogger;

namespace PonyEngineTests
{
	export class TestLoggerFactory : public PonyEngine::Factories::IEngineFeatureFactory<PonyEngine::Debug::ILogger>
	{
	public:
		TestLoggerFactory() noexcept = default;
		TestLoggerFactory(const TestLoggerFactory&) = delete;
		TestLoggerFactory(TestLoggerFactory&&) = delete;

		virtual ~TestLoggerFactory() noexcept = default;

		virtual PonyEngine::Debug::ILogger* Create(PonyEngine::IEngineView* engine) override;

		TestLogger* GetLogger() const noexcept;
	private:
		TestLogger* m_logger;
	};

	PonyEngine::Debug::ILogger* TestLoggerFactory::Create(PonyEngine::IEngineView* engine)
	{
		return m_logger = new TestLogger(engine);
	}

	TestLogger* TestLoggerFactory::GetLogger() const noexcept
	{
		return m_logger;
	}
}
