/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyEngine.Core.Implementation;

export import PonyEngine.Core.Factory;

import <utility>;

import PonyBase.Memory;

import :Engine;

export namespace PonyEngine::Core
{
	/// @brief Creates an engine.
	/// @param application Application context.
	/// @param params Engine parameters.
	/// @return Created engine.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT EngineData CreateEngine(IApplicationContext& application, const EngineParams& params);
}

namespace PonyEngine::Core
{
	EngineData CreateEngine(IApplicationContext& application, const EngineParams& params)
	{
		auto engine = PonyBase::Memory::UniquePointer<Engine>::Create(application, params.systemFactories);

		return EngineData{.engine = PonyBase::Memory::UniquePointer<IEngine>(std::move(engine))};
	}
}
