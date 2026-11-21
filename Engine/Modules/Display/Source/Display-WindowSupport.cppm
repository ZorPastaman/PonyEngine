/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Display:WindowSupport;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Display
{
	enum class CommonWindowFeature : std::uint8_t
	{
		None = 0,
		ModeSwitchable = 1 << 0,
		Title = 1 << 1,
		Icon = 1 << 2,
		Hidable = 1 << 3,
		All = (1 << 4) - 1
	};

	enum class FullscreenWindowFeature : std::uint8_t
	{
		None = 0,
		MultiWindowPerDisplay = 1 << 0,
		MultiDisplayWindow = 1 << 1,
		Changeable = 1 << 2,
		All = (1 << 3) - 1
	};

	enum class WindowedWindowFeature : std::uint8_t
	{
		None = 0,
		Resizable = 1 << 0,
		ResizeForbiddable = 1 << 1,
		ResizeLimits = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_MASK_FEATURES(CommonWindowFeature)
	PONY_ENUM_MASK_FEATURES(FullscreenWindowFeature)
	PONY_ENUM_MASK_FEATURES(WindowedWindowFeature)

	struct FullscreenWindowSupport final
	{
		FullscreenWindowFeature features = FullscreenWindowFeature::None;
	};

	struct WindowedWindowSupport final
	{
		std::optional<Math::Vector2<std::uint32_t>> minSize;
		std::optional<Math::Vector2<std::uint32_t>> maxSize;
		WindowedWindowFeature features = WindowedWindowFeature::None;
	};

	struct WindowSupport final
	{
		CommonWindowFeature commonFeatures = CommonWindowFeature::None;
		std::optional<FullscreenWindowSupport> fullscreen;
		std::optional<WindowedWindowSupport> windowed;
	};
}

namespace PonyEngine::Display
{
	constexpr std::array<std::string_view, 4> CommonWindowFeatureNames
	{
		"ModeSwitchable",
		"Title",
		"Icon",
		"Hidable"
	};

	constexpr std::array<std::string_view, 3> FullscreenWindowFeatureNames
	{
		"MultiWindowPerDisplay",
		"MultiDisplayWindow",
		"Changeable"
	};

	constexpr std::array<std::string_view, 3> WindowedWindowFeatureNames
	{
		"Resizable",
		"ResizeForbiddable",
		"ResizeLimits"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Display::CommonWindowFeature, PonyEngine::Display::CommonWindowFeatureNames)
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Display::FullscreenWindowFeature, PonyEngine::Display::FullscreenWindowFeatureNames)
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Display::WindowedWindowFeature, PonyEngine::Display::WindowedWindowFeatureNames)
}
