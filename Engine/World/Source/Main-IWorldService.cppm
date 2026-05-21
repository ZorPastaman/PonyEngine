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
	class IWorldService
	{
		PONY_INTERFACE_BODY(IWorldService)

		template<Component T>
		void RegisterComponent();
		template<Tag T>
		void RegisterTag();

		[[nodiscard("Wierd call")]]
		virtual std::shared_ptr<IWorld> CreateWorld() = 0;

	protected:
		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) = 0;
		virtual void RegisterTag(std::type_index tagType) = 0;
	};
}

namespace PonyEngine::World
{
	template<Component T>
	void IWorldService::RegisterComponent()
	{
		RegisterComponent(typeid(T), sizeof(T), alignof(T));
	}

	template<Tag T>
	void IWorldService::RegisterTag()
	{
		RegisterTag(typeid(T));
	}
}
