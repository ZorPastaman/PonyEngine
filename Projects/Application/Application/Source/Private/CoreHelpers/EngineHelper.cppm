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

#include "PonyEngine/Log/Log.h"

export module CoreHelpers:EngineHelper;

import PonyEngine.Core.Implementation;
import PonyEngine.Log;

export namespace CoreHelpers
{
	/// @brief Creates an engine.
	/// @param engineParams Engine parameters.
	/// @return Created engine.
	[[nodiscard("Pure function")]]
	PonyEngine::Core::EngineData CreateEngine(const PonyEngine::Core::EngineParams& engineParams);
	/// @brief Creates and sets up an engine.
	/// @param logger Logger.
	/// @param factories System factories.
	/// @return Created and set up engine.
	[[nodiscard("Pure function")]]
	PonyEngine::Core::EngineData CreateAndSetupEngine(PonyEngine::Log::ILogger& logger, const PonyEngine::Core::SystemFactoriesContainer& factories);

	/// @brief Creates an engine parameters.
	/// @param logger Logger.
	/// @param factories System factories.
	/// @return Created parameters.
	[[nodiscard("Pure function")]]
	PonyEngine::Core::EngineParams CreateEngineParams(PonyEngine::Log::ILogger& logger, const PonyEngine::Core::SystemFactoriesContainer& factories);
}

namespace CoreHelpers
{
	PonyEngine::Core::EngineData CreateEngine(const PonyEngine::Core::EngineParams& engineParams)
	{
		PonyEngine::Core::EngineData engine = PonyEngine::Core::CreateEngine(engineParams);
		assert(engine.engine && "The engine is nullptr.");
		assert(engine.tickableEngine && "The tickable engine is nullptr.");

		return engine;
	}

	PonyEngine::Core::EngineData CreateAndSetupEngine(PonyEngine::Log::ILogger& logger, const PonyEngine::Core::SystemFactoriesContainer& factories)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Create engine params.");
		const PonyEngine::Core::EngineParams params = CreateEngineParams(logger, factories);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Engine params created.");

		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Create engine.");
		auto engineData = CoreHelpers::CreateEngine(params);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "'{}' engine created.", engineData.engine->Name());

		return engineData;
	}

	PonyEngine::Core::EngineParams CreateEngineParams(PonyEngine::Log::ILogger& logger, const PonyEngine::Core::SystemFactoriesContainer& factories)
	{
		auto params = PonyEngine::Core::EngineParams{.logger = logger};
		params.systemFactories = factories;

		return params;
	}
}
