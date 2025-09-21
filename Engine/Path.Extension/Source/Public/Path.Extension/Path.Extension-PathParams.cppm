/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Path.Extension:PathParams;

import std;

export namespace PonyEngine::Path
{
	/// @brief Path parameters.
	struct PathParams final
	{
		std::filesystem::path rootPath = ""; ///< Root path. It's relative to the executable path.
		std::filesystem::path localDataPath; ///< Local data path. It must be absolute.
		std::filesystem::path userDataPath; ///< User data path. It must be absolute.
		std::filesystem::path logPath; ///< Log path. It must be absolute.
	};
}
