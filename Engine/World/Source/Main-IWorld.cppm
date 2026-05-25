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

export module PonyEngine.World:IWorld;

import std;

import :Component;
import :Entity;
import :QueryParams;

export namespace PonyEngine::World
{
	class IWorld
	{
		PONY_INTERFACE_BODY(IWorld)

		[[nodiscard("Pure function")]]
		virtual std::size_t EntityCount() const noexcept = 0;
		virtual std::size_t GetEntities(std::span<Entity> entities) const noexcept = 0;
		[[nodiscard("Pure function")]]
		bool IsValid(Entity entity) const noexcept;
		[[nodiscard("Wierd call")]]
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		[[nodiscard("Pure function")]]
		virtual bool AreValid(std::span<const Entity> entities) const noexcept = 0;
		virtual void AreValid(std::span<const Entity> entities, std::span<bool> valid) const = 0;
		virtual void CreateEntities(std::span<Entity> entities) = 0;
		virtual void DestroyEntities(std::span<const Entity> entities) = 0;

		template<Component T>
		void AddComponent(Entity entity, const T& component);
		void AddComponent(Entity entity, std::type_index componentType, const void* componentData);
		template<Component T>
		T& AddComponent(Entity entity);
		void* AddComponent(Entity entity, std::type_index componentType);
		template<Component T>
		void AddComponents(std::span<const Entity> entities);
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType) = 0;
		template<Component T>
		void AddComponents(std::span<const Entity> entities, std::span<const T> components);
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, const void* componentData) = 0;
		template<Component T>
		void AddComponents(std::span<const Entity> entities, std::span<T*> componentPointers);
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, std::span<void*> componentPointers) = 0;

		template<Component T>
		void RemoveComponent(Entity entity);
		void RemoveComponent(Entity entity, std::type_index componentType);
		template<Component T>
		void RemoveComponents(std::span<const Entity> entities);
		virtual void RemoveComponents(std::span<const Entity> entities, std::type_index componentType) = 0;

		template<Component T> [[nodiscard("Pure function")]]
		bool HasComponent(Entity entity) const;
		[[nodiscard("Pure function")]]
		bool HasComponent(Entity entity, std::type_index componentType) const;
		template<Component T> [[nodiscard("Pure function")]]
		bool HasComponents(std::span<const Entity> entities) const;
		[[nodiscard("Pure function")]]
		virtual bool HasComponents(std::span<const Entity> entities, std::type_index componentType) const = 0;
		template<Component T>
		void HasComponents(std::span<const Entity> entities, std::span<bool> has) const;
		virtual void HasComponents(std::span<const Entity> entities, std::type_index componentType, std::span<bool> has) const = 0;

		template<Component T> [[nodiscard("Pure function")]]
		std::size_t CountComponents() const;
		[[nodiscard("Pure function")]]
		virtual std::size_t CountComponents(std::type_index componentType) const = 0;

		template<Component T>
		void DropComponents();
		virtual void DropComponents(std::type_index componentType) = 0;

		[[nodiscard("Pure function")]]
		virtual std::size_t CountQuery(const QueryParams& params) const = 0;
		virtual void Query(const QueryParams& params, const std::function<void(QueryItem&)>& callback) const = 0;
	};
}

namespace PonyEngine::World
{
	bool IWorld::IsValid(const Entity entity) const noexcept
	{
		return AreValid(std::span(&entity, 1uz));
	}

	Entity IWorld::CreateEntity()
	{
		Entity entity;
		CreateEntities(std::span(&entity, 1uz));
		return entity;
	}

	void IWorld::DestroyEntity(const Entity entity)
	{
		DestroyEntities(std::span(&entity, 1uz));
	}

	template<Component T>
	void IWorld::AddComponent(const Entity entity, const T& component)
	{
		AddComponent(entity, typeid(T), &component);
	}

	void IWorld::AddComponent(const Entity entity, const std::type_index componentType, const void* const componentData)
	{
		AddComponents(std::span(&entity, 1uz), componentType, componentData);
	}

	template<Component T>
	T& IWorld::AddComponent(const Entity entity)
	{
		return *static_cast<T*>(AddComponent(entity, typeid(T)));
	}

	void* IWorld::AddComponent(const Entity entity, const std::type_index componentType)
	{
		void* component;
		AddComponents(std::span(&entity, 1uz), componentType, std::span(&component, 1uz));
		return component;
	}

	template<Component T>
	void IWorld::AddComponents(const std::span<const Entity> entities)
	{
		AddComponents(entities, typeid(T));
	}

	template<Component T>
	void IWorld::AddComponents(const std::span<const Entity> entities, const std::span<const T> components)
	{
#ifndef NDEBUG
		if (entities.size() != components.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and component span sizes are mismatched");
		}
#endif

		AddComponents(entities, typeid(T), components.data());
	}

	template<Component T>
	void IWorld::AddComponents(const std::span<const Entity> entities, const std::span<T*> componentPointers)
	{
		AddComponents(entities, typeid(T), std::span(static_cast<void**>(componentPointers.data()), componentPointers.size()));
	}

	template<Component T>
	void IWorld::RemoveComponent(const Entity entity)
	{
		RemoveComponent(entity, typeid(T));
	}

	void IWorld::RemoveComponent(const Entity entity, const std::type_index componentType)
	{
		RemoveComponents(std::span(&entity, 1uz), componentType);
	}

	template<Component T>
	void IWorld::RemoveComponents(const std::span<const Entity> entities)
	{
		RemoveComponents(entities, typeid(T));
	}

	template<Component T>
	bool IWorld::HasComponent(const Entity entity) const
	{
		return HasComponent(entity, typeid(T));
	}

	bool IWorld::HasComponent(const Entity entity, const std::type_index componentType) const
	{
		return HasComponents(std::span(&entity, 1uz), componentType);
	}

	template<Component T>
	bool IWorld::HasComponents(const std::span<const Entity> entities) const
	{
		return HasComponents(entities, typeid(T));
	}

	template<Component T>
	void IWorld::HasComponents(const std::span<const Entity> entities, const std::span<bool> has) const
	{
		HasComponents(entities, typeid(T), has);
	}

	template<Component T>
	std::size_t IWorld::CountComponents() const
	{
		return CountComponents(typeid(T));
	}

	template<Component T>
	void IWorld::DropComponents()
	{
		DropComponents(typeid(T));
	}
}
