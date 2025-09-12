/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Path:IPathService;

import std;

export namespace PonyEngine::Path
{
	/// @brief Path service.
	class IPathService
	{
		INTERFACE_BODY(IPathService)

		/// @brief Gets the path count.
		/// @return Path count.
		[[nodiscard("Pure function")]]
		virtual std::size_t PathCount() const noexcept = 0;
		/// @brief Gets a path ID by the @p index.
		/// @param index Path ID index.
		/// @return Path ID.
		[[nodiscard("Pure function")]]
		virtual std::string_view PathId(std::size_t index) const noexcept = 0;
		/// @brief Tries to find a path by the @p pathId.
		/// @param pathId Path ID.
		/// @return Path if it's found; nullptr if it's not.
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path* FindPath(std::string_view pathId) const noexcept = 0;
		/// @brief Adds a path.
		/// @param pathId Path ID. Mustn't be already added.
		/// @param path Path. Must be absolute.
		virtual void AddPath(std::string_view pathId, const std::filesystem::path& path) = 0;
	};
}
