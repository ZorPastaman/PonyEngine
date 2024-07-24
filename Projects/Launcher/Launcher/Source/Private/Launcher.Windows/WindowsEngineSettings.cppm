/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher.Windows:WindowsEngineSettings;

import Launcher;

export namespace Launcher
{
	/// @brief Gets the engine settings.
	/// @return Engine settings.
	[[nodiscard("Pure function")]]
	EngineSettings GetEngineSettings() noexcept;
}

namespace Launcher
{
	EngineSettings GetEngineSettings() noexcept
	{
		return EngineSettings{.targetFrameRate = 165.f};
	}
}
