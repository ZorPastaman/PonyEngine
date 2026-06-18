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
	class ILoadableResource : public IResource
	{
		PONY_INTERFACE_BODY(ILoadableResource)

		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback = nullptr) const = 0;
	};
}
