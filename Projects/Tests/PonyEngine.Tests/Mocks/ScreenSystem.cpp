/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "ScreenSystem.h"

namespace Mocks
{
	PonyMath::Utility::Resolution<std::uint32_t> ScreenSystem::DisplayResolution() const noexcept
	{
		return PonyMath::Utility::Resolution<std::uint32_t>(1280u, 720u);
	}
}
