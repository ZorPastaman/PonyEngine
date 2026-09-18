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

export module PonyEngine.FileSystem.WinAPI:Module;

import std;

export namespace PonyEngine::FileSystem
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
}

namespace PonyEngine::FileSystem
{
	HMODULE GetModule()
	{
		HMODULE moduleHandle;
		if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCSTR>(&GetModule), &moduleHandle) || !moduleHandle)
		{
			throw std::runtime_error(std::format("Failed to find module: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return moduleHandle;
	}

	std::filesystem::path GetModulePath(const HMODULE module)
	{
		auto path = std::array<wchar_t, MAX_PATH>();
		if (!GetModuleFileNameW(module, path.data(), static_cast<DWORD>(path.size()))) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get module name: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return std::filesystem::path(path.data());
	}
}
