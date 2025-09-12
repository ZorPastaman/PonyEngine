/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:ServiceData;

import std;

import PonyEngine.Utility;

import :IService;
import :ITickableService;

export namespace PonyEngine::Application
{
	/// @brief Service data.
	struct ServiceData final
	{
		std::variant<std::shared_ptr<IService>, std::shared_ptr<ITickableService>> service; ///< Service.
		Utility::ObjectInterfaces publicInterfaces; ///< Service public interfaces.
		std::int32_t tickOrder = 0; ///< Service tick order. It's used only the @p service is a tickable service.
	};
}
