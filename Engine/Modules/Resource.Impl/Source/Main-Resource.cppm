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

import :ResourceData;
import :ResourceInfo;
import :ResourceLoadProcess;

export namespace PonyEngine::Resource
{
	/// @brief Resource.
	struct Resource final
	{
		std::shared_ptr<const ResourceInfo> info; ///< Resource info.
		std::shared_ptr<ResourceData> data; ///< Resource data.
		std::weak_ptr<ResourceLoadProcess> loadProcess; ///< Resource load process.
		std::shared_ptr<std::mutex> mutex; ///< Resource mutex.
	};
}
