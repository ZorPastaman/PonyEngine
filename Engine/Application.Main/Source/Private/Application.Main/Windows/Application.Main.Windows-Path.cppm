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

export module PonyEngine.Application.Main.Windows:Path;

import std;

import PonyEngine.Application.Main;
import PonyEngine.File;

export namespace PonyEngine::Application::Windows
{
	/// @brief Gets the executable file path.
	/// @return Executable file path.
	[[nodiscard("Pure function")]]
	std::filesystem::path ExecutableFile();

	/// @brief Gets the local data directory.
	/// @return Local data directory.
	[[nodiscard("Pure function")]]
	std::filesystem::path LocalDataDirectory();
	/// @brief Gets the user data directory.
	/// @return User data directory.
	[[nodiscard("Pure function")]]
	std::filesystem::path UserDataDirectory();
	/// @brief Gets the temporary data directory.
	/// @return Temporary data directory.
	[[nodiscard("Pure function")]]
	std::filesystem::path TempDataDirectory();
}

namespace PonyEngine::Application::Windows
{
	/// @brief Creates a tailed path.
	/// @param path Path.
	/// @return Tailed path.
	[[nodiscard("Pure function")]]
	std::filesystem::path CreateTailedPath(const std::filesystem::path& path);

	std::filesystem::path ExecutableFile()
	{
		return File::Windows::GetModulePath(nullptr).lexically_normal();
	}

	std::filesystem::path LocalDataDirectory()
	{
		return CreateTailedPath(File::Windows::GetKnownPath(FOLDERID_LocalAppData));
	}

	std::filesystem::path UserDataDirectory()
	{
		return CreateTailedPath(File::Windows::GetKnownPath(FOLDERID_SavedGames));
	}

	std::filesystem::path TempDataDirectory()
	{
		return CreateTailedPath(File::Windows::GetTemporaryPath());
	}

	std::filesystem::path CreateTailedPath(const std::filesystem::path& path)
	{
		const std::filesystem::path tailedPath = AddTail(path);
		std::filesystem::create_directories(tailedPath);

		return tailedPath;
	}
}
