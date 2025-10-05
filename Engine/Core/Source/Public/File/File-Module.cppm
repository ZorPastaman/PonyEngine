/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.File:Module;

import std;

import PonyEngine.Text;

#if PONY_WINDOWS
export namespace PonyEngine::File::Windows
{
	/// @brief Gets this exe/dll module.
	/// @return Exe/dll module.
	[[nodiscard("Pure function")]]
	HMODULE GetModule();
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::File::Windows
{
	HMODULE GetModule()
	{
		HMODULE moduleHandle;
		if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCSTR>(&GetModule), &moduleHandle) || !moduleHandle)
		{
			throw std::runtime_error(Text::FormatSafe("Failed to find module. Error code: '0x{:X}'.", GetLastError()));
		}

		return moduleHandle;
	}
}
#endif
