/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:ApplicationPaths;

import std;

export namespace PonyEngine::Application
{
	/// @brief Application paths.
	struct ApplicationPaths final
	{
		std::filesystem::path gameData; ///< Path to the game executable directory.
		std::filesystem::path executable; ///< Path to the game executable. It's @p gameData/<GameExecutableName>
		std::filesystem::path localData; ///< Path to the local data. It's a path for files that the application produces.
		std::filesystem::path userData; ///< Path to the user data. Is' a path for files that a user produces.
	};
}
