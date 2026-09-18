/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.Ext:IFileDataAccess;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Data access that provides direct access to a resource data in a file.
	class IFileDataAccess
	{
		PONY_INTERFACE_BODY(IFileDataAccess)

		/// @brief Gets the file path.
		/// @return File path.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path& Path() const noexcept = 0;
		/// @brief Gets the data file offset.
		/// @return File offset in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Offset() const noexcept = 0;
		/// @brief Gets the data size.
		/// @return Data size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;
	};
}
