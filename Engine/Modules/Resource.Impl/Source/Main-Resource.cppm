/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:Resource;

import std;

import PonyEngine.Resource.Ext;

import :ResourceData;
import :ResourceInfo;
import :ResourceLoadHandler;

export namespace PonyEngine::Resource
{
	struct Resource final
	{
		std::shared_ptr<const ResourceInfo> info;
		std::shared_ptr<ResourceData> data;
		std::weak_ptr<ResourceLoadHandler> loadHandler;
		std::shared_ptr<std::mutex> mutex;
	};
}
