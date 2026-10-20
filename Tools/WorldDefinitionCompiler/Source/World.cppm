/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyTools.World;

import std;

export namespace PonyTools::World
{
	/// @brief World definition.
	class WorldDefinition final
	{
	public:
		[[nodiscard("Pure constructor")]]
		WorldDefinition() noexcept = default;
		[[nodiscard("Pure constructor")]]
		WorldDefinition(const WorldDefinition& other) = default;
		[[nodiscard("Pure constructor")]]
		WorldDefinition(WorldDefinition&& other) noexcept = default;

		~WorldDefinition() noexcept = default;

		/// @brief Gets the entity count.
		/// @return Entity count.
		[[nodiscard("Pure function")]]
		std::size_t EntityCount() const noexcept;
		/// @brief Gets an entity ID.
		/// @param index Entity index.
		/// @return Entity ID.
		[[nodiscard("Pure function")]]
		std::string_view EntityID(std::size_t index) const noexcept;

		/// @brief Gets the component table count.
		/// @return Component table count.
		[[nodiscard("Pure function")]]
		std::size_t ComponentTableCount() const noexcept;
		/// @brief Gets a component table type.
		/// @param tableIndex Table index.
		/// @return Component table type.
		[[nodiscard("Pure function")]]
		std::string_view ComponentType(std::size_t tableIndex) const noexcept;
		/// @brief Gets component table entity indices.
		/// @param tableIndex Table index.
		/// @return Component table entity indices.
		[[nodiscard("Pure function")]]
		std::span<const std::uint64_t> ComponentEntities(std::size_t tableIndex) const noexcept;
		/// @brief Gets a component table data.
		/// @param tableIndex Table index.
		/// @return Component table data.
		[[nodiscard("Pure function")]]
		std::vector<std::byte>& ComponentData(std::size_t tableIndex) noexcept;
		/// @brief Gets a component table data.
		/// @param tableIndex Table index.
		/// @return Component table data.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> ComponentData(std::size_t tableIndex) const noexcept;

		/// @brief Gets the object count.
		/// @return Object count.
		[[nodiscard("Pure function")]]
		std::size_t ObjectCount() const noexcept;
		/// @brief Gets an object ID.
		/// @param objectIndex Object index.
		/// @return Object ID.
		[[nodiscard("Pure function")]]
		std::string_view ObjectID(std::size_t objectIndex) const noexcept;
		/// @brief Gets an object type.
		/// @param objectIndex Object index.
		/// @return Object type.
		[[nodiscard("Pure function")]]
		std::string_view ObjectType(std::size_t objectIndex) const noexcept;
		/// @brief Gets an object type.
		/// @param objectIndex Object index.
		/// @return Object type.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> ObjectData(std::size_t objectIndex) const noexcept;

		/// @brief Adds the entity.
		/// @param entityId Entity ID.
		/// @return Entity index.
		std::uint64_t AddEntity(std::string_view entityId);
		/// @brief Adds a component.
		/// @param entityIndex Entity index.
		/// @param componentType Component type.
		/// @return Component table index.
		std::size_t AddComponent(std::uint64_t entityIndex, std::string_view componentType);
		/// @brief Adds the object.
		/// @param objectId Object ID.
		/// @param objectType Object type.
		/// @param objectData Object data.
		/// @return Object index.
		std::uint64_t AddObject(std::string_view objectId, std::string_view objectType, std::span<const std::byte> objectData);

		WorldDefinition& operator =(const WorldDefinition& other);
		WorldDefinition& operator =(WorldDefinition&& other) noexcept = default;

	private:
		/// @brief Component table.
		struct ComponentTable final
		{
			std::string type; ///< Component type.
			std::vector<std::uint64_t> entities; ///< Indices of entities that have a component of this table.
			std::vector<std::byte> data; ///< Component data.
		};
		/// @brief Object.
		struct Object final
		{
			std::string id; ///< Object ID.
			std::string type; ///< Object type.
			std::vector<std::byte> data; ///< Object data.
		};

		/// @brief Gets or creates a component table.
		/// @param componentType Component type.
		/// @return Component table index.
		[[nodiscard("Weird call")]]
		std::size_t GetOrCreateTable(std::string_view componentType);

		std::vector<std::string> entityIds; ///< Entity IDs.
		std::vector<ComponentTable> componentTables; ///< Component table.
		std::vector<Object> objects; ///< Objects.
	};
}

namespace PonyTools::World
{
	std::size_t WorldDefinition::EntityCount() const noexcept
	{
		return entityIds.size();
	}

	std::string_view WorldDefinition::EntityID(const std::size_t index) const noexcept
	{
		return entityIds[index];
	}

	std::size_t WorldDefinition::ComponentTableCount() const noexcept
	{
		return componentTables.size();
	}

	std::string_view WorldDefinition::ComponentType(const std::size_t tableIndex) const noexcept
	{
		return componentTables[tableIndex].type;
	}

	std::span<const std::uint64_t> WorldDefinition::ComponentEntities(const std::size_t tableIndex) const noexcept
	{
		return componentTables[tableIndex].entities;
	}

	std::vector<std::byte>& WorldDefinition::ComponentData(const std::size_t tableIndex) noexcept
	{
		return componentTables[tableIndex].data;
	}

	std::span<const std::byte> WorldDefinition::ComponentData(const std::size_t tableIndex) const noexcept
	{
		return componentTables[tableIndex].data;
	}

	std::size_t WorldDefinition::ObjectCount() const noexcept
	{
		return objects.size();
	}

	std::string_view WorldDefinition::ObjectID(const std::size_t objectIndex) const noexcept
	{
		return objects[objectIndex].id;
	}

	std::string_view WorldDefinition::ObjectType(const std::size_t objectIndex) const noexcept
	{
		return objects[objectIndex].type;
	}

	std::span<const std::byte> WorldDefinition::ObjectData(const std::size_t objectIndex) const noexcept
	{
		return objects[objectIndex].data;
	}

	std::uint64_t WorldDefinition::AddEntity(const std::string_view entityId)
	{
		if (std::ranges::contains(entityIds, entityId)) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Entity with the same id '{}' is already added", entityId));
		}

		if (entityIds.size() >= std::numeric_limits<std::uint64_t>::max()) [[unlikely]]
		{
			throw std::overflow_error("Too many entities");
		}

		entityIds.push_back(std::string(entityId));
		return static_cast<std::uint64_t>(entityIds.size() - 1uz);
	}

	std::size_t WorldDefinition::AddComponent(const std::uint64_t entityIndex, const std::string_view componentType)
	{
		std::size_t tableIndex = GetOrCreateTable(componentType);
		ComponentTable& table = componentTables[tableIndex];

		if (std::ranges::contains(table.entities, entityIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Entity already has component of this type");
		}

		table.entities.push_back(entityIndex);
		return tableIndex;
	}

	std::uint64_t WorldDefinition::AddObject(const std::string_view objectId, const std::string_view objectType, const std::span<const std::byte> objectData)
	{
		if (std::ranges::find_if(objects, [&](const Object& object) { return object.id == objectId; }) != objects.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Object with the same id is already added");
		}

		objects.push_back(Object{.id = std::string(objectId), .type = std::string(objectType), .data = std::vector(objectData.cbegin(), objectData.cend())});
		return static_cast<std::uint64_t>(objects.size() - 1uz);
	}

	std::size_t WorldDefinition::GetOrCreateTable(const std::string_view componentType)
	{
		const auto position = std::ranges::find_if(componentTables, [&](const ComponentTable& table) { return table.type == componentType; });
		const std::size_t index = position - componentTables.cbegin();
		if (index == componentTables.size())
		{
			componentTables.push_back(ComponentTable{.type = std::string(componentType)});
		}

		return index;
	}

	WorldDefinition& WorldDefinition::operator =(const WorldDefinition& other)
	{
		WorldDefinition definition = other;
		return *this = std::move(definition);
	}
}
