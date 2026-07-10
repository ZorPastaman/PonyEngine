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

export module PonyEngine.Resource.Ext:IFileResourceData;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource data that provides a direct file access.
	class IFileResourceData
	{
		PONY_INTERFACE_BODY(IFileResourceData)

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
