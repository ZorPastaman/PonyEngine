/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

#include <catch2/catch_test_macros.hpp>

import PonyEngine.File;

void Dummy()
{
}

#if PONY_WINDOWS
TEST_CASE("GetModule returns a current module", "[File][Module]")
{
	HMODULE moduleHandle;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCSTR>(&Dummy), &moduleHandle);
	REQUIRE(moduleHandle == PonyEngine::File::Windows::GetModule());
}
#endif
