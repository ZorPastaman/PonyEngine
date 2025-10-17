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
	/// @brief Fullscreen rectangle style.
	struct FullscreenRectStyle final
	{
		bool alwaysOnTop = false;  ///< Is the client rectangle always on top?
	};

	/// @brief Window rectangle style.
	/// @remark It may be unsupported on some platforms.
	struct WindowRectStyle final
	{
		bool hasFrame = true; ///< Does the client rectangle have a frame?
		bool movable = true; ///< Is the client rectangle movable?
		bool resizable = false; ///< Is the client rectangle resizable?
		bool closable = true; ///< Is the client rectangle closable?
		bool maximizable = true; ///< Is the client rectangle maximizable?
		bool minimizable = true;  ///< Is the client rectangle minimizable?
		bool alwaysOnTop = false;  ///< Is the client rectangle always on top?
	};

	using RectStyle = std::variant<FullscreenRectStyle, WindowRectStyle>; ///< Rectangle style.
}
