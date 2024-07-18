/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:EngineSettings;

export namespace Launcher
{
	/// @brief Engine settings.
	struct EngineSettings final
	{
		float targetFrameRate; ///< Target frame rate in fps.
	};
}
