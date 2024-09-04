/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <exception>

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

import PonyBase.Core;

import PonyDebug.Log;

import Application.Windows;

int APIENTRY wWinMain(const HINSTANCE, const HINSTANCE, const LPWSTR, const int)
{
	try
	{
		const auto application = Application::WindowsApplication();

		try
		{
			return application.Run();
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On ticking application.");

			return static_cast<int>(PonyBase::Core::ExitCodes::ApplicationTickException);
		}
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main().");

		return static_cast<int>(PonyBase::Core::ExitCodes::MainException);
	}
}
