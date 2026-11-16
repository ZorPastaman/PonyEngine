/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display.Impl.WinAPI:DisplayProperties;

import std;

export namespace PonyEngine::Display
{
	/// @brief Display properties.
	struct DisplayProperties final
	{
		std::string sourceName; ///< Display source name.
		std::string targetName; ///< Display target name.
		std::string friendlyTargetName; ///< Display friendly target name.
	};
}
