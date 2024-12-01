/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <cstdint>

import PonyMath.Utility;

import PonyEngine.Screen;

namespace Mocks
{
	class ScreenSystem final : public PonyEngine::Screen::IScreenSystem
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> DisplayResolution() const noexcept override;
	};
}
