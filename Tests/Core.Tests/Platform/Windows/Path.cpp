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

import PonyEngine.Platform.Windows;

TEST_CASE("GetModulePath returns a current module path", "[Platform][Path]")
{
	auto path = std::array<wchar_t, MAX_PATH>();
	GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
	REQUIRE(std::wstring(path.data()) == PonyEngine::Platform::Windows::GetModulePath(nullptr).wstring());
}

TEST_CASE("GetKnowsPath returns a local data path", "[Platform][Path]")
{
	wchar_t* pathRaw = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pathRaw);
	REQUIRE(std::wstring(pathRaw) == PonyEngine::Platform::Windows::GetKnownPath(FOLDERID_LocalAppData));
	CoTaskMemFree(pathRaw);
}
