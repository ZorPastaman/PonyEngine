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

int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	try
	{
		const std::vector<std::string> commandLine = PonyEngine::Application::MakeCommandLine();
		const std::vector<std::string_view> commandLineView = PonyEngine::Application::MakeCommandLineView(commandLine);
		return std::make_unique<PonyEngine::Application::GUIProcess>(hInstance, hPrevInstance, lpCmdLine, nShowCmd, commandLineView)->Run();
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
