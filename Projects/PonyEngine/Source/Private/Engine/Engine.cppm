/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Engine;

import <cstddef>;
import <string>;

import PonyEngine.IEngine;
import PonyEngine.EngineParams;
import PonyEngine.EngineFeatures;
import PonyEngine.Debug.ILoggerView;
import PonyEngine.Debug.ILogger;
import PonyEngine.LoggerOwnerKit;

namespace PonyEngine
{
	/// <summary>
	/// Pony Engine main class.
	/// </summary>
	export class Engine final : public IEngine
	{
	public:
		Engine(const EngineParams& params) noexcept;
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		virtual ~Engine() noexcept;

		virtual size_t GetFrameCount() const noexcept override;

		virtual Debug::ILoggerView* GetLogger() const noexcept override;

		virtual void Tick() override;

	private:
		LoggerOwnerKit m_loggerKit;

		size_t m_frameCount;
	};

	Engine::Engine(const EngineParams& params) noexcept :
		m_frameCount(0)
	{
		m_loggerKit = CreateLogger(params, this);

		m_loggerKit.logger->Log("Engine created");
	}

	Engine::~Engine() noexcept
	{
		m_loggerKit.logger->Log("Engine destructed");

		for (Debug::ILoggerEntry* const loggerEntry : m_loggerKit.loggerEntries)
		{
			m_loggerKit.logger->RemoveLoggerEntry(loggerEntry);
			delete loggerEntry;
		}

		delete m_loggerKit.logger;
	}

	size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	Debug::ILoggerView* Engine::GetLogger() const noexcept
	{
		return m_loggerKit.logger;
	}

	void Engine::Tick()
	{
		++m_frameCount;
	}
}
