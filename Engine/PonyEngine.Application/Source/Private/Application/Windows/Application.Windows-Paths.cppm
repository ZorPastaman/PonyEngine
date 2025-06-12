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
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Application.Windows:Paths;

import std;

import PonyEngine.Application;
import PonyEngine.Utility;

export namespace PonyEngine::Application::Windows
{
	/// @brief Gets the Windows paths.
	/// @return Platform paths.
	[[nodiscard("Pure function")]]
	PlatformPaths GetPlatformPaths();

	/// @brief Gets a game data path. It's a directory where a game executable is.
	/// @return Game data path.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetGameDataPath();
	/// @brief Gets a game executable path. It's @p GetGameDataPath + a game executable name.
	/// @return Game executable path.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetExecutablePath();
	/// @brief Gets a local data path. It's a directory for files that the application produces.
	/// @return Local data path.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetLocalDataPath();
	/// @brief Gets a user data path. It's a directory for files that a user produces.
	/// @return User data path.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetUserDataPath();
}

namespace PonyEngine::Application::Windows
{
	/// @brief Gets a known path.
	/// @param folderId Folder id.
	/// @return Known path. It includes company and game folders.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetKnownPath(REFKNOWNFOLDERID folderId);

	PlatformPaths GetPlatformPaths()
	{
		return PlatformPaths
		{
			.gameData = GetGameDataPath(),
			.executable = GetExecutablePath(),
			.localData = GetLocalDataPath(),
			.userData = GetUserDataPath()
		};
	}

	std::filesystem::path GetGameDataPath()
	{
		return GetExecutablePath().parent_path();
	}

	std::filesystem::path GetExecutablePath()
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()))) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get module name. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}

	std::filesystem::path GetLocalDataPath()
	{
		return GetKnownPath(FOLDERID_LocalAppData);
	}

	std::filesystem::path GetUserDataPath()
	{
		return GetKnownPath(FOLDERID_SavedGames);
	}

	std::filesystem::path GetKnownPath(REFKNOWNFOLDERID folderId)
	{
		wchar_t* path = nullptr;
		try
		{
			if (const HRESULT result = SHGetKnownFolderPath(folderId, 0, nullptr, &path); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get known path. Result: '0x{:X}'.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			const auto answer = std::filesystem::path(path).append(PONY_STRINGIFY_VALUE(PONY_COMPANY_NAME)).append(PONY_STRINGIFY_VALUE(PONY_GAME_NAME));
			CoTaskMemFree(path);

			return answer;
		}
		catch (...)
		{
			CoTaskMemFree(path);

			throw;
		}
	}
}
