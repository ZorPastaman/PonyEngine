/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:TickableServiceInfo;

import std;

import PonyEngine.Application.Ext;

export namespace PonyEngine::Application
{
	/// @brief Tickable service info.
	struct TickableServiceInfo final
	{
		ITickableService* tickableService; ///< Tickable service. May be nullptr.
		std::int32_t tickOrder; ///< Tick order.
	};
}
