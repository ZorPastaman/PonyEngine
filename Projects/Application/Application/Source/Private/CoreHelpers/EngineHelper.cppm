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

#include "PonyEngine/Log/EngineLog.h"
#include "PonyEngine/Log/Log.h"

export module CoreHelpers:EngineHelper;

import PonyEngine.Core.Implementation;
import PonyEngine.Log;
import PonyEngine.Time;

import TimeHelpers;

export namespace CoreHelpers
{
	/// @brief Creates an engine.
	/// @param engineParams Engine parameters.
	/// @return Created engine.
	[[nodiscard("Pure function")]]
	PonyEngine::Core::EngineData CreateEngine(const PonyEngine::Core::EngineParams& engineParams);
	/// @brief Sets up the @p engine.
	/// @param engine Engine to set up.
	void SetupEngine(const PonyEngine::Core::IEngine& engine);
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

	/// @brief Sets up a frame rate system of the @p engine.
	/// @param engine Engine to set up.
	void SetupFrameRateSystem(const PonyEngine::Core::IEngine& engine) noexcept;
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

	void SetupEngine(const PonyEngine::Core::IEngine& engine)
	{
		PONY_LOG(&engine, PonyEngine::Log::LogType::Debug, "Set up frame rate system.");
		SetupFrameRateSystem(engine);
		PONY_LOG(&engine, PonyEngine::Log::LogType::Debug, "Frame rate system set up.");
	}

	PonyEngine::Core::EngineData CreateAndSetupEngine(PonyEngine::Log::ILogger& logger, const PonyEngine::Core::SystemFactoriesContainer& factories)
	{
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Create engine params.");
		const PonyEngine::Core::EngineParams params = CreateEngineParams(logger, factories);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Engine params created.");

		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "Create engine.");
		auto engineData = CoreHelpers::CreateEngine(params);
		PONY_LOG_GENERAL(&logger, PonyEngine::Log::LogType::Debug, "'{}' engine created.", engineData.engine->Name());

		PONY_LOG(engineData.engine.get(), PonyEngine::Log::LogType::Info, "Set up engine.")
		SetupEngine(*engineData.engine);
		PONY_LOG(engineData.engine.get(), PonyEngine::Log::LogType::Info, "Engine set up.")

		return engineData;
	}

	PonyEngine::Core::EngineParams CreateEngineParams(PonyEngine::Log::ILogger& logger, const PonyEngine::Core::SystemFactoriesContainer& factories)
	{
		auto params = PonyEngine::Core::EngineParams{.logger = logger};
		params.systemFactories = factories;

		return params;
	}

	void SetupFrameRateSystem(const PonyEngine::Core::IEngine& engine) noexcept
	{
		if (const auto frameRateSystem = engine.SystemManager().FindSystem<PonyEngine::Time::IFrameRateSystem>())
		{
			TimeHelpers::SetupFrameRateSystem(*frameRateSystem);
		}
		else
		{
			PONY_LOG(&engine, PonyEngine::Log::LogType::Warning, "Engine doesn't have frame rate system.");
		}
	}
}
