/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display:WindowMode;

import std;

import PonyEngine.Math;

import :DisplayHandle;

export namespace PonyEngine::Display
{
	struct FullscreenWindowMode final
	{
		std::span<const DisplayHandle> displays;
	};

	struct WindowedWindowMode final
	{
		std::optional<Math::Vector2<std::uint32_t>> size;
		std::optional<Math::Vector2<std::uint32_t>> minSize;
		std::optional<Math::Vector2<std::uint32_t>> maxSize;
		bool resizableByUser = true;
	};

	using WindowMode = std::variant<FullscreenWindowMode, WindowedWindowMode>;
}
