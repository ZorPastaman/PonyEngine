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
	/// @brief Direct file resource access.
	class IFileResource : public IResource
	{
		PONY_INTERFACE_BODY(IFileResource)

		/// @brief Gets a resource file path.
		/// @return Resource file path.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& Path() const noexcept = 0;
		/// @brief Gets a resource file offset.
		/// @return File offset in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Offset() const noexcept = 0;
		/// @brief Gets a resource size.
		/// @return Resource size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
	};
}
