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
		virtual std::span<const Entity> Entities() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(Entity entity) const noexcept = 0;
		[[nodiscard("Wierd call")]]
		virtual Entity CreateEntity() = 0;
		virtual void DestroyEntity(Entity entity) = 0;
		[[nodiscard("Pure function")]]
		virtual bool AreValid(std::span<const Entity> entities) const = 0;
		virtual void AreValid(std::span<const Entity> entities, std::span<bool> valid) const = 0;
		virtual void CreateEntities(std::span<Entity> entities) = 0;
		virtual void DestroyEntities(std::span<const Entity> entities) = 0;

		template<Component T>
		void AddComponent(Entity entity, const T& component = T{});
		virtual void AddComponent(Entity entity, std::type_index componentType, const void* componentData) = 0;
		template<Component T>
		T& AddComponent(Entity entity);
		virtual void* AddComponent(Entity entity, std::type_index componentType) = 0;
		template<Component T>
		void AddComponents(std::span<const Entity> entities, std::span<const T> components);
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, const void* componentData) = 0;
		template<Component T>
		void AddComponents(std::span<const Entity> entities, std::span<T*> componentPointers);
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, std::span<void*> componentPointers) = 0;

		template<Component T>
		void RemoveComponent(Entity entity);
		virtual void RemoveComponent(Entity entity, std::type_index componentType) = 0;
		template<Component T>
		void RemoveComponents(std::span<const Entity> entities);
		virtual void RemoveComponents(std::span<const Entity> entities, std::type_index componentType) = 0;

		template<Tag T>
		void AddTag(Entity entity);
		virtual void AddTag(Entity entity, std::type_index tagType) = 0;
		template<Tag T>
		void AddTags(std::span<const Entity> entities);
		virtual void AddTags(std::span<const Entity> entities, std::type_index tagType) = 0;

		template<Tag T>
		void RemoveTag(Entity entity);
		virtual void RemoveTag(Entity entity, std::type_index tagType) = 0;
		template<Tag T>
		void RemoveTags(std::span<const Entity> entities);
		virtual void RemoveTags(std::span<const Entity> entities, std::type_index tagType) = 0;

		template<Component T> [[nodiscard("Pure function")]]
		bool HasComponent(Entity entity) const;
		[[nodiscard("Pure function")]]
		virtual bool HasComponent(Entity entity, std::type_index componentType) const = 0;
		template<Component T> [[nodiscard("Pure function")]]
		bool HasComponents(std::span<const Entity> entities) const;
		[[nodiscard("Pure function")]]
		virtual bool HasComponents(std::span<const Entity> entities, std::type_index componentType) const = 0;
		template<Component T>
		void HasComponents(std::span<const Entity> entities, std::span<bool> has) const;
		virtual void HasComponents(std::span<const Entity> entities, std::type_index componentType, std::span<bool> has) const = 0;

		template<Tag T> [[nodiscard("Pure function")]]
		bool HasTag(Entity entity) const;
		[[nodiscard("Pure function")]]
		virtual bool HasTag(Entity entity, std::type_index tagType) const = 0;
		template<Tag T> [[nodiscard("Pure function")]]
		bool HasTags(std::span<const Entity> entities) const;
		[[nodiscard("Pure function")]]
		virtual bool HasTags(std::span<const Entity> entities, std::type_index tagType) const = 0;
		template<Tag T>
		void HasTags(std::span<const Entity> entities, std::span<bool> has) const;
		virtual void HasTags(std::span<const Entity> entities, std::type_index tagType, std::span<bool> has) const = 0;

		template<Component T> [[nodiscard("Pure function")]]
		std::size_t CountComponents() const;
		[[nodiscard("Pure function")]]
		virtual std::size_t CountComponents(std::type_index componentType) const = 0;

		template<Tag T> [[nodiscard("Pure function")]]
		std::size_t CountTags() const;
		[[nodiscard("Pure function")]]
		virtual std::size_t CountTags(std::type_index tagType) const = 0;

		template<Component T>
		void DropComponents();
		virtual void DropComponents(std::type_index componentType) = 0;

		template<Tag T>
		void DropTags();
		virtual void DropTags(std::type_index tagType) = 0;

		[[nodiscard("Pure function")]]
		virtual std::size_t CountQuery(const QueryParams& params) const = 0;
		virtual void Query(const QueryParams& params, const std::function<void(QueryItem&)>& callback) const = 0;
	};
}

namespace PonyEngine::World
{
	template<Component T>
	void IWorld::AddComponent(const Entity entity, const T& component)
	{
		AddComponent(entity, typeid(T), &component);
	}

	template<Component T>
	T& IWorld::AddComponent(const Entity entity)
	{
		return *static_cast<T*>(AddComponent(entity, typeid(T)));
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

	template<Component T>
	void IWorld::RemoveComponents(const std::span<const Entity> entities)
	{
		RemoveComponents(entities, typeid(T));
	}

	template<Tag T>
	void IWorld::AddTag(const Entity entity)
	{
		AddTag(entity, typeid(T));
	}

	template<Tag T>
	void IWorld::AddTags(const std::span<const Entity> entities)
	{
		AddTags(entities, typeid(T));
	}

	template<Tag T>
	void IWorld::RemoveTag(const Entity entity)
	{
		RemoveTag(entity, typeid(T));
	}

	template<Tag T>
	void IWorld::RemoveTags(const std::span<const Entity> entities)
	{
		RemoveTags(entities, typeid(T));
	}

	template<Component T>
	bool IWorld::HasComponent(const Entity entity) const
	{
		return HasComponent(entity, typeid(T));
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

	template<Tag T>
	bool IWorld::HasTag(const Entity entity) const
	{
		return HasTag(entity, typeid(T));
	}

	template<Tag T>
	bool IWorld::HasTags(const std::span<const Entity> entities) const
	{
		return HasTags(entities, typeid(T));
	}

	template<Tag T>
	void IWorld::HasTags(const std::span<const Entity> entities, const std::span<bool> has) const
	{
		HasTags(entities, typeid(T), has);
	}

	template<Component T>
	std::size_t IWorld::CountComponents() const
	{
		return CountComponents(typeid(T));
	}

	template<Tag T>
	std::size_t IWorld::CountTags() const
	{
		return CountTags(typeid(T));
	}

	template<Component T>
	void IWorld::DropComponents()
	{
		DropComponents(typeid(T));
	}

	template<Tag T>
	void IWorld::DropTags()
	{
		DropTags(typeid(T));
	}
}
