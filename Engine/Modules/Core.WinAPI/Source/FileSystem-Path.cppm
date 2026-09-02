/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <shlobj.h>

export module PonyEngine.FileSystem.WinAPI:Path;

import std;

import PonyEngine.Format.WinAPI;

export namespace PonyEngine::FileSystem
{
	/// @brief Gets a known path.
	/// @param folderId Folder id.
	/// @return Known path.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetKnownPath(REFKNOWNFOLDERID folderId);
	/// @brief Gets a temporary directory.
	/// @return Temporary directory.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetTemporaryPath();
}

namespace PonyEngine::FileSystem
{
	std::filesystem::path GetKnownPath(REFKNOWNFOLDERID folderId)
	{
		wchar_t* pathRaw = nullptr;
		if (const HRESULT result = SHGetKnownFolderPath(folderId, 0, nullptr, &pathRaw); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get known path: FolderID = '{}'; Result = '0x{:X}'", folderId, static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		const auto path = std::unique_ptr<wchar_t, decltype(&CoTaskMemFree)>(pathRaw, &CoTaskMemFree);

		return std::filesystem::path(path.get());
	}

	std::filesystem::path GetTemporaryPath()
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetTempPath2W(MAX_PATH, path.data()))
		{
			throw std::runtime_error(std::format("Failed to get temporary path: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}
}
