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

export module CoreHelpers:EngineHelper;

import <stdexcept>;

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
	/// @param engineParams Engine parameters.
	/// @return Created and set up engine.
	[[nodiscard("Pure function")]]
	PonyEngine::Core::EngineData CreateAndSetupEngine(const PonyEngine::Core::EngineParams& engineParams);
}

namespace CoreHelpers
{
	PonyEngine::Core::EngineData CreateEngine(const PonyEngine::Core::EngineParams& engineParams)
	{
		PonyEngine::Core::EngineData engine = PonyEngine::Core::CreateEngine(engineParams);
		if (!engine.engine)
		{
			throw std::logic_error("The engine is nullptr.");
		}
		if (!engine.tickableEngine)
		{
			throw std::logic_error("The tickable engine is nullptr.");
		}

		return engine;
	}

	PonyEngine::Core::EngineData CreateAndSetupEngine(const PonyEngine::Core::EngineParams& engineParams)
	{
		PONY_LOG_GENERAL(engineParams.logger, PonyEngine::Log::LogType::Info, "Create engine.");
		auto engine = CoreHelpers::CreateEngine(engineParams);
		PONY_LOG_GENERAL(engineParams.logger, PonyEngine::Log::LogType::Info, "'{}' engine created.", engine.engine->Name());

		return engine;
	}
}
