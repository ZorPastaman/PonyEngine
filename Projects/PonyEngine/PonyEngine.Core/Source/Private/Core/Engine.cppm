/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/EngineLog.h"

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <exception>;
import <format>;
import <memory>;
import <stdexcept>;
import <string>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.Common;

import :SystemManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class Engine final : public IEngine, public ITickableEngine
	{
	public:
		/// @brief Creates an @p Engine.
		/// @param logger Logger.
		/// @param systemFactories System factories.
		[[nodiscard("Pure constructor")]]
		Engine(Log::ILogger& logger, const SystemFactoriesContainer& systemFactories);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::size_t FrameCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ISystemManager& SystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int ExitCode() const noexcept override;
		virtual void Stop(int exitCode = static_cast<int>(Common::ExitCodes::Success)) noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Core::Engine"; ///< Class name.

	private:
		std::size_t frameCount; ///< Frame count.

		int engineExitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
		bool isTicking; ///< @a True if the engine is ticking now; @a false otherwise.

		Log::ILogger* const logger; ///< Logger.
		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Core
{
	/// @brief Prepares the @p logger for work.
	/// @param logger Logger.
	/// @return Prepared logger.
	[[nodiscard("Pure function")]]
	Log::ILogger* PrepareLogger(Log::ILogger& logger) noexcept;
	/// @brief Creates a system manager.
	/// @param systemFactories Engine parameters.
	/// @param engine Engine that owns the manager.
	/// @return Created system manager.
	[[nodiscard("Pure function")]]
	std::unique_ptr<SystemManager> CreateSystemManager(const SystemFactoriesContainer& systemFactories, IEngine& engine);

	Engine::Engine(Log::ILogger& logger, const SystemFactoriesContainer& systemFactories) :
		frameCount{0},
		isRunning{true},
		isTicking{false},
		logger{PrepareLogger(logger)},
		systemManager{CreateSystemManager(systemFactories, *this)}
	{
		PONY_LOG(this, Log::LogType::Info, "Begin system manager.");
		systemManager->Begin();
		PONY_LOG(this, Log::LogType::Info, "System manager begun.");
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG(this, Log::LogType::Info, "End system manager.");
		systemManager->End();
		PONY_LOG(this, Log::LogType::Info, "System manager ended.");

		PONY_LOG(this, Log::LogType::Info, "Destroy system manager.");
		systemManager.reset();
		PONY_LOG(this, Log::LogType::Info, "System manager destroyed.");
	}

	std::size_t Engine::FrameCount() const noexcept
	{
		return frameCount;
	}

	Log::ILogger& Engine::Logger() const noexcept
	{
		return *logger;
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
		PONY_LOG_IF(isRunning, this, Log::LogType::Warning, "Tried to get exit code when engine is still running.");

		return engineExitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			engineExitCode = exitCode;
			isRunning = false;
			PONY_LOG(this, Log::LogType::Info, "Engine stopped with exit code '{}'.", exitCode);
		}
		else
		{
			PONY_LOG(this, Log::LogType::Info, "Tried to stop already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!isRunning)
		{
			throw std::logic_error("Engine is ticked when it's already been stopped.");
		}

		if (isTicking)
		{
			throw std::logic_error("Engine is ticked inside another tick.");
		}
		isTicking = true;

		PONY_LOG(this, Log::LogType::Verbose, "Tick system manager.");

		try
		{
			systemManager->Tick();
		}
		catch (...)
		{
			// Logging is done in the system manager.
			Stop(static_cast<int>(Common::ExitCodes::SystemTickException));
			isTicking = false;

			throw;
		}

		++frameCount;
		isTicking = false;
	}

	const char* Engine::Name() const noexcept
	{
		return StaticName;
	}

	Log::ILogger* PrepareLogger(Log::ILogger& logger) noexcept
	{
		PONY_LOG_GENERAL(&logger, Log::LogType::Info, "Engine uses '{}' logger.", logger.Name());

		return &logger;
	}

	std::unique_ptr<SystemManager> CreateSystemManager(const SystemFactoriesContainer& systemFactories, IEngine& engine)
	{
		PONY_LOG(&engine, Log::LogType::Info, "Create system manager.");
		const auto systemManager = new SystemManager(systemFactories, engine);
		PONY_LOG(&engine, Log::LogType::Info, "System manager created.");

		return std::unique_ptr<SystemManager>(systemManager);
	}
}
