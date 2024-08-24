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
import <format>;
import <memory>;
import <stdexcept>;
import <string>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;

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
		virtual void Stop(int exitCode = 0) noexcept override;

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

		Log::ILogger* const logger; ///< Logger.
		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.
	};
}

namespace PonyEngine::Core
{
	/// @brief Creates a system manager.
	/// @param systemFactories Engine parameters.
	/// @param engine Engine that owns the manager.
	/// @return Created system manager.
	[[nodiscard("Pure function")]]
	std::unique_ptr<SystemManager> CreateSystemManager(const SystemFactoriesContainer& systemFactories, IEngine& engine);

	Engine::Engine(Log::ILogger& logger, const SystemFactoriesContainer& systemFactories) :
		frameCount{0},
		isRunning{true},
		logger{&logger},
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
		PONY_LOG_IF(isRunning, this, Log::LogType::Warning, "Tried to get the exit code when the engine is still running.");

		return engineExitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			PONY_LOG(this, Log::LogType::Info, "Stop the engine with the exit code '{}'.", exitCode);
			isRunning = false;
			engineExitCode = exitCode;
		}
		else
		{
			PONY_LOG(this, Log::LogType::Info, "Tried to stop the already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!isRunning) // TODO: Throw if the engine is ticked when it's in tick. Need to think about exceptions from SystemManager::Tick().
		{
			throw std::logic_error("The engine is ticked when it's already been stopped.");
		}

		PONY_LOG(this, Log::LogType::Verbose, "Tick system manager.");
		systemManager->Tick();

		++frameCount;
	}

	const char* Engine::Name() const noexcept
	{
		return StaticName;
	}

	std::unique_ptr<SystemManager> CreateSystemManager(const SystemFactoriesContainer& systemFactories, IEngine& engine)
	{
		PONY_LOG(&engine, Log::LogType::Info, "Create system manager.");
		const auto systemManager = new SystemManager(systemFactories, engine);
		PONY_LOG(&engine, Log::LogType::Info, "System manager created.");

		return std::unique_ptr<SystemManager>(systemManager);
	}
}
