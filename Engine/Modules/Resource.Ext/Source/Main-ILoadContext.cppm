/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.Ext:ILoadContext;

import std;

import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Load context.
	class ILoadContext
	{
		PONY_INTERFACE_BODY(ILoadContext)

		/// @brief Gets a resource data access.
		/// @return Resource data access.
		[[nodiscard("Pure function")]]
		virtual void* ResourceDataAccess() const noexcept = 0;
		/// @brief Gets a type of an object returned from @p ResourceDataAccess().
		/// @return Resource data access type.
		[[nodiscard("Pure function")]]
		virtual std::type_index ResourceDataAccessType() const noexcept = 0;

		/// @brief Gets a resource type.
		/// @return Resource type.
		[[nodiscard("Pure function")]]
		virtual ResourceType ResourceType() const noexcept = 0;

		/// @brief Gets a load data count.
		/// @return Load data count.
		[[nodiscard("Pure function")]]
		virtual std::size_t LoadDataCount() const noexcept = 0;
		/// @brief Gets a load data.
		/// @param index Load data index. Must be less than @p LoadDataCount().
		/// @return Load data.
		[[nodiscard("Pure function")]]
		virtual const void* LoadData(std::size_t index) const noexcept = 0;
		/// @brief Gets a load data type.
		/// @param index Load data index. Must be less than @p LoadDataCount().
		/// @return Load data type.
		[[nodiscard("Pure function")]]
		virtual std::type_index LoadDataType(std::size_t index) const noexcept = 0;

		/// @brief Gets interface types.
		/// @return Interface types.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> InterfaceTypes() const noexcept = 0;
	};
}
