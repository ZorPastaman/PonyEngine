/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <exception>
#include <format>
#include <iostream>

#include "PonyEngine/Platform/Windows/Framework.h"

export module Main;

import Application.Windows;

export int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	try
	{
		Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if !NDEBUG
		Application::Windows::CreateConsole(CP_UTF8);
#endif

		std::cout << "Wow ☃ 日本国 кошка\n";
		OutputDebugStringA("Wow ☃ 日本国 кошка\n");
		MessageBoxExA(nullptr, "Wow ☃ 日本国 кошка", "Wowe", MB_OK, 0);

#if !NDEBUG
		Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what(); // TODO: Use pony console later.

		return Application::ExitCodes::MainException;
	}
	catch (...)
	{
		std::cerr << "Non std::exception!"; // TODO: Use pony console later.

		return Application::ExitCodes::MainException;
	}

	return Application::ExitCodes::Success;
}
