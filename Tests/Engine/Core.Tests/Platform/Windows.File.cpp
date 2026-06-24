/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Platform/Windows/Storage.h"

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.Platform;

void Dummy()
{
}

TEST_CASE("GetModule returns a current module", "[Platform][Windows][File]")
{
	HMODULE moduleHandle;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCSTR>(&Dummy), &moduleHandle);
	REQUIRE(moduleHandle == PonyEngine::Platform::Windows::GetModule());
}

TEST_CASE("GetModulePath returns a current module path", "[Platform][Windows][File]")
{
	auto path = std::array<wchar_t, MAX_PATH>();
	GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
	REQUIRE(std::wstring(path.data()) == PonyEngine::Platform::Windows::GetModulePath(nullptr).wstring());
}

TEST_CASE("GetKnowsPath returns a local data path", "[Platform][Windows][File]")
{
	wchar_t* pathRaw = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pathRaw);
	REQUIRE(std::wstring(pathRaw) == PonyEngine::Platform::Windows::GetKnownPath(FOLDERID_LocalAppData));
	CoTaskMemFree(pathRaw);
}

TEST_CASE("GetTemporaryPath returns a temp path", "[Platform][Windows][File]")
{
	auto path = std::array<wchar_t, MAX_PATH>();
	GetTempPath2W(MAX_PATH, path.data());
	REQUIRE(std::wstring(path.data()) == PonyEngine::Platform::Windows::GetTemporaryPath().wstring());
}
