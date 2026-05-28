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
import :ObjectHandle;

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
		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IWorld> CreateWorld() = 0;
		virtual void CollectDeadWorlds() = 0;

		template<Component Component, typename Object>
		void RegisterComponentObjectHandleMember(ObjectHandle<Object> Component::* member);
		template<typename T> [[nodiscard("Weird call")]]
		ObjectHandle<T> RegisterObject(const std::shared_ptr<T>& object);
		template<typename T>
		void UnregisterObject(ObjectHandle<T> handle);
		template<typename T> [[nodiscard("Pure function")]]
		bool IsObjectValid(ObjectHandle<T> handle) const noexcept;
		template<typename T> [[nodiscard("Pure function")]]
		T* GetObject(ObjectHandle<T> handle) const;
		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<T> GetSharedObject(ObjectHandle<T> handle) const;
		virtual void CollectGarbage() = 0;

	protected:
		/// @brief Registers the component type.
		/// @param componentType Component type.
		/// @param componentSize Component size.
		/// @param componentAlignment Component alignment.
		virtual void RegisterComponent(std::type_index componentType, std::size_t componentSize, std::size_t componentAlignment) = 0;

		virtual void RegisterComponentObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset) = 0;
		[[nodiscard("Weird call")]]
		virtual std::pair<HandleID, HandleVersion> RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object) = 0;
		virtual void UnregisterObject(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsObjectValid(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<void>& GetObject(std::type_index objectType, HandleID handleId, HandleVersion handleVersion) const = 0;
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
	void IWorldService::RegisterComponentObjectHandleMember(ObjectHandle<Object> Component::* const member)
	{
#ifndef NDEBUG
		if (!member) [[unlikely]]
		{
			throw std::invalid_argument("Member is nullptr");
		}
#endif

		const std::size_t offset = reinterpret_cast<std::size_t>(&(reinterpret_cast<const Component*>(0)->*member));
		RegisterComponentObjectHandleMember(typeid(Object), typeid(Component), offset);
	}

	template<typename T>
	ObjectHandle<T> IWorldService::RegisterObject(const std::shared_ptr<T>& object)
	{
		const auto [handleId, handleVersion] = RegisterObject(typeid(T), object);
		return ObjectHandle<T>{.id = handleId, .version = handleVersion};
	}

	template<typename T>
	void IWorldService::UnregisterObject(const ObjectHandle<T> handle)
	{
		UnregisterObject(typeid(T), handle.id, handle.version);
	}

	template<typename T>
	bool IWorldService::IsObjectValid(const ObjectHandle<T> handle) const noexcept
	{
		return IsObjectValid(typeid(T), handle.id, handle.version);
	}

	template<typename T>
	T* IWorldService::GetObject(const ObjectHandle<T> handle) const
	{
		return static_cast<T*>(GetObject(typeid(T), handle.id, handle.version).get());
	}

	template<typename T>
	std::shared_ptr<T> IWorldService::GetSharedObject(const ObjectHandle<T> handle) const
	{
		return std::static_pointer_cast<T>(GetObject(typeid(T), handle.id, handle.version));
	}
}
