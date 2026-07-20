/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"
#include <KnownFolders.h>

export module PonyEngine.Application.Impl.Windows:Path;

import std;

import PonyEngine.Application.Impl;
import PonyEngine.Platform.Windows;

export namespace PonyEngine::Application::Windows
{
	[[nodiscard("Pure function")]]
	std::filesystem::path GetExecutablePath();
	[[nodiscard("Pure function")]]
	std::filesystem::path GetLocalDataDirectory();
	[[nodiscard("Pure function")]]
	std::filesystem::path GetUserDataDirectory();
	[[nodiscard("Pure function")]]
	std::filesystem::path GetTempDataDirectory();
}

namespace PonyEngine::Application::Windows
{
	std::filesystem::path GetExecutablePath()
	{
		return Platform::Windows::GetModulePath(nullptr).lexically_normal();
	}

	std::filesystem::path GetLocalDataDirectory()
	{
		return AddTail(Platform::Windows::GetKnownPath(FOLDERID_LocalAppData));
	}

	std::filesystem::path GetUserDataDirectory()
	{
		return AddTail(Platform::Windows::GetKnownPath(FOLDERID_SavedGames));
	}

	std::filesystem::path GetTempDataDirectory()
	{
		return AddTail(Platform::Windows::GetTemporaryPath());
	}
}
