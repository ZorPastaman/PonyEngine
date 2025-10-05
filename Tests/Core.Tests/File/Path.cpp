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

import std;

import PonyEngine.File;

#if PONY_WINDOWS
TEST_CASE("GetModulePath returns a current module path", "[File][Path]")
{
	auto path = std::array<wchar_t, MAX_PATH>();
	GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
	REQUIRE(std::wstring(path.data()) == PonyEngine::File::Windows::GetModulePath(nullptr).wstring());
}

TEST_CASE("GetKnowsPath returns a local data path", "[File][Path]")
{
	wchar_t* pathRaw = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pathRaw);
	REQUIRE(std::wstring(pathRaw) == PonyEngine::File::Windows::GetKnownPath(FOLDERID_LocalAppData));
	CoTaskMemFree(pathRaw);
}

TEST_CASE("GetTemporaryPath returns a temp path", "[Utility][Path]")
{
	auto path = std::array<wchar_t, MAX_PATH>();
	GetTempPath2W(MAX_PATH, path.data());
	REQUIRE(std::wstring(path.data()) == PonyEngine::File::Windows::GetTemporaryPath().wstring());
}
#endif
