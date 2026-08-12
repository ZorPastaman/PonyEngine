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
import :IResourceLoadHandler;
import :IResourceLoadRequest;
import :ResourceLoadContext;

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
		/// @param context Resource load context.
		/// @param loadHandler Resource load handler. Must be kept alive till the end of the request.
		/// @return Resource load request.
		[[nodiscard("Weird call")]]
		virtual std::shared_ptr<IResourceLoadRequest> Load(const ResourceLoadContext& context, IResourceLoadHandler& loadHandler) = 0;
	};
}
