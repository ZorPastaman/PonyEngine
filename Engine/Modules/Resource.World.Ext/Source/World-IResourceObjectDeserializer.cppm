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

export module PonyEngine.Resource.World.Ext:IResourceObjectDeserializer;

import std;

import PonyEngine.World;

export namespace PonyEngine::Resource::World
{
	class IResourceObjectDeserializer
	{
		PONY_INTERFACE_BODY(IResourceObjectDeserializer)

		template<typename T>
		void Associate(std::string_view serializedType);
		virtual void Associate(std::type_index interfaceType, std::string_view serializedType) = 0;
	};
}

namespace PonyEngine::Resource::World
{
	template<typename T>
	void IResourceObjectDeserializer::Associate(const std::string_view serializedType)
	{
		Associate(typeid(T), serializedType);
	}
}
