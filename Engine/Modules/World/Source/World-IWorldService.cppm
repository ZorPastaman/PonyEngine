/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.World:IWorldService;

import std;

import :Component;
import :IWorld;
import :WorldDefinition;

export namespace PonyEngine::World
{
	/// @brief World service.
	class IWorldService
	{
		PONY_INTERFACE_BODY(IWorldService)

		/// @brief Registers the component type.
		/// @tparam T Component type.
		/// @note The function is thread-safe.
		template<Component T>
		void RegisterComponent();
		/// @brief Registers the component object handle member.
		/// @tparam Component Component type.
		/// @tparam Object Object type.
		/// @param member Member pointer. Mustn't be nullptr.
		/// @remark It's used for correct garbage collection.
		/// @note The function is thread-safe.
		template<Component Component, typename Object>
		void RegisterObjectHandleMember(ObjectHandle<Object> Component::* member);
		/// @brief Register the component entity reference member.
		/// @tparam Component Component type.
		/// @param member Entity reference member. Mustn't be nullptr.
		/// @note The function is thread-safe.
		template<Component Component>
		void RegisterEntityReferenceMember(Entity Component::* member);

		/// @brief Creates a world.
		/// @return World.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IWorld> CreateWorld() = 0;
		/// @brief Creates a world.
		/// @param definition World definition.
		/// @return World.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IWorld> CreateWorld(const WorldDefinition& definition) = 0;

	protected:
		/// @brief Registers the component type.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param componentAlignment Component alignment.
		/// @note The function is thread-safe.
		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) = 0;
		/// @brief Registers the component object handle member.
		/// @param objectType Object type.
		/// @param componentType Component type.
		/// @param componentOffset Component offset.
		/// @note The function is thread-safe.
		virtual void RegisterObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset) = 0;
		/// @brief Register the component entity reference member.
		/// @param componentType Component type.
		/// @param componentOffset Entity reference member. Mustn't be nullptr.
		/// @note The function is thread-safe.
		virtual void RegisterEntityReferenceMember(std::type_index componentType, std::size_t componentOffset) = 0;
	};
}

namespace PonyEngine::World
{
	template<Component T>
	void IWorldService::RegisterComponent()
	{
		RegisterComponent(typeid(T), sizeof(T), alignof(T));
	}

	template<Component Component, typename Object>
	void IWorldService::RegisterObjectHandleMember(ObjectHandle<Object> Component::* const member)
	{
		assert(member && "Member is nullptr");

		Component dummy{};
		const std::size_t offset = static_cast<std::size_t>(reinterpret_cast<std::uintptr_t>(&(dummy.*member).typeless) - reinterpret_cast<std::uintptr_t>(&dummy));
		RegisterObjectHandleMember(typeid(Object), typeid(Component), offset);
	}

	template<Component Component>
	void IWorldService::RegisterEntityReferenceMember(Entity Component::* const member)
	{
		assert(member && "Member is nullptr");

		Component dummy{};
		const std::size_t offset = static_cast<std::size_t>(reinterpret_cast<std::uintptr_t>(&(dummy.*member)) - reinterpret_cast<std::uintptr_t>(&dummy));
		RegisterEntityReferenceMember(typeid(Component), offset);
	}
}
