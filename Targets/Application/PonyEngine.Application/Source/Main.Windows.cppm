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

#include "PonyEngine/Module/API.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Main;

import PonyEngine.Application.Windows;

import PonyEngine.Core;
import PonyEngine.Module;

extern "C" void InitializeModule1();
PONY_MODULE_INITIALIZER_EARLIEST(InitializeModule1);

void InitializeModule1()
{
	std::cout << "Module!\n";
}

namespace PonyEngine::Module
{
	PONY_MODULE_ALLOCATE(a) const ModuleInitializer FirstInitializer = nullptr;
	PONY_MODULE_ALLOCATE(z) const ModuleInitializer LastInitializer = nullptr;
}

export int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if !NDEBUG
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		auto begin = (uintptr_t)&PonyEngine::Module::FirstInitializer
			+ sizeof(PonyEngine::Module::FirstInitializer);
		auto end = (uintptr_t)&PonyEngine::Module::LastInitializer;
		for (auto current = begin; current < end;
			current += sizeof(PonyEngine::Module::ModuleInitializer)) {
			auto initializer = *(const PonyEngine::Module::ModuleInitializer*)current;
			if (initializer) initializer();
		}

		std::cout << "Wow ☃ 日本国 кошка\n";
		OutputDebugStringA("Wow ☃ 日本国 кошка\n");
		MessageBoxExA(nullptr, "Wow ☃ 日本国 кошка", "Wowe", MB_OK, 0);

#if !NDEBUG
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
