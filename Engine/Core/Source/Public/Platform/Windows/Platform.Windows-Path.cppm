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

export module PonyEngine.Platform.Windows:Path;

import std;

import PonyEngine.Platform.WinCore;
import PonyEngine.Utility;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets a module path.
	/// @param module Module. If it's null, the path to the executable module of the current process is returned.
	/// @return Module path.
	[[nodiscard("Pure function")]]
	std::filesystem::path GetModulePath(HMODULE module);

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

namespace PonyEngine::Platform::Windows
{
	std::filesystem::path GetModulePath(const HMODULE module)
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetModuleFileNameW(module, path.data(), static_cast<DWORD>(path.size()))) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get module name. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}

	std::filesystem::path GetKnownPath(REFKNOWNFOLDERID folderId)
	{
		wchar_t* pathRaw = nullptr;
		if (const HRESULT result = SHGetKnownFolderPath(folderId, 0, nullptr, &pathRaw); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get known path. FolderID: '{}'. Result: '0x{:X}'.", folderId, static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		const auto path = std::unique_ptr<wchar_t, decltype(&CoTaskMemFree)>(pathRaw, &CoTaskMemFree);

		return std::filesystem::path(path.get());
	}

	std::filesystem::path GetTemporaryPath()
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetTempPath2W(MAX_PATH, path.data()))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get temp directory. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}
}
