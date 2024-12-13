/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyEngine.Window.Windows.Detail:WindowsUtility;

import <cstdint>;
import <stdexcept>;
import <utility>;

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Shape;
import PonyMath.Utility;

export namespace PonyEngine::Window
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR DefaultCursor();

	/// @brief Converts the Windows rect to a pair of a position and a resolution.
	/// @param windowRect Windows rect.
	/// @return Pair of a position and a resolution.
	[[nodiscard("Pure function")]]
	std::pair<PonyMath::Core::Vector2<int>, PonyMath::Core::Vector2<int>> ConvertToPositionResolution(const RECT& windowRect) noexcept;
	/// @brief Converts the Windows rect to a rect.
	/// @param rect Windows rect.
	/// @return Rect.
	[[nodiscard("Pure function")]]
	PonyMath::Shape::Rect<std::int32_t> ConvertToRect(const RECT& rect) noexcept;
	/// @brief Converts the rect to a Windows rect.
	/// @tparam T Value type.
	/// @param rect Source.
	/// @return Windows rect.
	template<PonyMath::Core::Arithmetic T> [[nodiscard("Pure function")]]
	RECT ConvertToWindowsRect(const PonyMath::Shape::Rect<T>& rect) noexcept;
}

namespace PonyEngine::Window
{
	HCURSOR DefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageW(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (!cursor)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to load default cursor. Error code: '0x{:X}'.", GetLastError()));
		}

		return cursor;
	}

	std::pair<PonyMath::Core::Vector2<int>, PonyMath::Core::Vector2<int>> ConvertToPositionResolution(const RECT& windowRect) noexcept
	{
		const auto position = PonyMath::Core::Vector2<int>(static_cast<int>(windowRect.left), static_cast<int>(windowRect.top));
		const auto resolution = PonyMath::Core::Vector2<int>(static_cast<int>(windowRect.right - windowRect.left), static_cast<int>(windowRect.bottom - windowRect.top));

		return std::pair(position, resolution);
	}

	PonyMath::Shape::Rect<std::int32_t> ConvertToRect(const RECT& rect) noexcept
	{
		return PonyMath::Shape::Rect<std::int32_t>(static_cast<std::int32_t>(rect.left), static_cast<std::int32_t>(rect.top), 
			static_cast<std::int32_t>(rect.right - rect.left), static_cast<std::int32_t>(rect.bottom - rect.top));
	}

	template<PonyMath::Core::Arithmetic T>
	RECT ConvertToWindowsRect(const PonyMath::Shape::Rect<T>& rect) noexcept
	{
		return RECT{.left = static_cast<LONG>(rect.MinX()), .top = static_cast<LONG>(rect.MinY()), .right = static_cast<LONG>(rect.MaxX()), .bottom = static_cast<LONG>(rect.MaxY())};
	}
}
