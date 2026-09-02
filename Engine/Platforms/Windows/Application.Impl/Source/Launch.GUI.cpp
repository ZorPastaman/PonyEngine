/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

import std;

import PonyEngine.Application.Impl.Windows;

int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	try
	{
		const std::vector<std::string> commandLine = PonyEngine::Application::MakeCommandLine();
		return std::make_unique<PonyEngine::Application::GUIProcess>(hInstance, hPrevInstance, lpCmdLine, nShowCmd, 
			PonyEngine::Application::MakeCommandLineView(commandLine))->Run();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, std::format("{}:\n{}", typeid(e).name(), e.what()).c_str(), "Exception", MB_OK | MB_ICONERROR | MB_TOPMOST);
		return -1;
	}
	catch (...)
	{
		MessageBoxA(nullptr, "Unexpected exception", "Unexpected exception", MB_OK | MB_ICONERROR | MB_TOPMOST);
		return -1;
	}
}
