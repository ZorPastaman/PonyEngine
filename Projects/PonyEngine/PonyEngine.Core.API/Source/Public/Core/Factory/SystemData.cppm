/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemData;

import <variant>;

import PonyBase.Memory;

import PonyEngine.Core;

import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	/// @brief System data.
	struct SystemData final
	{
		std::variant<PonyBase::Memory::UniquePointer<IEngineSystem>, PonyBase::Memory::UniquePointer<ITickableEngineSystem>> system; ///< System.
		ObjectInterfaces publicInterfaces; ///< System public interfaces.
	};
}
