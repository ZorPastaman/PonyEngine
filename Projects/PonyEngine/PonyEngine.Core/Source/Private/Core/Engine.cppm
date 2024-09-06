/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <memory>;
import <stdexcept>;

import PonyBase.Core;

import PonyDebug.Log;

import PonyEngine.Core.Factory;

import :EngineLogger;
import :SystemManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class Engine final : public IEngine, public ITickableEngine
	{
	public:
		/// @brief Creates an @p Engine.
		/// @param application Application.
		/// @param systemFactories System factories.
		[[nodiscard("Pure constructor")]]
		Engine(IApplication& application, const SystemFactoriesContainer& systemFactories);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::size_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode = static_cast<int>(PonyBase::Core::ExitCodes::Success)) noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Core::Engine"; ///< Class name.

	private:
		void BeginTick();
		void EndTick() noexcept;

		void TickSystemManager();

		/// @brief Creates an engine logger.
		/// @return Created engine logger.
		[[nodiscard("Pure function")]]
		std::unique_ptr<EngineLogger> CreateEngineLogger();

		/// @brief Creates a system manager.
		/// @param systemFactories Engine parameters.
		/// @return Created system manager.
		[[nodiscard("Pure function")]]
		std::unique_ptr<Core::SystemManager> CreateSystemManager(const SystemFactoriesContainer& systemFactories);

		std::size_t frameCount; ///< Frame count.
		int engineExitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
		bool isTicking; ///< @a True if the engine is ticking now; @a false otherwise.

		IApplication* application; ///< Application

		std::unique_ptr<EngineLogger> engineLogger; ///< Engine logger.
		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Core
{
	Engine::Engine(IApplication& application, const SystemFactoriesContainer& systemFactories) :
		frameCount{0},
		isRunning{true},
		isTicking{false},
		application{&application},
		engineLogger{CreateEngineLogger()},
		systemManager{CreateSystemManager(systemFactories)}
	{
		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Begin system manager.");
			systemManager->Begin();
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager begun.");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On beginning system manager.");

			throw;
		}

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Engine created in '{}' application.", application.Name());
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "End system manager.");
		systemManager->End();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager ended.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy system manager.");
		systemManager.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager destroyed.");
	}

	std::size_t Engine::FrameCount() const noexcept
	{
		return frameCount;
	}

	PonyDebug::Log::ILogger& Engine::Logger() const noexcept
	{
		return *engineLogger;
	}

	ISystemManager& Engine::SystemManager() const noexcept
	{
		return *systemManager;
	}

	bool Engine::IsRunning() const noexcept
	{
		return isRunning;
	}

	int Engine::ExitCode() const noexcept
	{
		PONY_LOG_IF(isRunning, Logger(), PonyDebug::Log::LogType::Warning, "Tried to get exit code when engine is still running.");

		return engineExitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			engineExitCode = exitCode;
			isRunning = false;
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Engine stopped with exit code '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Tried to stop already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		BeginTick();

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Tick system manager.");
		TickSystemManager();

		EndTick();
	}

	const char* Engine::Name() const noexcept
	{
		return StaticName;
	}

	void Engine::BeginTick()
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
	}

	void Engine::EndTick() noexcept
	{
		++frameCount;
		isTicking = false;
	}

	void Engine::TickSystemManager()
	{
		try
		{
			systemManager->Tick();
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On ticking system manager.");
			if (IsRunning())
			{
				Stop(static_cast<int>(PonyBase::Core::ExitCodes::SystemManagerTickException));
			}

			throw;
		}
	}

	std::unique_ptr<EngineLogger> Engine::CreateEngineLogger()
	{
		try
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create engine logger.");
			const auto logger = new EngineLogger(*this, application->Logger());
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Engine logger created.");

			return std::unique_ptr<EngineLogger>(logger);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On creating engine logger.");

			throw;
		}
	}

	std::unique_ptr<Core::SystemManager> Engine::CreateSystemManager(const SystemFactoriesContainer& systemFactories)
	{
		try
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create system manager.");
			const auto manager = new Core::SystemManager(systemFactories, *this);
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "System manager created.");

			return std::unique_ptr<Core::SystemManager>(manager);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Logger(), e, "On creating system manager.");

			throw;
		}
	}
}
