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

export module Application:EngineLoop;

import <exception>;
import <format>;
import <stdexcept>;

import PonyEngine.Common;
import PonyEngine.Core.Implementation;
import PonyEngine.Log;
import PonyEngine.Time;

import :ILoopElement;
import :IEngineConfigProvider;

export namespace Application
{
	/// @brief Engine loop.
	class EngineLoop final : public ILoopElement
	{
	public:
		/// @brief Creates an engine loop.
		/// @param loggerToUse Logger to use.
		/// @param systemFactoriesProvider Engine system factories provider.
		/// @param engineSetupAgent Engine set-up agent.
		[[nodiscard("Pure constructor")]]
		EngineLoop(PonyEngine::Log::ILogger& loggerToUse, const IEngineConfigProvider& systemFactoriesProvider);
		EngineLoop(const EngineLoop&) = delete;
		EngineLoop(EngineLoop&&) = delete;

		~EngineLoop() noexcept;

		virtual bool Tick(int& exitCode) override;

		EngineLoop& operator =(const EngineLoop&) = delete;
		EngineLoop& operator =(EngineLoop&&) = delete;

	private:
		PonyEngine::Log::ILogger* const logger; ///< logger;
		PonyEngine::Core::EngineData engine; ///< Engine.
	};
}

namespace Application
{
	/// @brief Creates an engine.
	/// @param logger Logger.
	/// @param systemFactoriesProvider System factories provider.
	/// @return Created engine.
	[[nodiscard("Pure function")]]
	PonyEngine::Core::EngineData CreateEngine(PonyEngine::Log::ILogger& logger, const IEngineConfigProvider& systemFactoriesProvider);

	EngineLoop::EngineLoop(PonyEngine::Log::ILogger& loggerToUse, const IEngineConfigProvider& systemFactoriesProvider) :
		logger{&loggerToUse},
		engine{CreateEngine(*logger, systemFactoriesProvider)}
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Set up engine systems.");
		systemFactoriesProvider.SetupSystems(engine.engine->SystemManager());
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine systems set up.");
	}

	EngineLoop::~EngineLoop() noexcept
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Destroy engine.");
		engine.engine.reset();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine destroyed.");
	}

	bool EngineLoop::Tick(int& exitCode)
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Verbose, "Tick engine.");

		try
		{
			engine.tickableEngine->Tick();
		}
		catch (const std::exception& e)
		{
			if (!engine.engine->IsRunning())
			{
				// Logging is done in the engine.
				exitCode = engine.engine->ExitCode();

				return true;
			}

			PONY_LOG_E_GENERAL(logger, e, "On ticking engine.")

			exitCode = static_cast<int>(PonyEngine::Common::ExitCodes::EngineTickException);

			return true;
		}

		if (engine.engine->IsRunning()) [[likely]]
		{
			return false;
		}

		exitCode = engine.engine->ExitCode();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine exited with code '{}'.", exitCode);

		return true;
	}

	PonyEngine::Core::EngineData CreateEngine(PonyEngine::Log::ILogger& logger, const IEngineConfigProvider& systemFactoriesProvider)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create engine.");
		auto params = PonyEngine::Core::EngineParams{.logger = logger};
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Add system factories to params.");
		systemFactoriesProvider.AddSystemFactories(params.systemFactories);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "System factories added to params.");
		PonyEngine::Core::EngineData engine = PonyEngine::Core::CreateEngine(params);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Engine created.");

		return engine;
	}
}
