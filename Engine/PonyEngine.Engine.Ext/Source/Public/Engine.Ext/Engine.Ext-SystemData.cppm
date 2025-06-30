/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Engine.Ext:SystemData;

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
	};
}
