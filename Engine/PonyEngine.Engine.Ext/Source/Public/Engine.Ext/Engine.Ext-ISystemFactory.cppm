/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Engine.Ext:ISystemFactory;

import :IEngineContext;
import :SystemData;

export namespace PonyEngine::Engine
{
	/// @brief System factory.
	class ISystemFactory
	{
		INTERFACE_BODY(ISystemFactory)

		/// @brief Creates a system.
		/// @param engine Engine context.
		/// @return Created system data.
		[[nodiscard("Redundant call")]]
		virtual SystemData Create(IEngineContext& engine) = 0;

		/// @brief Gets the system initialize order.
		/// @note The order must remain the same for the whole engine lifetime.
		/// @return System initialize order.
		[[nodiscard("Pure function")]]
		virtual std::int32_t InitOrder() const noexcept = 0;
		/// @brief Gets the system tick order.
		/// @note The order must remain the same for the whole engine lifetime.
		/// @return System tick order.
		[[nodiscard("Pure function")]]
		virtual std::int32_t TickOrder() const noexcept = 0;
	};
}
