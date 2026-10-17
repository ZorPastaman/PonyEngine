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

export module PonyEngine.Resource.World.Ext:IWorldDefinitionLoader;

import std;

import PonyEngine.World;

import :IComponentDeserializer;
import :IObjectDeserializer;

export namespace PonyEngine::Resource::World
{
	/// @brief World definition loader.
	class IWorldDefinitionLoader
	{
		PONY_INTERFACE_BODY(IWorldDefinitionLoader)

		/// @brief Registers the component deserializer.
		/// @tparam T Component type.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		template<PonyEngine::World::Component T>
		void RegisterComponentDeserializer(std::string_view type, IInlineComponentDeserializer& deserializer);
		/// @brief Registers the component deserializer.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void RegisterComponentDeserializer(std::type_index componentType, std::size_t componentSize, std::string_view type, IInlineComponentDeserializer& deserializer) = 0;
		/// @brief Unregisters the component deserializer.
		/// @tparam T Component type.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		template<PonyEngine::World::Component T>
		void UnregisterComponentDeserializer(std::string_view type, IInlineComponentDeserializer& deserializer);
		/// @brief Unregisters the component deserializer.
		/// @param componentType Component type.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void UnregisterComponentDeserializer(std::type_index componentType, std::string_view type, IInlineComponentDeserializer& deserializer) = 0;
		/// @brief Registers the component deserializer.
		/// @tparam T Component type.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		template<PonyEngine::World::Component T>
		void RegisterComponentDeserializer(std::string_view type, IComponentDeserializer& deserializer);
		/// @brief Registers the component deserializer.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void RegisterComponentDeserializer(std::type_index componentType, std::size_t componentSize, std::string_view type, IComponentDeserializer& deserializer) = 0;
		/// @brief Unregisters the component deserializer.
		/// @tparam T Component type.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		template<PonyEngine::World::Component T>
		void UnregisterComponentDeserializer(std::string_view type, IComponentDeserializer& deserializer);
		/// @brief Unregisters the component deserializer.
		/// @param componentType Component type.
		/// @param type Component type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void UnregisterComponentDeserializer(std::type_index componentType, std::string_view type, IComponentDeserializer& deserializer) = 0;

		/// @brief Registers the object deserializer.
		/// @param type Object type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void RegisterObjectDeserializer(std::string_view type, IInlineObjectDeserializer& deserializer) = 0;
		/// @brief Unregisters the object deserializer.
		/// @param type Object type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void UnregisterObjectDeserializer(std::string_view type, IInlineObjectDeserializer& deserializer) = 0;
		/// @brief Registers the object deserializer.
		/// @param type Object type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void RegisterObjectDeserializer(std::string_view type, IObjectDeserializer& deserializer) = 0;
		/// @brief Unregisters the object deserializer.
		/// @param type Object type in serialized data.
		/// @param deserializer Deserializer.
		/// @note The function must be called on main thread.
		virtual void UnregisterObjectDeserializer(std::string_view type, IObjectDeserializer& deserializer) = 0;
	};
}

namespace PonyEngine::Resource::World
{
	template<PonyEngine::World::Component T>
	void IWorldDefinitionLoader::RegisterComponentDeserializer(const std::string_view type, IInlineComponentDeserializer& deserializer)
	{
		RegisterComponentDeserializer(typeid(T), sizeof(T), type, deserializer);
	}

	template<PonyEngine::World::Component T>
	void IWorldDefinitionLoader::UnregisterComponentDeserializer(const std::string_view type, IInlineComponentDeserializer& deserializer)
	{
		UnregisterComponentDeserializer(typeid(T), type, deserializer);
	}

	template<PonyEngine::World::Component T>
	void IWorldDefinitionLoader::RegisterComponentDeserializer(const std::string_view type, IComponentDeserializer& deserializer)
	{
		RegisterComponentDeserializer(typeid(T), sizeof(T), type, deserializer);
	}

	template<PonyEngine::World::Component T>
	void IWorldDefinitionLoader::UnregisterComponentDeserializer(const std::string_view type, IComponentDeserializer& deserializer)
	{
		UnregisterComponentDeserializer(typeid(T), type, deserializer);
	}
}
