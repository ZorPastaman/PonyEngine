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

export module PonyEngine.Resource.Ext:IResourceData;

import std;

import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	class IResourceData
	{
		PONY_INTERFACE_BODY(IResourceData)

		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback = nullptr) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsFileReferenceAvailable() const noexcept { return false; }
		[[nodiscard("Pure function")]]
		virtual const FileReference& GetFileReference() const { throw std::logic_error("Not implemented"); }
		[[nodiscard("Pure function")]]
		virtual bool IsMemoryReferenceAvailable() const noexcept { return false; }
		[[nodiscard("Pure function")]]
		virtual const MemoryReference& GetMemoryReference() const { throw std::logic_error("Not implemented"); }
	};
}
