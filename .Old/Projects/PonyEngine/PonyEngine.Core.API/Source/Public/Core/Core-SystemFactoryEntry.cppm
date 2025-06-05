/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:SystemFactoryEntry;

import <cstdint>;
import <memory>;

import :ISystemFactory;

export namespace PonyEngine::Core
{
	/// @brief System factory entry.
	struct SystemFactoryEntry final
	{
		std::shared_ptr<ISystemFactory> factory; ///< System factory. Mustn't be @a nullptr.
		std::int32_t tickOrder = 0; ///< Tick order.
	};
}
