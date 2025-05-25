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
#include <windows.h>

export module Main;

export int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	MessageBoxExA(nullptr, "Wow", "Wowe", MB_OK, 0);
	return 0;
}
