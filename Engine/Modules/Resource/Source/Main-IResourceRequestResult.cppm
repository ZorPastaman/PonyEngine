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

export module PonyEngine.Resource:IResourceRequestResult;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource request result.
	class IResourceRequestResult
	{
		PONY_INTERFACE_BODY(IResourceRequestResult)

		/// @brief Checks whether the resource is of type @p type.
		/// @param type The resource type to check against.
		/// @return @a true if the resource is of the specified type; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsTypeOf(std::type_index type) const noexcept;
		/// @brief Checks whether the resource is of types @p types.
		/// @param types The resource types to check against.
		/// @return @a true if the resource is of the specified types; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept = 0;
		/// @brief Checks whether the resource is of types @p Args.
		/// @tparam Args The resource types to check against.
		/// @return @a true if the resource is of the specified types; @a false otherwise.
		template<typename... Args> [[nodiscard("Pure function")]]
		bool IsTypeOf() const noexcept;

		/// @brief Gets a resource.
		/// @param type Resource type. Must be one of the resource types.
		/// @return Resource.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const void> Resource(std::type_index type) const = 0;
		/// @brief Gets a resource.
		/// @tparam T Resource type. Must be one of the resource types.
		/// @return Resource.
		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<const T> Resource() const;
	};
}

namespace PonyEngine::Resource
{
	bool IResourceRequestResult::IsTypeOf(const std::type_index type) const noexcept
	{
		return IsTypeOf(std::span(&type, 1uz));
	}

	template<typename... Args>
	bool IResourceRequestResult::IsTypeOf() const noexcept
	{
		return IsTypeOf(std::array<std::type_index, sizeof...(Args)>{typeid(Args)...});
	}

	template<typename T>
	std::shared_ptr<const T> IResourceRequestResult::Resource() const
	{
		return std::static_pointer_cast<const T>(Resource(typeid(T)));
	}
}
