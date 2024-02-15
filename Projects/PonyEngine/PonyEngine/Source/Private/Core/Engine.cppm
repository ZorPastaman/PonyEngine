/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <iostream>;
import <exception>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;

import :EngineFeatures;
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
		inline virtual std::size_t GetFrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual Debug::Log::ILogger& GetLogger() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual bool IsRunning() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual int GetExitCode() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual void Tick() override;

	private:
		const LoggerOwnerKit m_loggerKit; /// @brief Logger and sub-logger that are owned by the @p Engine.

		std::size_t m_frameCount; /// @brief Current frame.

		int m_exitCode;
		bool m_isRunning;
	};

	Engine::Engine(const EngineParams& params) :
		m_frameCount{0},
		m_isRunning{true},
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

	inline std::size_t Engine::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	inline Debug::Log::ILogger& Engine::GetLogger() const noexcept
	{
		return *m_loggerKit.logger;
	}

	inline bool Engine::IsRunning() const noexcept
	{
		return m_isRunning;
	}

	inline int Engine::GetExitCode() const noexcept
	{
		return m_exitCode;
	}

	void Engine::Tick()
	{
		++m_frameCount;
	}
}
