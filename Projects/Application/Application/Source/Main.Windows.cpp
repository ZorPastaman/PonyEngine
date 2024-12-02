/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <format>
#include <exception>

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

import PonyBase.Core;
import PonyBase.StringUtility;

import PonyDebug.Log;

import Application.Windows;

int APIENTRY wWinMain(const HINSTANCE, const HINSTANCE, const LPWSTR, const int)
{
	try
	{
		auto application = Application::WindowsApplication();

		try
		{
			int applicationResult = application.Run();
			if (applicationResult != 0)
			{
				MessageBoxW(nullptr, std::format(L"The application finished with the code '{}'.", applicationResult).c_str(), L"Pony Engine - Application Error", MB_OK | MB_ICONERROR);
			}

			return applicationResult;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On running application.");
			MessageBoxW(nullptr, std::format(L"The application threw the exception: '{}'.", PonyBase::Utility::ConvertToWideString(e.what())).c_str(), L"Pony Engine - Application Exception", MB_OK | MB_ICONERROR);

			return static_cast<int>(PonyBase::Core::ExitCodes::ApplicationTickException);
		}
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main().");
		MessageBoxW(nullptr, std::format(L"The main threw the exception: '{}'.", PonyBase::Utility::ConvertToWideString(e.what())).c_str(), L"Pony Engine - Main Exception", MB_OK | MB_ICONERROR);

		return static_cast<int>(PonyBase::Core::ExitCodes::MainException);
	}
}
