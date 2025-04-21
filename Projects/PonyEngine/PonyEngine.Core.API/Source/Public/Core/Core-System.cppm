/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Core:System;

import :IEngineContext;
import :SystemParams;

export namespace PonyEngine::Core
{
	/// @brief System.
	class System
	{
		BASE_BODY(System)

	public:
		/// @brief Begins the system.
		/// @details It's called once before a first engine tick.
		virtual void Begin() = 0;
		/// @brief Ends the system.
		/// @details It's called once after a last engine tick.
		virtual void End() = 0;

	protected:
		/// @brief Creates a system.
		/// @param engine Engine context.
		/// @param params System parameters.
		[[nodiscard("Pure constructor")]]
		System(IEngineContext& engine, const SystemParams& params) noexcept;

		/// @brief Gets the engine context.
		/// @return Engine context.
		[[nodiscard("Pure function")]]
		IEngineContext& Engine() const noexcept;

	private:
		IEngineContext* engine; ///< Engine context.
	};
}

namespace PonyEngine::Core
{
	System::System(IEngineContext& engine, const SystemParams&) noexcept :
		engine{&engine}
	{
	}

	IEngineContext& System::Engine() const noexcept
	{
		return *engine;
	}
}
