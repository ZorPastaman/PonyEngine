/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Platform/Windows/Framework.h"

import std;

import PonyEngine.Application.Impl.Windows;

#ifdef PONY_ENGINE_APPLICATION_MODE_GUI

int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	try
	{
		return std::make_unique<PonyEngine::Application::Windows::GUIProcess>(hInstance, hPrevInstance, lpCmdLine, nShowCmd)->Run();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, "Exception", std::format("{}:\n{}", typeid(e).name(), e.what()).c_str(), MB_OK | MB_ICONERROR | MB_TOPMOST);
		return -1;
	}
	catch (...)
	{
		MessageBoxA(nullptr, "Unexpected exception", "Unexpected exception", MB_OK | MB_ICONERROR | MB_TOPMOST);
		return -1;
	}
}

#elifdef PONY_ENGINE_APPLICATION_MODE_CONSOLE

int main(const int argc, const char* const argv[])
{
	try
	{
		return std::make_unique<PonyEngine::Application::Windows::ConsoleProcess>(argc, argv)->Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << std::format("{}:\n{}\n", typeid(e).name(), e.what());
		return -1;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception";
		return -1;
	}
}

#else

#error "No GUI or Console define set"

#endif
