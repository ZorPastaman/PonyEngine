/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Engine.Extension:SystemData;

import std;

import PonyEngine.Utility;

import :ISystem;
import :ITickableSystem;

export namespace PonyEngine::Engine
{
	/// @brief System data.
	struct SystemData final
	{
		std::variant<std::shared_ptr<ISystem>, std::shared_ptr<ITickableSystem>> system; ///< System.
		Utility::ObjectInterfaces publicInterfaces; ///< System public interfaces.
		std::int32_t tickOrder = 0; ///< Tick order. It's used only the @p system is a tickable system.
	};
}
