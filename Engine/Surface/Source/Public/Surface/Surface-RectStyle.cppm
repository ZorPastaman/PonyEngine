/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface:RectStyle;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Surface
{
	/// @brief Rectangle style.
	struct RectStyle final
	{
		Math::Rect<std::int32_t> clientRect = Math::Rect<std::int32_t>(Math::Vector2<std::int32_t>(320, 240)); ///< Client rectangle.
		Math::Vector2<std::int32_t> minimalClientSize = Math::Vector2<std::int32_t>(320, 240); ///< Minimal client rectangle size.
		bool fullscreen = true; ///< Is the client rectangle fullscreen?
		bool movable = false; ///< Is the client rectangle movable?
		bool resizable = false; ///< Is the client rectangle resizable?
		bool closable = false; ///< Is the client rectangle closable?
		bool maximizable = false; ///< Is the client rectangle maximizable?
		bool minimizable = false;  ///< Is the client rectangle minimizable?
		bool alwaysOnTop = false;  ///< Is the client rectangle always on top?
		bool popup = true;  ///< Is the client rectangle popup - pure client rectangle without any other elements?
	};
}
