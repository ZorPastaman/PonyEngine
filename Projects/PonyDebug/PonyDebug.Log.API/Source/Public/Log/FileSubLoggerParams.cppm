/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:FileSubLoggerParams;

import <filesystem>;

import :SubLoggerParams;

export namespace PonyDebug::Log
{
	/// @brief File sub-logger parameters.
	struct FileSubLoggerParams final : SubLoggerParams
	{
		std::filesystem::path logPath; ///< Log file path.
	};
}
