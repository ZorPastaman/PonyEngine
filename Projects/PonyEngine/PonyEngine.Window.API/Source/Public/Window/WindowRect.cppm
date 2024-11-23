/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:WindowRect;

import <cstdint>;

import PonyMath.Core;
import PonyMath.Utility;

export namespace PonyEngine::Window
{
	/// @brief Window rect.
	struct WindowRect final
	{
		bool fullscreen = true; ///< If @a true, the window will expand to the whole screen. @p position and @p resolution aren't used in this case.
		PonyMath::Core::Vector2<std::int32_t> position = PonyMath::Core::Vector2<std::int32_t>(10, 10); ///< Window position. Left-upper corner. It's used only if @p fullscreen is @a false.
		PonyMath::Utility::Resolution<std::uint32_t> resolution = PonyMath::Utility::Resolution<std::uint32_t>(1280u, 720u); ///< Window client area resolution. It's used only if @p fullscreen is @a false.
	};
}
