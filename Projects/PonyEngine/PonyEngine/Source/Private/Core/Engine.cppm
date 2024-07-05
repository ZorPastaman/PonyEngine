/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:Engine;

import <cstddef>;
import <format>;
import <memory>;
import <stdexcept>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;
import PonyEngine.Log;

import :SystemManager;
import :TimeManager;

export namespace PonyEngine::Core
{
	/// @brief Pony Engine main class.
	class Engine final : public IEngine
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
		virtual Log::ILogger& GetLogger() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ITimeManager& GetTimeManager() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ISystemManager& GetSystemManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual int GetExitCode() const noexcept override;
		virtual void Stop(int exitCode = 0) noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

		static constexpr const char* StaticName = "PonyEngine::Engine"; ///< Engine static name.

	private:
		Log::ILogger* const logger; ///< Logger.

		std::unique_ptr<TimeManager> timeManager; ///< Time manager.
		std::unique_ptr<SystemManager> systemManager; ///< System manager.

		int exitCode; ///< Exit code. It's defined only if @p isRunning is @a true.
		bool isRunning; ///< @a True if the engine is running; @a false otherwise.
	};
}

namespace PonyEngine::Core
{
	Engine::Engine(const EngineParams& params) :
		logger{&params.GetLogger()},
		isRunning{true}
	{
		logger->Log(Log::LogType::Info, Log::LogInput("Create time manager", 0)); // TODO: Add log action wrappers
		timeManager.reset(new TimeManager());
		PONY_LOG_PTR(this, Log::LogType::Info, "Time manager created.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Create system manager.");
		systemManager.reset(new SystemManager(params, *this));
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager created.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Begin system manager.");
		systemManager->Begin();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager begun.");
	}

	Engine::~Engine() noexcept
	{
		PONY_LOG_PTR(this, Log::LogType::Info, "End system manager.");
		systemManager->End();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager ended.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Destroy system manager.");
		systemManager.reset();
		PONY_LOG_PTR(this, Log::LogType::Info, "System manager destroyed.");

		PONY_LOG_PTR(this, Log::LogType::Info, "Destroy time manager.");
		const std::size_t lastFrame = timeManager->GetFrameCount();
		timeManager.reset();
		logger->Log(Log::LogType::Info, Log::LogInput("Time manager destroyed.", lastFrame));
	}

	Log::ILogger& Engine::GetLogger() const noexcept
	{
		return *logger;
	}

	ITimeManager& Engine::GetTimeManager() const noexcept
	{
		return *timeManager;
	}

	ISystemManager& Engine::GetSystemManager() const noexcept
	{
		return *systemManager;
	}

	bool Engine::IsRunning() const noexcept
	{
		return isRunning;
	}

	int Engine::GetExitCode() const noexcept
	{
		PONY_LOG_IF_PTR(isRunning, this, Log::LogType::Warning, "Tried to get an exit code when the engine is still running.");

		return exitCode;
	}

	void Engine::Stop(const int exitCode) noexcept
	{
		if (isRunning)
		{
			PONY_LOG_PTR(this, Log::LogType::Info, std::format("Stop an engine with the exit code '{}'.", exitCode).c_str());
			isRunning = false;
			this->exitCode = exitCode;
		}
		else
		{
			PONY_LOG_PTR(this, Log::LogType::Info, "Tried to stop an already stopped engine. Ignore it.");
		}
	}

	void Engine::Tick()
	{
		if (!isRunning)
		{
			throw std::logic_error("The engine is ticked when it's already stopped.");
		}

		PONY_LOG_PTR(this, Log::LogType::Verbose, "Tick time manager.");
		timeManager->Tick();
		PONY_LOG_PTR(this, Log::LogType::Verbose, "Tick system manager.");
		systemManager->Tick();
	}

	const char* Engine::GetName() const noexcept
	{
		return StaticName;
	}
}
