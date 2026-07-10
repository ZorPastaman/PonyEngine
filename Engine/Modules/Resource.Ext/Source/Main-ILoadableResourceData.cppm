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

export module PonyEngine.Resource.Ext:ILoadableResourceData;

import std;

import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	/// @brief Loadable resource data.
	class ILoadableResourceData
	{
		PONY_INTERFACE_BODY(ILoadableResourceData)

		/// @brief Gets the resource size.
		/// @return Resource size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
		/// @brief Loads a resource data.
		/// @param params Load parameters.
		/// @param callback Load callback. Can be nullptr. If it's not nullptr, it must be valid till the finish of the load operation.
		/// @return Load request. Must be kept alive till the finish of the load operation.
		/// @note The resource data object must be kep alive till the finish of the load operation as well.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback = nullptr) const = 0;
	};
}
