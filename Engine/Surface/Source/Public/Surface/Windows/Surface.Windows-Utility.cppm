/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Surface.Windows:Utility;

import PonyEngine.Surface;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Converts an engine style to a Windows style.
	/// @param style Engine style.
	/// @return Windows style.
	[[nodiscard("Pure function")]]
	constexpr DWORD ConvertToWindowsStyle(SurfaceStyle style) noexcept;
	/// @brief Converts an engine style to a Windows style ex.
	/// @param style Engine style.
	/// @return Windows style ex.
	[[nodiscard("Pure function")]]
	constexpr DWORD ConvertToWindowsStyleEx(SurfaceStyle style) noexcept;

	/// @brief Converts a Windows style to a surface style.
	/// @param style Windows style.
	/// @return Surface style.
	[[nodiscard("Pure function")]]
	constexpr SurfaceStyle ConvertToSurfaceStyle(DWORD style) noexcept;
	/// @brief Converts a Windows style ex to a surface style.
	/// @param style Windows style ex.
	/// @return Surface style.
	[[nodiscard("Pure function")]]
	constexpr SurfaceStyle ConvertExToSurfaceStyle(DWORD style) noexcept;
}

namespace PonyEngine::Surface::Windows
{
	constexpr DWORD ConvertToWindowsStyle(const SurfaceStyle style) noexcept
	{
		DWORD windowsStyle = 0;
		windowsStyle |= style == SurfaceStyle::None ? WS_POPUP : 0;
		windowsStyle |= (style & SurfaceStyle::Border) != SurfaceStyle::None ? WS_BORDER : 0;
		windowsStyle |= (style & SurfaceStyle::Title) != SurfaceStyle::None ? WS_BORDER | WS_CAPTION : 0;
		windowsStyle |= (style & SurfaceStyle::Close) != SurfaceStyle::None ? WS_BORDER | WS_CAPTION | WS_SYSMENU : 0;
		windowsStyle |= (style & SurfaceStyle::Maximize) != SurfaceStyle::None ? WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX : 0;
		windowsStyle |= (style & SurfaceStyle::Minimize) != SurfaceStyle::None ? WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX : 0;
		windowsStyle |= (style & SurfaceStyle::Resizable) != SurfaceStyle::None ? WS_BORDER | WS_THICKFRAME : 0;

		return windowsStyle;
	}

	constexpr DWORD ConvertToWindowsStyleEx(const SurfaceStyle style) noexcept
	{
		return (style & SurfaceStyle::AlwaysOnTop) != SurfaceStyle::None ? WS_EX_TOPMOST : 0;
	}

	constexpr SurfaceStyle ConvertToSurfaceStyle(const DWORD style) noexcept
	{
		auto surfaceStyle = SurfaceStyle::None;
		surfaceStyle |= style & (WS_BORDER | WS_CAPTION | WS_THICKFRAME) ? SurfaceStyle::Border : SurfaceStyle::None;
		surfaceStyle |= style & WS_CAPTION ? SurfaceStyle::Title : SurfaceStyle::None;
		surfaceStyle |= style & WS_SYSMENU ? SurfaceStyle::Close : SurfaceStyle::None;
		surfaceStyle |= style & WS_MAXIMIZEBOX ? SurfaceStyle::Maximize : SurfaceStyle::None;
		surfaceStyle |= style & WS_MINIMIZEBOX ? SurfaceStyle::Minimize : SurfaceStyle::None;
		surfaceStyle |= style & WS_THICKFRAME ? SurfaceStyle::Resizable : SurfaceStyle::None;

		return surfaceStyle;
	}

	constexpr SurfaceStyle ConvertExToSurfaceStyle(const DWORD style) noexcept
	{
		return style & WS_EX_TOPMOST ? SurfaceStyle::AlwaysOnTop : SurfaceStyle::None;
	}
}
