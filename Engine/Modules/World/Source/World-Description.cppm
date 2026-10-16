/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:Description;

import std;

import :ObjectHandle;

export namespace PonyEngine::World
{
	/// @brief Description. Holds data to any @p std::string_view object.
	struct Description final
	{
		ObjectHandle<const std::string_view> value; ///< Description object handle.
	};
}
