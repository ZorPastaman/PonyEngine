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

export module PonyEngine.Path:MainPathIds;

import std;

export namespace PonyEngine::Path
{
	/// @brief Main path IDs. These paths are always present.
	struct MainPathIds final
	{
		NON_CONSTRUCTIBLE_BODY(MainPathIds)

		static constexpr std::string_view Root = "Root"; ///< Path to an application root folder.
		static constexpr std::string_view Executable = "Executable"; ///< Path to an executable.
		static constexpr std::string_view ExecutableDirectory = "ExecutableDirectory"; ///< Path to an executable folder.
		static constexpr std::string_view LocalData = "LocalData"; ///< Path to a local data.
		static constexpr std::string_view UserData = "UserData"; ///< Path to a user data.
		static constexpr std::string_view Log = "Log"; ///< Path to logs.
	};
}
