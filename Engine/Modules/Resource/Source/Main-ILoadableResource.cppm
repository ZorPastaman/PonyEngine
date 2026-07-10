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

export module PonyEngine.Resource:ILoadableResource;

import std;

import :ILoadRequest;
import :IResource;
import :LoadParams;

export namespace PonyEngine::Resource
{
	/// @brief Loadable resource.
	/// @details It can be anything. It just guarantees that it can read resource bytes.
	class ILoadableResource : public IResource
	{
		PONY_INTERFACE_BODY(ILoadableResource)

		/// @brief Gets the resource size.
		/// @return Resource size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
		/// @brief Loads a resource data.
		/// @param params Load parameters.
		/// @param callback Load callback. Can be nullptr. If it's not nullptr, it must be valid till the finish of the load operation.
		/// @return Load request. Must be kept alive till the finish of the load operation.
		/// @remark The callback may be called on a separate thread or on the thread this function was called on if the request is completed immediately.
		/// @remark The callback may be called before this function returns.
		/// @remark The callback mustn't do expensive operations, it should return as fast as possible. If you need to parse data or something else, do it on another thread.
		/// @note The resource object must be kep alive till the finish of the load operation as well.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback = nullptr) const = 0;
	};
}
