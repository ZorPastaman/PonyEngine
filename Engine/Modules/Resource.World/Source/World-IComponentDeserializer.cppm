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

export module PonyEngine.Resource.World:IComponentDeserializer;

import std;

export namespace PonyEngine::Resource::World
{
	class IComponentDeserializer
	{
		PONY_INTERFACE_BODY(IComponentDeserializer)

		virtual void Deserialize(std::span<const std::byte> input, std::span<std::byte> output) = 0;
	};
}
