/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemData;

import <memory>;
import <variant>;

import PonyBase.ObjectUtility;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief System data.
	struct SystemData final
	{
		std::variant<std::unique_ptr<System>, std::unique_ptr<TickableSystem>> system; ///< System.
		PonyBase::Utility::ObjectInterfaces publicInterfaces; ///< System public interfaces.
	};
}
