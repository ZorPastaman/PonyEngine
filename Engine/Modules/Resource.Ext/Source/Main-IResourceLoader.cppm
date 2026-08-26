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

export module PonyEngine.Resource.Ext:IResourceLoader;

import std;

import PonyEngine.Resource;

import :ILoadableResource;
import :ILoadContext;
import :IResourceLoadRequest;

export namespace PonyEngine::Resource
{
	/// @brief Resource loader.
	class IResourceLoader
	{
		PONY_INTERFACE_BODY(IResourceLoader)

		/// @brief Prepares a resource.
		/// @param context Resource context.
		virtual void PrepareResource(ILoadableResource& context) = 0;
		/// @brief Makes a load request.
		/// @param context Load context.
		/// @param callback Callback. May be nullptr.
		/// @return Resource load request.
		/// @note The context, request, callback and loader must be kept alive till the finish of the operation.
		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IResourceLoadRequest> Load(ILoadContext& context, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback = nullptr) = 0;
	};
}
