/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Factory:FileSubLoggerParams;

import <filesystem>;

export namespace PonyEngine::Log
{
	/// @brief File sub-logger parameters.
	struct FileSubLoggerParams final
	{
		std::filesystem::path logPath = "Log.log"; ///< Log file path.
	};
}
