/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <exception>
#include <format>
#include <iostream>

#include "PonyEngine/Platform/Windows/Framework.h"

import PonyEngine.Application.Windows;

int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		PonyEngine::Application::App app;

		std::cout << "Wow ☃ 日本国 кошка\n";
		OutputDebugStringA("Wow ☃ 日本国 кошка\n");
		MessageBoxExA(nullptr, "Wow ☃ 日本国 кошка", "Wowe", MB_OK, 0);

#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what(); // TODO: Use pony console later.

		return PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		std::cerr << "Non std::exception!"; // TODO: Use pony console later.

		return PonyEngine::Application::ExitCodes::MainException;
	}

	return PonyEngine::Application::ExitCodes::Success;
}
