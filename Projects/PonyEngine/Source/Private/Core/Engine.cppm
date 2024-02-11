/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:Engine;

import <cstddef>;
import <iostream>;
import <exception>;

import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Logger;

import :EngineFeatures;
import :EngineParams;
import :IEngine;
import :LoggerOwnerKit;

namespace PonyEngine::Core
{
	/// @brief Pony Engine main class.
	export class Engine final : public IEngine
	{
	public:
		/// @brief Creates an @p Engine with the @p params.
		/// @param params Engine parameters.
		[[nodiscard("Pure constructor")]]
		Engine(const EngineParams& params);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		virtual ~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Debug::Log::ILogger* GetLogger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual void Tick() override;

	private:
		const LoggerOwnerKit m_loggerKit; /// @brief Logger and sub-logger that are owned by the @p Engine.

		std::size_t m_frameCount; /// @brief Current frame.
	};

	Engine::Engine(const EngineParams& params) :
		m_frameCount{0},
		m_loggerKit(CreateLogger(params.loggerParams, *this))
	{
		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine created");
	}

	Engine::~Engine() noexcept
	{
		m_loggerKit.logger->Log(Debug::Log::LogType::Info, "Engine destructed");

		for (Debug::Log::ISubLogger* const subLogger : m_loggerKit.subLoggers)
		{
			try
			{
				m_loggerKit.logger->RemoveSubLogger(subLogger);
				delete subLogger;
			}
			catch (std::exception& e)
			{
				std::cerr << "Exception on removing sub logger: " << e.what() << std::endl;
			}
		}

		delete m_loggerKit.logger;
	}

	std::size_t Engine::GetFrameCount() const noexcept
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
