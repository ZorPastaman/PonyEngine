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

export namespace PonyEngine::Resource::World
{
	/// @brief Resource object deserializer.
	/// @details It deserializes 'Pony.Resource' world objects.
	class IResourceObjectDeserializer
	{
		PONY_INTERFACE_BODY(IResourceObjectDeserializer)

		/// @brief Associates the resource interface type with its serialized type.
		/// @tparam T Resource interface type.
		/// @param serializedType Serialized type.
		template<typename T>
		void Associate(std::string_view serializedType);
		/// @brief Associates the resource interface type with its serialized type.
		/// @param interfaceType Resource interface type.
		/// @param serializedType Serialized type.
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
