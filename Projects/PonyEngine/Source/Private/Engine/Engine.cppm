/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Engine;

import PonyEngine.IEngine;
import PonyEngine.EngineParams;
import PonyEngine.EngineFeatures;
import PonyEngine.LoggerOwnerKit;
import PonyEngine.Debug.Log.LogType;

namespace PonyEngine
{
	/// <summary>
	/// Pony Engine main class.
	/// </summary>
	export class Engine final : public IEngine
	{
	public:
		Engine(const EngineParams& params);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		virtual ~Engine();

		virtual size_t GetFrameCount() const noexcept override;

		virtual Debug::Log::ILogger* GetLogger() const noexcept override;

		virtual void Tick() override;

	private:
		const LoggerOwnerKit m_loggerKit;

		size_t m_frameCount;
	};

	Engine::Engine(const EngineParams& params) :
		m_frameCount{0},
		m_loggerKit{CreateLogger(params.loggerParams, this)}
	{
		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine created");
	}

	Engine::~Engine()
	{
		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine destructed");

		for (Debug::Log::ISubLogger* const subLogger : m_loggerKit.subLoggers)
		{
			m_loggerKit.logger->RemoveSubLogger(subLogger);
			delete subLogger;
		}

		delete m_loggerKit.logger;
	}

	size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	Debug::Log::ILogger* Engine::GetLogger() const noexcept
	{
		return m_loggerKit.logger;
	}

	void Engine::Tick()
	{
		++m_frameCount;
	}
}
