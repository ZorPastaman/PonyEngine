/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Surface:Utility;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Surface
{
	/// @brief Converts an absolute point to a relative point.
	/// @param point Point.
	/// @param resolution Resolution.
	/// @return Relative point.
	[[nodiscard("Pure function")]]
	constexpr Math::Vector2<float> AbsoluteToRelative(const Math::Vector2<std::int32_t>& point, const Math::Vector2<std::int32_t>& resolution) noexcept;
	/// @brief Converts a relative point to an absolute point.
	/// @param point Point.
	/// @param resolution Resolution.
	/// @return Absolute point.
	[[nodiscard("Pure function")]]
	constexpr Math::Vector2<std::int32_t> RelativeToAbsolute(const Math::Vector2<float>& point, const Math::Vector2<std::int32_t>& resolution) noexcept;
}

#if PONY_WINDOWS
export namespace PonyEngine::Surface::Windows
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR GetDefaultCursor();
}
#endif

namespace PonyEngine::Surface
{
	constexpr Math::Vector2<float> AbsoluteToRelative(const Math::Vector2<std::int32_t>& point, const Math::Vector2<std::int32_t>& resolution) noexcept
	{
		return Math::Divide(static_cast<Math::Vector2<float>>(point), static_cast<Math::Vector2<float>>(resolution));
	}

	constexpr Math::Vector2<std::int32_t> RelativeToAbsolute(const Math::Vector2<float>& point, const Math::Vector2<std::int32_t>& resolution) noexcept
	{
		return Math::RoundToIntegral<std::int32_t>(Math::Multiply(point, static_cast<Math::Vector2<float>>(resolution)));
	}
}

#if PONY_WINDOWS
namespace PonyEngine::Surface::Windows
{
	HCURSOR GetDefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageA(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (!cursor)
		{
			throw std::runtime_error(std::format("Failed to load default cursor. Error code: '0x{:X}'.", GetLastError()));
		}

		return cursor;
	}
}
#endif
