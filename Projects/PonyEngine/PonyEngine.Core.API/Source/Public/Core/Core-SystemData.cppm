/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:SystemData;

import <memory>;
import <variant>;

import PonyBase.Utility;

import :System;
import :TickableSystem;

export namespace PonyEngine::Core
{
	/// @brief System data.
	struct SystemData final
	{
		std::variant<std::shared_ptr<System>, std::shared_ptr<TickableSystem>> system; ///< System.
		PonyBase::Utility::ObjectInterfaces publicInterfaces; ///< System public interfaces.
	};
}
