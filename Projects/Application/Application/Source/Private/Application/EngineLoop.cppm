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

import <format>;
import <stdexcept>;

import PonyEngine.Core.Implementation;
import PonyEngine.Log;
import PonyEngine.Time;

import CoreHelpers;

import :ILoopElement;
import :ISystemFactoriesProvider;

export namespace Application
{
	/// @brief Engine loop.
	class EngineLoop final : public ILoopElement
	{
	public:
		/// @brief Creates an engine loop.
		/// @param loggerToUse Logger to use.
		/// @param systemFactoriesProvider Engine system factories provider.
		[[nodiscard("Pure constructor")]]
		EngineLoop(PonyEngine::Log::ILogger& loggerToUse, const ISystemFactoriesProvider& systemFactoriesProvider);
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
	PonyEngine::Core::EngineData CreateEngine(PonyEngine::Log::ILogger& logger, const ISystemFactoriesProvider& systemFactoriesProvider);

	EngineLoop::EngineLoop(PonyEngine::Log::ILogger& loggerToUse, const ISystemFactoriesProvider& systemFactoriesProvider) :
		logger{&loggerToUse},
		engine{CreateEngine(*logger, systemFactoriesProvider)}
	{
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
		engine.tickableEngine->Tick();

		if (engine.engine->IsRunning()) [[likely]]
		{
			return false;
		}

		exitCode = engine.engine->ExitCode();
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine exited with the code '{}'.", exitCode);

		return true;
	}

	PonyEngine::Core::EngineData CreateEngine(PonyEngine::Log::ILogger& logger, const ISystemFactoriesProvider& systemFactoriesProvider)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create engine params.");
		auto engineParams = PonyEngine::Core::EngineParams{.logger = logger};
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Add system factories.");
		systemFactoriesProvider.AddSystemFactories(engineParams.systemFactories);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "System factories added.");
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Engine params created.");

		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "Create and set up engine.");
		auto engine = CoreHelpers::CreateAndSetupEngine(engineParams);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Info, "'{}' engine created and set up.", engine.engine->Name());

		return engine;
	}
}
