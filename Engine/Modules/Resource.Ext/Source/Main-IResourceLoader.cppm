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

import :IResourceLoadRequest;
import :ResourceLoadContext;
import :ResourceLoadInfo;
import :ResourceLoadData;

export namespace PonyEngine::Resource
{
	/// @brief Resource loader.
	class IResourceLoader
	{
		PONY_INTERFACE_BODY(IResourceLoader)

		/// @brief Prepares a resource.
		/// @param info Resource info.
		/// @param data Resource data.
		virtual void PrepareResource(const ResourceLoadInfo& info, ResourceLoadData& data) = 0;
		/// @brief Makes a load operation.
		/// @param context Resource load context.
		/// @param loadRequest Resource load request.
		virtual void Load(const ResourceLoadContext& context, const std::shared_ptr<IResourceLoadRequest>& loadRequest) = 0;
	};
}
