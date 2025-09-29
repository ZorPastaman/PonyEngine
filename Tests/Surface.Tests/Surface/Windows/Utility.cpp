/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Platform/Windows/Framework.h"

#include <catch2/catch_test_macros.hpp>

import PonyEngine.Surface.Windows;

TEST_CASE("DefaultCursor returns default cursor", "[Surface][Utility]")
{
	REQUIRE(static_cast<HCURSOR>(LoadImageA(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED)) == PonyEngine::Surface::Windows::GetDefaultCursor());
}
