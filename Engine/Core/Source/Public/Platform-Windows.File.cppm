/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Storage.h"

export module PonyEngine.Platform:Windows.File;

import std;

import :Windows.GUID;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets this exe/dll module.
	/// @return Exe/dll module.
	[[nodiscard("Pure function")]]
	HMODULE GetModule();

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
	HMODULE GetModule()
	{
		HMODULE moduleHandle;
		if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCSTR>(&GetModule), &moduleHandle) || !moduleHandle)
		{
			throw std::runtime_error(std::format("Failed to find module. Error code: '0x{:X}'.", GetLastError()));
		}

		return moduleHandle;
	}

	std::filesystem::path GetModulePath(const HMODULE module)
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetModuleFileNameW(module, path.data(), static_cast<DWORD>(path.size()))) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get module name. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}

	std::filesystem::path GetKnownPath(REFKNOWNFOLDERID folderId)
	{
		wchar_t* pathRaw = nullptr;
		if (const HRESULT result = SHGetKnownFolderPath(folderId, 0, nullptr, &pathRaw); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get known path. FolderID: '{}'. Result: '0x{:X}'.", folderId, static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		const auto path = std::unique_ptr<wchar_t, decltype(&CoTaskMemFree)>(pathRaw, &CoTaskMemFree);

		return std::filesystem::path(path.get());
	}

	std::filesystem::path GetTemporaryPath()
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetTempPath2W(MAX_PATH, path.data()))
		{
			throw std::runtime_error(std::format("Failed to get temporary path. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}
}
