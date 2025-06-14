/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:CursorParams;

import <optional>;

import PonyMath.Core;
import PonyMath.Shape;

export namespace PonyEngine::Window
{
	/// @brief Cursor parameters.
	struct CursorParams final
	{
		bool visible = true; ///< Is cursor initially visible?
		std::optional<PonyMath::Core::Vector2<float>> cursorPosition; ///< Initial cursor position. It's set in client normalized coordinates. If it's nullopt a cursor position isn't changed.
		std::optional<PonyMath::Shape::Rect<float>> cursorClipping; ///< Cursor clipping rect. It's set in client normalized coordinates. If it's nullopt a cursor isn't clipped.
	};
}
