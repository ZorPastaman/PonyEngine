/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Base.h"

export module PonyEngine.Core:TickableSystem;

import :IEngineContext;
import :System;
import :SystemParams;

export namespace PonyEngine::Core
{
	/// @brief Tickable system.
	class TickableSystem : public System
	{
		BASE_BODY_WITHOUT_CONSTRUCTOR(TickableSystem)

	public:
		/// @brief Ticks the system.
		virtual void Tick() = 0;

	protected:
		/// @brief Creates a tickable system.
		/// @param engine Engine context.
		/// @param params System parameters.
		[[nodiscard("Pure constructor")]]
		TickableSystem(IEngineContext& engine, const SystemParams& params) noexcept;
	};
}

namespace PonyEngine::Core
{
	TickableSystem::TickableSystem(IEngineContext& engine, const SystemParams& params) noexcept :
		System(engine, params)
	{
	}
}
