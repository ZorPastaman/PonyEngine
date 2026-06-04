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
import :ObjectHandle;
import :QueryParams;

export namespace PonyEngine::World
{
	/// @brief World. Contains entities and their components.
	/// @note All read operations are thread-safe but write operations are not.
	class IWorld
	{
		PONY_INTERFACE_BODY(IWorld)

		/// @brief Gets an entity count.
		/// @return Entity count.
		[[nodiscard("Pure function")]]
		virtual std::size_t EntityCount() const noexcept = 0;
		/// @brief Gets all the entities.
		/// @param entities Entities.
		/// @return Count of entities written to the @p entities.
		/// @note If the world has more entities than the @p entities size, only @p entities.size() first entities will be written.
		virtual std::size_t GetEntities(std::span<Entity> entities) const noexcept = 0;
		/// @brief Checks if the @p entity is valid.
		/// @param entity Entity to check.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValid(Entity entity) const noexcept;
		/// @brief Creates a new entity.
		/// @return New entity.
		[[nodiscard("Weird call")]]
		Entity CreateEntity();
		/// @brief Destroys the entity.
		/// @param entity Entity to destroy. Must be valid.
		void DestroyEntity(Entity entity);
		/// @brief Checks if all the entities are valid.
		/// @param entities Entities to check.
		/// @return @a True if all the entities are valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool AreValid(std::span<const Entity> entities) const noexcept = 0;
		/// @brief Checks if the entities are valid.
		/// @param entities Entities to check.
		/// @param valid Entity validity. @a True if an entity is valid; @a false otherwise. 
		///              Synced with the @p entities by index. Its size must be the same as the size of the @p entities.
		virtual void AreValid(std::span<const Entity> entities, std::span<bool> valid) const = 0;
		/// @brief Creates new entities.
		/// @param entities New entities. Its size defines how many entities to create.
		virtual void CreateEntities(std::span<Entity> entities) = 0;
		/// @brief Destroys the entities.
		/// @param entities Entities to destroy. Must be valid.
		virtual void DestroyEntities(std::span<const Entity> entities) = 0;

		/// @brief Adds a component to the @p entity and initializes it with the @p componentData.
		/// @tparam T Component type.
		/// @param entity Entity. Must be valid.
		/// @param componentData Component data.
		template<Component T>
		void AddComponent(Entity entity, const T& componentData);
		/// @brief Adds a component to the @p entity and initializes it with the @p componentData.
		/// @param entity Entity. Must be valid.
		/// @param componentType Component type.
		/// @param componentData Component data.
		void AddComponent(Entity entity, std::type_index componentType, const void* componentData);
		/// @brief Adds a component to the @p entity but doesn't initialize it.
		/// @tparam T Component type.
		/// @param entity Entity. Must be valid.
		/// @return Component data.
		template<Component T>
		T& AddComponent(Entity entity);
		/// @brief Adds a component to the @p entity but doesn't initialize it.
		/// @param entity Entity. Must be valid.
		/// @param componentType Component type.
		/// @return Component data.
		void* AddComponent(Entity entity, std::type_index componentType);
		/// @brief Adds components to the @p entities but doesn't initialize it.
		/// @tparam T Component type.
		/// @param entities Entities. Must be valid.
		template<Component T>
		void AddComponents(std::span<const Entity> entities);
		/// @brief Adds components to the @p entities but doesn't initialize it.
		/// @param entities Entities. Must be valid.
		/// @param componentType Component type.
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType) = 0;
		/// @brief Adds components to the @p entities and initializes them with the @p componentData.
		/// @tparam T Component type.
		/// @param entities Entities. Must be valid.
		/// @param componentData Component data. Synced with the @p entities by index. Its size must be the same as the size of the @p entities.
		template<Component T>
		void AddComponents(std::span<const Entity> entities, std::span<const T> componentData);
		/// @brief Adds components to the @p entities and initializes them with the @p componentData.
		/// @param entities Entities. Must be valid.
		/// @param componentType Component type.
		/// @param componentData Component data. Must be a contiguous array of all the components synced with the @p entities by index.
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, const void* componentData) = 0;
		/// @brief Adds components to the @p entities but doesn't initialize them.
		/// @tparam T Component type.
		/// @param entities Entities. Must be valid.
		/// @param componentData Component data. Synced with the @p entities by index.
		template<Component T>
		void AddComponents(std::span<const Entity> entities, std::span<T*> componentData);
		/// @brief Adds components to the @p entities but doesn't initialize them.
		/// @param entities Entities. Must be valid.
		/// @param componentType Component type.
		/// @param componentData Component data. Synced with the @p entities by index.
		virtual void AddComponents(std::span<const Entity> entities, std::type_index componentType, std::span<void*> componentData) = 0;

		/// @brief Removes a component from the entity.
		/// @tparam T Component type.
		/// @param entity Entity. Must be valid.
		template<Component T>
		void RemoveComponent(Entity entity);
		/// @brief Removes a component from the entity.
		/// @param entity Entity. Must be valid.
		/// @param componentType Component type.
		void RemoveComponent(Entity entity, std::type_index componentType);
		/// @brief Removes components from the entities.
		/// @tparam T Component type.
		/// @param entities Entities. Must be valid.
		template<Component T>
		void RemoveComponents(std::span<const Entity> entities);
		/// @brief Removes components from the entities.
		/// @param entities Entities. Must be valid.
		/// @param componentType Component type.
		virtual void RemoveComponents(std::span<const Entity> entities, std::type_index componentType) = 0;

		/// @brief Checks if the entity has a component.
		/// @tparam T Component type.
		/// @param entity Entity. Must be valid.
		/// @return @a True if it has; @p false otherwise.
		template<Component T> [[nodiscard("Pure function")]]
		bool HasComponent(Entity entity) const;
		/// @brief Checks if the entity has a component.
		/// @param entity Entity. Must be valid.
		/// @param componentType Component type.
		/// @return @a True if it has; @p false otherwise.
		[[nodiscard("Pure function")]]
		bool HasComponent(Entity entity, std::type_index componentType) const;
		/// @brief Checks if all the entities have components.
		/// @tparam T Component type.
		/// @param entities Entities. Must be valid.
		/// @return @a True if they have; @p false otherwise.
		template<Component T> [[nodiscard("Pure function")]]
		bool HasComponents(std::span<const Entity> entities) const;
		/// @brief Checks if all the entities have components.
		/// @param entities Entities. Must be valid.
		/// @param componentType Component type.
		/// @return @a True if they have; @p false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool HasComponents(std::span<const Entity> entities, std::type_index componentType) const = 0;
		/// @brief Checks if the entities have components.
		/// @tparam T Component type.
		/// @param entities Entities. Must be valid.
		/// @param has Has flags. @a True if an entity has a component; @a false otherwise.
		///            Synced with the @p entities by index. Its size must be the same as the size of the @p entities.
		template<Component T>
		void HasComponents(std::span<const Entity> entities, std::span<bool> has) const;
		/// @brief Checks if the entities have components.
		/// @param entities Entities. Must be valid.
		/// @param componentType Component type.
		/// @param has Has flags. @a True if an entity has a component; @a false otherwise.
		///            Synced with the @p entities by index. Its size must be the same as the size of the @p entities.
		virtual void HasComponents(std::span<const Entity> entities, std::type_index componentType, std::span<bool> has) const = 0;

		/// @brief Gets a component table size.
		/// @tparam T Component type.
		/// @return Component table size.
		template<Component T> [[nodiscard("Pure function")]]
		std::size_t CountComponents() const;
		/// @brief Gets a component table size.
		/// @param componentType Component type.
		/// @return Component table size.
		[[nodiscard("Pure function")]]
		virtual std::size_t CountComponents(std::type_index componentType) const = 0;

		/// @brief Gets all the entities that have a component of type @p T.
		/// @tparam T Component type.
		/// @param entities Entities.
		/// @return Count of entities written to the @p entities.
		/// @note If the world has more entities than the @p entities size, only @p entities.size() first entities will be written.
		template<Component T>
		std::size_t GetEntities(std::span<Entity> entities) const;
		/// @brief Gets all the entities that have a component of type @p componentType.
		/// @param componentType Component type.
		/// @param entities Entities.
		/// @return Count of entities written to the @p entities.
		/// @note If the world has more entities than the @p entities size, only @p entities.size() first entities will be written.
		virtual std::size_t GetEntities(std::type_index componentType, std::span<Entity> entities) const = 0;
		/// @brief Gets all the components of type @p T.
		/// @tparam T Component type.
		/// @param componentData Component data.
		/// @return Count of components written to the @p componentData.
		/// @note If the world has more components than the @p componentData size, only @p componentData.size() first components will be written.
		template<Component T>
		std::size_t GetComponents(std::span<T*> componentData) const;
		/// @brief Gets all the components of type @p componentType.
		/// @param componentType Component type.
		/// @param componentData Component data.
		/// @return Count of components written to the @p componentData.
		/// @note If the world has more components than the @p componentData size, only @p componentData.size() first components will be written.
		virtual std::size_t GetComponents(std::type_index componentType, std::span<void*> componentData) const = 0;
		/// @brief Gets all the entities and components of type @p T.
		/// @tparam T Component type.
		/// @param entities Entities.
		/// @param componentData Component data. Its size must be synced with the @p entities.
		/// @return Count of entities written to the @p entities.
		/// @note If the world has more entities than the @p entities size, only @p entities.size() first entities will be written.
		template<Component T>
		std::size_t GetEntitiesAndComponents(std::span<Entity> entities, std::span<T*> componentData) const;
		/// @brief Gets all the entities and components of type @p componentType.
		/// @param componentType Component type.
		/// @param entities Entities.
		/// @param componentData Component data. Its size must be synced with the @p entities.
		/// @return Count of entities written to the @p entities.
		/// @note If the world has more entities than the @p entities size, only @p entities.size() first entities will be written.
		virtual std::size_t GetEntitiesAndComponents(std::type_index componentType, std::span<Entity> entities, std::span<void*> componentData) const = 0;

		/// @brief Removes all the components of the type @p T.
		/// @tparam T Component type.
		template<Component T>
		void DropComponents();
		/// @brief Removes all the components of the type @p componentType.
		/// @param componentType Component type.
		virtual void DropComponents(std::type_index componentType) = 0;

		/// @brief Calculates the maximum possible number of entities that may satisfy the specified query.
		/// @param params Query parameters.
		/// @return Maximum possible number of entities.
		[[nodiscard("Pure function")]]
		virtual std::size_t CountQuery(const QueryParams& params) const = 0;
		/// @brief Runs the entity query.
		/// @param params Query parameters.
		/// @param callback Query callback. It's called on each entity that satisfies the query parameters.
		virtual void Query(const QueryParams& params, const std::function<void(QueryItem&)>& callback) const = 0;

		/// @brief Registers the object.
		/// @tparam T Object type.
		/// @param object Object.
		/// @return Object handle.
		/// @remark If the object is already registered, its current handle is returned.
		template<typename T> [[nodiscard("Weird call")]]
		ObjectHandle<T> RegisterObject(const std::shared_ptr<T>& object);
		/// @brief Unregisters an object.
		/// @tparam T Object type.
		/// @param handle Object handle. Must be valid.
		template<typename T>
		void UnregisterObject(ObjectHandle<T> handle);
		/// @brief Replaces a registered object.
		/// @tparam T Object type.
		/// @param handle Object handle. Must be valid.
		/// @param object Replacement object.
		template<typename T>
		void ReplaceObject(ObjectHandle<T> handle, const std::shared_ptr<T>& object);

		/// @brief Checks if the object handle is valid.
		/// @tparam T Object type.
		/// @param handle Object handle.
		/// @return @a True if it's valid; @a false otherwise.
		template<typename T> [[nodiscard("Pure function")]]
		bool IsObjectValid(ObjectHandle<T> handle) const noexcept;
		/// @brief Gets an object pointer.
		/// @tparam T Object type.
		/// @param handle Object handle. Must be valid.
		/// @return Object pointer.
		template<typename T> [[nodiscard("Pure function")]]
		T* GetObject(ObjectHandle<T> handle) const;
		/// @brief Gets an object shared pointer.
		/// @tparam T Object type.
		/// @param handle Object handle. Must be valid.
		/// @return Object shared pointer.
		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<T> GetSharedObject(ObjectHandle<T> handle) const;

		/// @brief Collects garbage objects and removes them.
		virtual void CollectGarbage() = 0;

	protected:
		/// @brief Registers the object.
		/// @param objectType Object type.
		/// @param object Object.
		/// @return Object handle.
		[[nodiscard("Weird call")]]
		virtual TypelessObjectHandle RegisterObject(std::type_index objectType, const std::shared_ptr<void>& object) = 0;
		/// @brief Unregisters an object.
		/// @param objectType Object type.
		/// @param handle Object handle. Must be valid.
		virtual void UnregisterObject(std::type_index objectType, TypelessObjectHandle handle) = 0;
		/// @brief Replaces a registered object.
		/// @param handle Object handle. Must be valid.
		/// @param objectType Object type.
		/// @param object Replacement object.
		virtual void ReplaceObject(TypelessObjectHandle handle, std::type_index objectType, const std::shared_ptr<void>& object) = 0;

		/// @brief Checks if the object handle is valid.
		/// @param objectType Object type.
		/// @param handle Object handle.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsObjectValid(std::type_index objectType, TypelessObjectHandle handle) const noexcept = 0;
		/// @brief Gets an object.
		/// @param objectType Object type.
		/// @param handle Object handle. Must be valid.
		/// @return Object.
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<void>& GetObject(std::type_index objectType, TypelessObjectHandle handle) const = 0;
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
	void IWorld::AddComponent(const Entity entity, const T& componentData)
	{
		AddComponent(entity, typeid(T), &componentData);
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
	void IWorld::AddComponents(const std::span<const Entity> entities, const std::span<const T> componentData)
	{
#ifndef NDEBUG
		if (entities.size() != componentData.size()) [[unlikely]]
		{
			throw std::invalid_argument("Entity and component span sizes are mismatched");
		}
#endif

		AddComponents(entities, typeid(T), componentData.data());
	}

	template<Component T>
	void IWorld::AddComponents(const std::span<const Entity> entities, const std::span<T*> componentData)
	{
		AddComponents(entities, typeid(T), std::span(reinterpret_cast<void**>(componentData.data()), componentData.size()));
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
	std::size_t IWorld::GetEntities(const std::span<Entity> entities) const
	{
		return GetEntities(typeid(T), entities);
	}

	template<Component T>
	std::size_t IWorld::GetComponents(const std::span<T*> componentData) const
	{
		return GetComponents(typeid(T), std::span(reinterpret_cast<void**>(componentData.data()), componentData.size()));
	}

	template<Component T>
	std::size_t IWorld::GetEntitiesAndComponents(const std::span<Entity> entities, const std::span<T*> componentData) const
	{
		return GetEntitiesAndComponents(typeid(T), entities, std::span(reinterpret_cast<void**>(componentData.data()), componentData.size()));
	}

	template<Component T>
	void IWorld::DropComponents()
	{
		DropComponents(typeid(T));
	}

	template<typename T>
	ObjectHandle<T> IWorld::RegisterObject(const std::shared_ptr<T>& object)
	{
		return ObjectHandle<T>{.typeless = RegisterObject(typeid(T), object)};
	}

	template<typename T>
	void IWorld::UnregisterObject(const ObjectHandle<T> handle)
	{
		UnregisterObject(typeid(T), handle.typeless);
	}

	template<typename T>
	void IWorld::ReplaceObject(const ObjectHandle<T> handle, const std::shared_ptr<T>& object)
	{
		ReplaceObject(handle.typeless, typeid(T), object);
	}

	template<typename T>
	bool IWorld::IsObjectValid(const ObjectHandle<T> handle) const noexcept
	{
		return IsObjectValid(typeid(T), handle.typeless);
	}

	template<typename T>
	T* IWorld::GetObject(const ObjectHandle<T> handle) const
	{
		return static_cast<T*>(GetObject(typeid(T), handle.typeless).get());
	}

	template<typename T>
	std::shared_ptr<T> IWorld::GetSharedObject(const ObjectHandle<T> handle) const
	{
		return std::static_pointer_cast<T>(GetObject(typeid(T), handle.typeless));
	}
}
