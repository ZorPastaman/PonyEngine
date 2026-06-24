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
	class ILoadableResourceData
	{
		PONY_INTERFACE_BODY(ILoadableResourceData)

		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback = nullptr) const = 0;
	};
}
