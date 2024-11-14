/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:TickableSystem;

import :IEngineContext;
import :System;
import :SystemParams;

export namespace PonyEngine::Core
{
	/// @brief Tickable system.
	class TickableSystem : public System
	{
	public:
		TickableSystem(const TickableSystem&) = delete;
		TickableSystem(TickableSystem&&) = delete;

		virtual ~TickableSystem() noexcept override = default;

		/// @brief Ticks the system.
		virtual void Tick() = 0;

		TickableSystem& operator =(const TickableSystem&) = delete;
		TickableSystem& operator =(TickableSystem&&) = delete;

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
