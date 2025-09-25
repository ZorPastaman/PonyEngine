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

import std;

import PonyEngine.Path.Windows;

TEST_CASE("GetModulePath returns a current module path", "[Path][Utility]")
{
	auto path = std::array<wchar_t, MAX_PATH>();
	GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
	REQUIRE(std::wstring(path.data()) == PonyEngine::Path::Windows::GetModulePath(nullptr).wstring());
}

TEST_CASE("GetKnowsPath returns a local data path", "[Path][Utility]")
{
	wchar_t* pathRaw = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pathRaw);
	REQUIRE(std::wstring(pathRaw) == PonyEngine::Path::Windows::GetKnownPath(FOLDERID_LocalAppData));
	CoTaskMemFree(pathRaw);
}
