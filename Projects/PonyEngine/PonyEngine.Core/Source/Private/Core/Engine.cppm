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

import <format>;
import <memory>;
import <stdexcept>;
import <string>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;

import :SystemManager;
import :TimeManager;

export namespace PonyEngine::Core
{
	/// @brief Engine.
	class Engine final : public IAdvancedEngine
	{
	public:
		/// @brief Creates an @p Engine with the @p params.
		/// @param params Engine parameters.
		[[nodiscard("Pure constructor")]]
		explicit Engine(const EngineParams& params);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		~Engine() noexcept;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ITimeManager& TimeManager() const noexcept override;
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
		Log::ILogger* const logger; ///< Logger.

		std::unique_ptr<Core::TimeManager> timeManager; ///< Time manager.
		std::unique_ptr<Core::SystemManager> systemManager; ///< System manager.

		int engineExitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
	};
}

namespace PonyEngine::Core
{
	Engine::Engine(const EngineParams& params) :
		logger{&params.Logger()},
		isRunning{true}
	{
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Create time manager");
		timeManager.reset(new Core::TimeManager(*this));
		PONY_LOG(this, Log::LogType::Info, "Time manager created.");

		PONY_LOG(this, Log::LogType::Info, "Create system manager.");
		systemManager.reset(new Core::SystemManager(params, *this));
		PONY_LOG(this, Log::LogType::Info, "System manager created.");

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

		PONY_LOG(this, Log::LogType::Info, "Destroy time manager.");
		timeManager.reset();
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Time manager destroyed.");
	}

	Log::ILogger& Engine::Logger() const noexcept
	{
		return *logger;
	}

	ITimeManager& Engine::TimeManager() const noexcept
	{
		return *timeManager;
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
		if (!isRunning)
		{
			throw std::logic_error("The engine is ticked when it's already been stopped.");
		}

		PONY_LOG(this, Log::LogType::Verbose, "Tick time manager.");
		timeManager->Tick();
		PONY_LOG(this, Log::LogType::Verbose, "Tick system manager.");
		systemManager->Tick();
	}

	const char* Engine::Name() const noexcept
	{
		return StaticName;
	}
}
