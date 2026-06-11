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

export module PonyEngine.Resource:IResource;

import std;

import :ILoadRequest;
import :LoadParams;
import :ResourceType;

export namespace PonyEngine::Resource
{
	class IResource
	{
		PONY_INTERFACE_BODY(IResource)

		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;

		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback = nullptr) const = 0;
	};
}
