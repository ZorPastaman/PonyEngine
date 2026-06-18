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

export module PonyEngine.Resource:IFileResource;

import std;

import :IResource;

export namespace PonyEngine::Resource
{
	class IFileResource : public IResource
	{
		PONY_INTERFACE_BODY(IFileResource)

		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& Path() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t Offset() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
	};
}
