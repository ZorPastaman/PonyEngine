/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Engine.Core:Engine;

import std;

import PonyEngine.Application;
import PonyEngine.Core;
import PonyEngine.Engine.Ext;

import :EngineLogger;
import :ExitCodes;
import :SystemManager;

export namespace PonyEngine::Engine
{
	/// @brief Engine.
	class Engine final : public Core::IEngine, private IEngine
	{
	public:
		/// @brief Creates an engine.
		/// @param application Application context.
		/// @param systemFactories System factories. The order of the factories may be changed.
		[[nodiscard("Pure constructor")]]
		Engine(Application::IApplicationContext& application, std::span<ISystemFactory*> systemFactories);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual PonyEngine::Engine::IEngine& PublicEngine() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyEngine::Engine::IEngine& PublicEngine() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:
		/// @brief Engine context.
		class EngineContext final : public IEngineContext
		{
		public:
			/// @brief Creates an engine context.
			/// @param engine Engine.
			[[nodiscard("Pure constructor")]]
			explicit EngineContext(Engine& engine) noexcept;
			EngineContext(const EngineContext&) = delete;
			EngineContext(EngineContext&&) = delete;

			~EngineContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Application::IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Application::IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual ISystemManager& SystemManager() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const ISystemManager& SystemManager() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::uint64_t FrameCount() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override;
			[[nodiscard("Pure function")]]
			virtual int ExitCode() const noexcept override;
			virtual void Stop(int exitCode) noexcept override;

			EngineContext& operator =(const EngineContext&) = delete;
			EngineContext& operator =(EngineContext&&) = delete;

		private:
			Engine* engine; ///< Engine.
		};

		std::uint64_t frameCount; ///< Frame count.
		int exitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
		bool isTicking; ///< @a True if the engine is ticking now; @a false otherwise.

		Application::IApplicationContext* application; ///< Application.

		EngineContext engineContext; ///< Engine context.

		std::unique_ptr<EngineLogger> logger; ///< Engine logger.
		std::unique_ptr<SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Engine
{
	Engine::Engine(Application::IApplicationContext& application, const std::span<ISystemFactory*> systemFactories) :
		frameCount{0ULL},
		exitCode{ExitCodes::InitialExitCode},
		isRunning{true},
		isTicking{false},
		application{&application},
		engineContext(*this)
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Constructing engine logger.");
		logger = std::make_unique<EngineLogger>(engineContext);

		PONY_LOG(*logger, Log::LogType::Info, "Constructing system manager.");
		systemManager = std::make_unique<SystemManager>(engineContext, systemFactories);
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(*logger, Log::LogType::Info, "Releasing system manager.");
		systemManager.reset();

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Releasing logger.");
		logger.reset();
	}

	PonyEngine::Engine::IEngine& Engine::PublicEngine() noexcept
	{
		return *this;
	}

	const PonyEngine::Engine::IEngine& Engine::PublicEngine() const noexcept
	{
		return *this;
	}

	bool Engine::IsRunning() const noexcept
	{
		return isRunning;
	}

	int Engine::ExitCode() const noexcept
	{
		return exitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			this->exitCode = exitCode;
			isRunning = false;
			PONY_LOG(*logger, Log::LogType::Info, "Engine is stopped. Exit code: '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(*logger, Log::LogType::Verbose, "Engine is stopped when it's not running. Ignoring.");
		}
	}

	void Engine::Tick()
	{
		if (!isRunning) [[unlikely]]
		{
			throw std::logic_error("Engine is ticked when it's already been stopped.");
		}

		if (isTicking) [[unlikely]]
		{
			throw std::logic_error("Engine is ticked inside another tick.");
		}

		isTicking = true;

		PONY_LOG(*logger, Log::LogType::Verbose, "Ticking systems.");
		try
		{
			systemManager->Tick();
		}
		catch (...)
		{
			Stop(ExitCodes::TickException);
			isTicking = false;

			throw;
		}

		isTicking = false;
		++frameCount;
	}

	Engine::EngineContext::EngineContext(Engine& engine) noexcept :
		engine{&engine}
	{
	}

	Application::IApplicationContext& Engine::EngineContext::Application() noexcept
	{
		return *engine->application;
	}

	const Application::IApplicationContext& Engine::EngineContext::Application() const noexcept
	{
		return *engine->application;
	}

	Log::ILogger& Engine::EngineContext::Logger() noexcept
	{
		return *engine->logger;
	}

	const Log::ILogger& Engine::EngineContext::Logger() const noexcept
	{
		return *engine->logger;
	}

	ISystemManager& Engine::EngineContext::SystemManager() noexcept
	{
		return *engine->systemManager;
	}

	const ISystemManager& Engine::EngineContext::SystemManager() const noexcept
	{
		return *engine->systemManager;
	}

	std::uint64_t Engine::EngineContext::FrameCount() const noexcept
	{
		return engine->frameCount;
	}

	bool Engine::EngineContext::IsRunning() const noexcept
	{
		return engine->isRunning;
	}

	int Engine::EngineContext::ExitCode() const noexcept
	{
		return engine->exitCode;
	}

	void Engine::EngineContext::Stop(const int exitCode) noexcept
	{
		engine->Stop(exitCode);
	}
}
