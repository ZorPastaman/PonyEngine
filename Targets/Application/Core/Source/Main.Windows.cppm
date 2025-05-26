/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <format> // TODO: Check for module support.

export module Main;

export int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	SetConsoleCP(CP_UTF8); // TODO: Move to base.
	SetConsoleOutputCP(CP_UTF8);

	OutputDebugStringA("Wow ☃ 日本国 кошка\n");
	OutputDebugStringA(std::format("{}\n", GetACP()).c_str());
	MessageBoxExA(nullptr, "Wow ☃ 日本国 кошка", "Wowe", MB_OK, 0);


	return 0;
}
