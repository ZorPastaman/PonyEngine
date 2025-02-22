/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Clear;

import <cstdint>;
import <type_traits>;

export namespace PonyEngine::Render
{
	enum class Clear : std::uint8_t
	{
		None = 0,
		Color = 1 << 0,
		Depth = 1 << 1,
		Stencil = 1 << 2,
		All = Color | Depth | Stencil
	};

	[[nodiscard("Pure operator")]]
	constexpr Clear operator ~(Clear clear) noexcept;
	[[nodiscard("Pure operator")]]
	constexpr Clear operator &(Clear left, Clear right) noexcept;
	[[nodiscard("Pure operator")]]
	constexpr Clear operator |(Clear left, Clear right) noexcept;
	[[nodiscard("Pure operator")]]
	constexpr Clear operator ^(Clear left, Clear right) noexcept;
}

namespace PonyEngine::Render
{
	constexpr Clear operator ~(const Clear clear) noexcept
	{
		return clear ^ Clear::All;
	}

	constexpr Clear operator &(const Clear left, const Clear right) noexcept
	{
		return static_cast<Clear>(static_cast<std::underlying_type_t<Clear>>(left) & static_cast<std::underlying_type_t<Clear>>(right));
	}

	constexpr Clear operator |(const Clear left, const Clear right) noexcept
	{
		return static_cast<Clear>(static_cast<std::underlying_type_t<Clear>>(left) | static_cast<std::underlying_type_t<Clear>>(right));
	}

	constexpr Clear operator ^(const Clear left, const Clear right) noexcept
	{
		return static_cast<Clear>(static_cast<std::underlying_type_t<Clear>>(left) ^ static_cast<std::underlying_type_t<Clear>>(right));
	}
}
