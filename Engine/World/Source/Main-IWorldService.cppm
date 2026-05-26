/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.World:IWorldService;

import std;

import :Component;
import :IWorld;

export namespace PonyEngine::World
{
	/// @brief World service.
	class IWorldService
	{
		PONY_INTERFACE_BODY(IWorldService)

		/// @brief Registers the component type.
		/// @tparam T Component type.
		/// @note The function is not thread-safe.
		template<Component T>
		void RegisterComponent();

		/// @brief Creates a world.
		/// @return World.
		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWorld> CreateWorld() = 0;

	protected:
		/// @brief Registers the component type.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param componentAlignment Component alignment.
		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) = 0;
	};
}

namespace PonyEngine::World
{
	template<Component T>
	void IWorldService::RegisterComponent()
	{
		RegisterComponent(typeid(T), sizeof(T), alignof(T));
	}
}
