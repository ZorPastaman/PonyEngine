/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.World:IObjectDeserializer;

import std;

export namespace PonyEngine::Resource::World
{
	class IObjectDeserializer
	{
		PONY_INTERFACE_BODY(IObjectDeserializer)

		virtual void Deserialize(std::span<const std::byte> input, std::shared_ptr<void>& output) = 0;
	};
}
