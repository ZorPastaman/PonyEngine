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
	/// @brief Component info.
	struct ComponentInfo final
	{
		std::size_t size = 0uz; ///< Component size.
		std::size_t alignment = 0uz; ///< Component alignment.
	};

	/// @brief Object handle info.
	struct ObjectHandleInfo final
	{
		std::type_index type; ///< Object type.
		std::size_t offset; ///< Handle offset.
		bool isConst; ///< Is an object const?
	};

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
		/// @param isConst Is an object const?
		/// @param componentType Component type.
		/// @param componentOffset Handle offset.
		void RegisterObjectHandleMember(std::type_index objectType, bool isConst, std::type_index componentType, std::size_t componentOffset);
		/// @brief Registers an entity reference member.
		/// @param componentType Component type.
		/// @param componentOffset Entity reference member offset.
		void RegisterEntityReferenceMember(std::type_index componentType, std::size_t componentOffset);

		/// @brief Checks if the component type is valid.
		/// @param componentType Component type.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValidComponent(std::type_index componentType) const noexcept;
		/// @brief Gets the component info.
		/// @param componentType Component type.
		/// @return Component info.
		[[nodiscard("Pure function")]]
		const ComponentInfo& GetComponentInfo(std::type_index componentType) const;
		/// @brief Creates a component table.
		/// @param componentType Component type. Must be valid.
		/// @return Component table.
		[[nodiscard("Pure function")]]
		ComponentTable CreateComponentTable(std::type_index componentType) const;
		/// @brief Gets object handle offsets.
		/// @param componentType Component type.
		/// @return Offsets in the format <offset, object type>.
		[[nodiscard("Pure function")]]
		std::span<const ObjectHandleInfo> GetObjectHandleInfos(std::type_index componentType) const noexcept;
		/// @brief Gets entity reference offsets.
		/// @param componentType Component type.
		/// @return Reference offsets.
		[[nodiscard("Pure function")]]
		std::span<const std::size_t> GetEntityReferences(std::type_index componentType) const noexcept;
		/// @brief Locks the registry via a unique lock.
		/// @return Registry lock.
		[[nodiscard("Pure function")]]
		std::unique_lock<std::shared_mutex> UniqueLock() noexcept;
		/// @brief Locks the registry via a shared lock.
		/// @return Registry lock.
		[[nodiscard("Pure function")]]
		std::shared_lock<std::shared_mutex> SharedLock() const noexcept;

		TypeRegistry& operator =(const TypeRegistry&) = delete;
		TypeRegistry& operator =(TypeRegistry&&) = delete;

	private:
		std::unordered_map<std::type_index, ComponentInfo> components; ///< Component infos.
		std::unordered_map<std::type_index, std::vector<ObjectHandleInfo>> objectHandles; /// Object handle infos.
		std::unordered_map<std::type_index, std::vector<std::size_t>> entityOffsets; ///< Entity offsets.
		mutable std::shared_mutex mutex; ///< Mutex.
	};
}

namespace PonyEngine::World
{
	void TypeRegistry::AddComponentType(const std::type_index componentType, const std::size_t size, const std::size_t alignment)
	{
		if (components.contains(componentType)) [[unlikely]]
		{
			throw std::logic_error("Component type is already registered");
		}

		components[componentType] = ComponentInfo{.size = size, .alignment = alignment};
	}

	void TypeRegistry::RegisterObjectHandleMember(const std::type_index objectType, const bool isConst, const std::type_index componentType, const std::size_t componentOffset)
	{
		std::vector<ObjectHandleInfo>& handleInfos = objectHandles[componentType];

		std::size_t index = 0uz;
		for (; index < handleInfos.size() && handleInfos[index].offset < componentOffset; ++index) // Sorting offsets
		{
		}

		if (index < handleInfos.size() && handleInfos[index].offset == componentOffset) [[unlikely]]
		{
			throw std::logic_error("Object handle member is already registered");
		}

		handleInfos.insert(handleInfos.cbegin() + index, ObjectHandleInfo{.type = objectType, .offset = componentOffset, .isConst = isConst});
	}

	void TypeRegistry::RegisterEntityReferenceMember(const std::type_index componentType, const std::size_t componentOffset)
	{
		std::vector<std::size_t>& offsets = entityOffsets[componentType];

		std::size_t index = 0uz;
		for (; index < offsets.size() && offsets[index] < componentOffset; ++index) // Sorting offsets
		{
		}

		if (index < offsets.size() && offsets[index] == componentOffset) [[unlikely]]
		{
			throw std::logic_error("Entity reference member is already registered");
		}

		offsets.insert(offsets.cbegin() + index, componentOffset);
	}

	bool TypeRegistry::IsValidComponent(const std::type_index componentType) const noexcept
	{
		return components.contains(componentType);
	}

	const ComponentInfo& TypeRegistry::GetComponentInfo(const std::type_index componentType) const
	{
		if (const auto position = components.find(componentType); position != components.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Component type is not registered");
	}

	ComponentTable TypeRegistry::CreateComponentTable(const std::type_index componentType) const
	{
		if (const auto position = components.find(componentType); position != components.cend()) [[likely]]
		{
			return ComponentTable(position->second.size, position->second.alignment);
		}

		throw std::invalid_argument("Component type is not registered");
	}

	std::span<const ObjectHandleInfo> TypeRegistry::GetObjectHandleInfos(const std::type_index componentType) const noexcept
	{
		if (const auto position = objectHandles.find(componentType); position != objectHandles.cend())
		{
			return position->second;
		}

		return std::span<const ObjectHandleInfo>();
	}

	std::span<const std::size_t> TypeRegistry::GetEntityReferences(const std::type_index componentType) const noexcept
	{
		if (const auto position = entityOffsets.find(componentType); position != entityOffsets.cend())
		{
			return position->second;
		}

		return std::span<const std::size_t>();
	}

	std::unique_lock<std::shared_mutex> TypeRegistry::UniqueLock() noexcept
	{
		return std::unique_lock(mutex);
	}

	std::shared_lock<std::shared_mutex> TypeRegistry::SharedLock() const noexcept
	{
		return std::shared_lock(mutex);
	}
}
