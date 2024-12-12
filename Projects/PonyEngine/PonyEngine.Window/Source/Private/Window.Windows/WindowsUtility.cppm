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
import PonyMath.Utility;

export namespace PonyEngine::Window
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR DefaultCursor();

	/// @brief Converts a Windows window rect to a pair of a position and a resolution.
	/// @param windowRect Windows window rect.
	/// @return Pair of a position and a resolution.
	[[nodiscard("Pure function")]]
	std::pair<PonyMath::Core::Vector2<int>, PonyMath::Core::Vector2<int>> ConvertToPositionResolution(const RECT& windowRect) noexcept;
	/// @brief Converts a Windows window rect to a pair of a position and a resolution.
	/// @param windowRect Windows window rect.
	/// @return Pair of a position and a resolution.
	[[nodiscard("Pure function")]]
	std::pair<PonyMath::Core::Vector2<std::int32_t>, PonyMath::Utility::Resolution<std::uint32_t>> ConvertToWindowRect(const RECT& windowRect) noexcept;
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

	std::pair<PonyMath::Core::Vector2<std::int32_t>, PonyMath::Utility::Resolution<std::uint32_t>> ConvertToWindowRect(const RECT& windowRect) noexcept
	{
		return std::pair(
			PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(windowRect.left), static_cast<std::int32_t>(windowRect.top)),
			PonyMath::Utility::Resolution<std::uint32_t>(static_cast<std::uint32_t>(windowRect.right - windowRect.left), static_cast<std::uint32_t>(windowRect.bottom - windowRect.top))
		);
	}
}
