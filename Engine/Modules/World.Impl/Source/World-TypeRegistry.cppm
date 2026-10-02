/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Impl:TypeRegistry;

import std;

import PonyEngine.World;

import :ComponentTable;

export namespace PonyEngine::World
{
	/// @brief Type registry.
	class TypeRegistry final
	{
	public:
		[[nodiscard("Pure constructor")]]
		TypeRegistry() noexcept = default;
		TypeRegistry(const TypeRegistry&) = delete;
		TypeRegistry(TypeRegistry&&) = delete;

		~TypeRegistry() noexcept = default;

		/// @brief Adds the component type.
		/// @param componentType Component type.
		/// @param size Component size.
		/// @param alignment Component alignment.
		void AddComponentType(std::type_index componentType, std::size_t size, std::size_t alignment);
		/// @brief Registers the component object handle member.
		/// @param objectType Object type.
		/// @param componentType Component type.
		/// @param componentOffset Handle offset.
		void RegisterComponentObjectHandleMember(std::type_index objectType, std::type_index componentType, std::size_t componentOffset);
		/// @brief Registers an entity reference member.
		/// @param componentType Component type.
		/// @param componentOffset Entity reference member offset.
		void RegisterEntityReferenceMember(std::type_index componentType, std::size_t componentOffset);

		/// @brief Checks if the component type is valid.
		/// @param componentType Component type.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValidComponent(std::type_index componentType) const noexcept;
		/// @brief Gets the component size.
		/// @param componentType Component type.
		/// @return Component size.
		[[nodiscard("Pure function")]]
		std::size_t ComponentSize(std::type_index componentType) const noexcept;
		/// @brief Creates a component table.
		/// @param componentType Component type. Must be valid.
		/// @return Component table.
		[[nodiscard("Pure function")]]
		ComponentTable CreateComponentTable(std::type_index componentType) const;
		/// @brief Gets object handle offsets.
		/// @param componentType Component type.
		/// @return Offsets in the format <offset, object type>.
		/// @note Use @p Lock() if you access this function and keep it till you end working with the return value.
		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::size_t, std::type_index>> ObjectOffsets(std::type_index componentType) const noexcept;
		/// @brief Gets entity reference offsets.
		/// @param componentType Component type.
		/// @return Reference offsets.
		[[nodiscard("Pure function")]]
		std::span<const std::size_t> EntityReferences(std::type_index componentType) const noexcept;
		/// @brief Locks the registry.
		/// @return Registry lock.
		[[nodiscard("Pure function")]]
		std::shared_lock<std::shared_mutex> Lock() const noexcept;

		TypeRegistry& operator =(const TypeRegistry&) = delete;
		TypeRegistry& operator =(TypeRegistry&&) = delete;

	private:
		/// @brief Component info.
		struct ComponentInfo final
		{
			std::size_t size; ///< Component size.
			std::size_t alignment; ///< Component alignment.
		};

		std::unordered_map<std::type_index, ComponentInfo> components; ///< Component infos. <component type, info>.
		std::unordered_map<std::type_index, std::vector<std::pair<std::size_t, std::type_index>>> objectOffsets; /// Object offsets. <componentType, <offset, objectType>>.
		std::unordered_map<std::type_index, std::vector<std::size_t>> entityOffsets; ///< Entity offsets.
		mutable std::shared_mutex mutex; ///< Mutex.
	};
}

namespace PonyEngine::World
{
	void TypeRegistry::AddComponentType(const std::type_index componentType, const std::size_t size, const std::size_t alignment)
	{
		components[componentType] = ComponentInfo{.size = size, .alignment = alignment};
	}

	void TypeRegistry::RegisterComponentObjectHandleMember(const std::type_index objectType, const std::type_index componentType, const std::size_t componentOffset)
	{
		std::vector<std::pair<std::size_t, std::type_index>>& offsets = objectOffsets[componentType];

		std::size_t index = 0uz;
		for (; index < offsets.size() && offsets[index].first < componentOffset; ++index) // Sorting offsets
		{
		}

		if (index < offsets.size() && offsets[index].first == componentOffset)
		{
			return;
		}

		offsets.insert(offsets.cbegin() + index, std::pair(componentOffset, objectType));
	}

	void TypeRegistry::RegisterEntityReferenceMember(const std::type_index componentType, const std::size_t componentOffset)
	{
		std::vector<std::size_t>& offsets = entityOffsets[componentType];

		std::size_t index = 0uz;
		for (; index < offsets.size() && offsets[index] < componentOffset; ++index) // Sorting offsets
		{
		}

		if (index < offsets.size() && offsets[index] == componentOffset)
		{
			return;
		}

		offsets.insert(offsets.cbegin() + index, componentOffset);
	}

	bool TypeRegistry::IsValidComponent(const std::type_index componentType) const noexcept
	{
		return components.contains(componentType);
	}

	std::size_t TypeRegistry::ComponentSize(const std::type_index componentType) const noexcept
	{
		if (const auto position = components.find(componentType); position != components.cend()) [[likely]]
		{
			return position->second.size;
		}

		return 0uz;
	}

	ComponentTable TypeRegistry::CreateComponentTable(const std::type_index componentType) const
	{
		if (const auto position = components.find(componentType); position != components.cend()) [[likely]]
		{
			return ComponentTable(position->second.size, position->second.alignment);
		}

		throw std::invalid_argument("Component type is not registered");
	}

	std::span<const std::pair<std::size_t, std::type_index>> TypeRegistry::ObjectOffsets(const std::type_index componentType) const noexcept
	{
		if (const auto position = objectOffsets.find(componentType); position != objectOffsets.cend())
		{
			return position->second;
		}

		return std::span<const std::pair<std::size_t, std::type_index>>();
	}

	std::span<const std::size_t> TypeRegistry::EntityReferences(const std::type_index componentType) const noexcept
	{
		if (const auto position = entityOffsets.find(componentType); position != entityOffsets.cend())
		{
			return position->second;
		}

		return std::span<const std::size_t>();
	}

	std::shared_lock<std::shared_mutex> TypeRegistry::Lock() const noexcept
	{
		return std::shared_lock(mutex);
	}
}
