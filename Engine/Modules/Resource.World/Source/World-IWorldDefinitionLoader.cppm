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

export module PonyEngine.Resource.World:IWorldDefinitionLoader;

import std;

import PonyEngine.World;

import :IComponentDeserializer;
import :IObjectDeserializer;

export namespace PonyEngine::Resource::World
{
	class IWorldDefinitionLoader
	{
		PONY_INTERFACE_BODY(IWorldDefinitionLoader)

		template<PonyEngine::World::Component T>
		void RegisterComponentDeserializer(std::string_view type, IComponentDeserializer* deserializer); // Nullptr means simple copy
		template<PonyEngine::World::Component T>
		void UnregisterComponentDeserializer(std::string_view type, IComponentDeserializer* deserializer); // Nullptr means simple copy
		template<typename T>
		void RegisterObjectDeserializer(std::string_view type, IObjectDeserializer& deserializer);
		template<typename T>
		void UnregisterObjectDeserializer(std::string_view type, IObjectDeserializer& deserializer);

	protected:
		virtual void RegisterComponentDeserializer(std::type_index componentType, std::size_t componentSize, std::string_view type, IComponentDeserializer* deserializer) = 0;
		virtual void RegisterObjectDeserializer(std::type_index objectType, std::string_view type, IObjectDeserializer& deserializer) = 0;
	};
}

namespace PonyEngine::Resource::World
{
	template<PonyEngine::World::Component T>
	void IWorldDefinitionLoader::RegisterComponentDeserializer(const std::string_view type, IComponentDeserializer* const deserializer)
	{
		RegisterComponentDeserializer(typeid(T), sizeof(T), type, deserializer);
	}

	template<PonyEngine::World::Component T>
	void IWorldDefinitionLoader::UnregisterComponentDeserializer(std::string_view type,
		IComponentDeserializer* deserializer)
	{
	}

	template<typename T>
	void IWorldDefinitionLoader::RegisterObjectDeserializer(const std::string_view type, IObjectDeserializer& deserializer)
	{
		RegisterObjectDeserializer(typeid(T), type, deserializer);
	}

	template<typename T>
	void IWorldDefinitionLoader::UnregisterObjectDeserializer(std::string_view type, IObjectDeserializer& deserializer)
	{
	}
}
