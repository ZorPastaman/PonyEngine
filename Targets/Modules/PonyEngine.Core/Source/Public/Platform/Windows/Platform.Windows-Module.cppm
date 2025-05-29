/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <stdexcept>;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Platform.Windows:Module;

import PonyEngine.Utility;

export namespace PonyEngine::Platform::Windows
{
	/// @brief Gets this dll module.
	/// @return Dll module.
	[[nodiscard("Pure function")]]
	HMODULE GetModule();
}

namespace PonyEngine::Platform::Windows
{
	HMODULE GetModule()
	{
		HMODULE moduleHandle;
		if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCSTR>(&GetModule), &moduleHandle) || !moduleHandle)
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to find module. Error code: '0x{:X}'.", GetLastError()));
		}

		return moduleHandle;
	}
}
