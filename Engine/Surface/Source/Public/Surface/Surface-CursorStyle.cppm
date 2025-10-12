/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Surface:CursorStyle;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Surface
{
	/// @brief Cursor style.
	struct CursorStyle final
	{
		std::optional<Math::Rect<float>> clippingRect = Math::Rect<float>(Math::Vector2<float>::One()); ///< Cursor clipping rectangle. It's in normalized client rectangle coordinates.
		bool visible = true; ///< Is the cursor visible?
	};
}
