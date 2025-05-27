/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <format>

#include "PonyEngine/Platform/Windows/Framework.h"

export module Main;

import Application.Windows;

export int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	Application::Windows::SetConsoleCodePage(CP_UTF8);
	Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);

	OutputDebugStringA("Wow ☃ 日本国 кошка\n");
	OutputDebugStringA(std::format("{}\n", GetACP()).c_str());
	MessageBoxExA(nullptr, "Wow ☃ 日本国 кошка", "Wowe", MB_OK, 0);

	return 0;
}
