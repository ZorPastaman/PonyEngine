/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Resource.Impl:Utility;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Checks if all the required types are provided.
	/// @param required Required types.
	/// @param provided Provided types.
	/// @return @a True if all the required types are provided; @a false otherwise.
	[[nodiscard("Pure function")]]
	bool CheckTypes(std::span<const std::type_index> required, std::span<const std::type_index> provided) noexcept;
	/// @brief Makes a resource of the required type.
	/// @param type Required type.
	/// @param interfaceTypes Interface types.
	/// @param interfaces Interfaces. Must be synced with the @p interfaceTypes by index.
	/// @param resource Resource.
	/// @return Resource of the required type.
	[[nodiscard("Pure function")]]
	std::shared_ptr<const void> MakeResource(std::type_index type, std::span<const std::type_index> interfaceTypes, std::span<const void* const> interfaces, 
		const std::shared_ptr<const void>& resource);
}

namespace PonyEngine::Resource
{
	bool CheckTypes(const std::span<const std::type_index> required, const std::span<const std::type_index> provided) noexcept
	{
		for (const std::type_index type : required)
		{
			if (!std::ranges::contains(provided, type))
			{
				return false;
			}
		}

		return true;
	}

	std::shared_ptr<const void> MakeResource(const std::type_index type, const std::span<const std::type_index> interfaceTypes, 
		const std::span<const void* const> interfaces, const std::shared_ptr<const void>& resource)
	{
		assert(interfaceTypes.size() == interfaces.size() && "Interfaces and interface types sizes mismatched.");
		assert(resource && "Resource is nullptr.");

		const std::size_t index = std::ranges::find(interfaceTypes, type) - interfaceTypes.cbegin();
		if (index >= interfaceTypes.size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid type");
		}

		return std::shared_ptr<const void>(resource, interfaces[index]);
	}
}
