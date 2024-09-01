/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import <exception>;

import PonyEngine.Common;
import PonyEngine.Log;

import Application.Windows;

int APIENTRY wWinMain(const HINSTANCE, const HINSTANCE, const LPWSTR, const int)
{
	try
	{
		return Application::WindowsApplication().Run();
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main().");
		return static_cast<int>(PonyEngine::Common::ExitCodes::ApplicationException);
	}
}
