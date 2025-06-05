/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:ScreenSystem;

import <cstdint>;

import PonyMath.Utility;

import PonyEngine.Screen;

export namespace Mocks
{
	class ScreenSystem final : public PonyEngine::Screen::IScreenSystem
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> DisplayResolution() const noexcept override;
	};
}

namespace Mocks
{
	PonyMath::Utility::Resolution<std::uint32_t> ScreenSystem::DisplayResolution() const noexcept
	{
		return PonyMath::Utility::Resolution<std::uint32_t>(1280u, 720u);
	}
}
