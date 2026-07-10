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

export module PonyEngine.Resource.Ext:IResourceProvider;

import std;

import PonyEngine.Resource;

import :IFileResourceData;
import :ILoadableResourceData;
import :IMemoryResourceData;
import :IResourceRegistry;

export namespace PonyEngine::Resource
{
	/// @brief Resource provider.
	class IResourceProvider
	{
		PONY_INTERFACE_BODY(IResourceProvider)

		/// @brief Invoked before a first tick.
		/// @param registry Resource registry.
		/// @note The function is always called on a main thread.
		virtual void Begin(IResourceRegistry& registry) = 0;
		/// @brief Invoked after a last tick.
		/// @param registry Resource registry.
		/// @note The function is always called on a main thread.
		virtual void End(IResourceRegistry& registry) = 0;
		/// @brief Ticks the provider.
		/// @param registry Resource registry.
		/// @note The function is always called on a main thread.
		virtual void Tick(IResourceRegistry& registry) = 0;

		/// @brief Gets a registered loadable resource data.
		/// @param index Resource data index.
		/// @return Loadable resource data.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILoadableResourceData> GetLoadableResource(std::size_t index) const = 0;
		/// @brief Gets a registered file resource data.
		/// @param index Resource data index.
		/// @return File resource data.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFileResourceData> GetFileResource(std::size_t index) const = 0;
		/// @brief Gets a registered memory resource data.
		/// @param index Resource data index.
		/// @return Memory resource data.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IMemoryResourceData> GetMemoryResource(std::size_t index) const = 0;
	};
}
