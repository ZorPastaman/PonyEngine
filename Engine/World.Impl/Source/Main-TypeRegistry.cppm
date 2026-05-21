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
import :TagTable;

export namespace PonyEngine::World
{
	class TypeRegistry final
	{
	public:
		[[nodiscard("Pure constructor")]]
		TypeRegistry() noexcept = default;
		TypeRegistry(const TypeRegistry&) = delete;
		[[nodiscard("Pure constructor")]]
		TypeRegistry(TypeRegistry&& other) noexcept = default;

		~TypeRegistry() noexcept = default;

		void AddComponentType(std::type_index componentType, std::size_t size, std::size_t alignment);
		void AddTagType(std::type_index tagType);

		[[nodiscard("Pure function")]]
		bool IsValidComponent(std::type_index componentType) const noexcept;
		[[nodiscard("Pure function")]]
		ComponentTable CreateComponentTable(std::type_index componentType) const;
		[[nodiscard("Pure function")]]
		bool IsValidTag(std::type_index tagType) const noexcept;
		[[nodiscard("Pure function")]]
		TagTable CreateTagTable(std::type_index tagType) const;

		TypeRegistry& operator =(const TypeRegistry&) = delete;
		TypeRegistry& operator =(TypeRegistry&& other) noexcept = default;

	private:
		struct ComponentInfo final
		{
			std::size_t size;
			std::size_t alignment;
		};

		std::unordered_map<std::type_index, ComponentInfo> components;
		std::unordered_set<std::type_index> tags;
	};
}

namespace PonyEngine::World
{
	void TypeRegistry::AddComponentType(const std::type_index componentType, const std::size_t size, const std::size_t alignment)
	{
		components[componentType] = ComponentInfo{.size = size, .alignment = std::max(alignment, alignof(std::max_align_t))};
	}

	void TypeRegistry::AddTagType(const std::type_index tagType)
	{
		tags.insert(tagType);
	}

	bool TypeRegistry::IsValidComponent(const std::type_index componentType) const noexcept
	{
		return components.contains(componentType);
	}

	ComponentTable TypeRegistry::CreateComponentTable(const std::type_index componentType) const
	{
		if (const auto position = components.find(componentType); position != components.cend()) [[likely]]
		{
			return ComponentTable(position->second.size, position->second.alignment);
		}

		throw std::invalid_argument("Component type is not registered");
	}

	bool TypeRegistry::IsValidTag(const std::type_index tagType) const noexcept
	{
		return tags.contains(tagType);
	}

	TagTable TypeRegistry::CreateTagTable(const std::type_index tagType) const
	{
		if (!IsValidTag(tagType)) [[unlikely]]
		{
			throw std::invalid_argument("Tag type is not registered");
		}

		return TagTable();
	}
}
