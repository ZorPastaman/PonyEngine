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

export module PonyEngine.Resource.World.Ext:ICopyComponentDeserializer;

import std;

import PonyEngine.World;

export namespace PonyEngine::Resource::World
{
	/// @brief Component deserializer that simply copied an input into an output.
	class ICopyComponentDeserializer
	{
		PONY_INTERFACE_BODY(ICopyComponentDeserializer)

		/// @brief Associates the component of type @p T with the @p serializedType.
		/// @tparam T Component type.
		/// @param serializedType Serialized type.
		template<PonyEngine::World::Component T>
		void Associate(std::string_view serializedType);
		/// @brief Associates the component of type @p componentType with the @p serializedType.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param serializedType Serialized type.
		virtual void Associate(std::type_index componentType, std::size_t componentSize, std::string_view serializedType) = 0;
	};
}

namespace PonyEngine::Resource::World
{
	template<PonyEngine::World::Component T>
	void ICopyComponentDeserializer::Associate(const std::string_view serializedType)
	{
		Associate(typeid(T), sizeof(T), serializedType);
	}
}
