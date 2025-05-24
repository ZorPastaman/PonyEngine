/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyBase.Utility.Windows:Module;

import <stdexcept>;

import PonyBase.Utility;

export namespace PonyBase::Utility::Windows
{
	/// @brief Gets this dll module.
	/// @return Dll module.
	[[nodiscard("Pure function")]]
	HMODULE GetModule();
}

namespace PonyBase::Utility::Windows
{
	HMODULE GetModule()
	{
		HMODULE moduleHandle;
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&GetModule), &moduleHandle) || !moduleHandle)
		{
			throw std::runtime_error(SafeFormat("Failed to find dll module. Error code: '0x{:X}'.", GetLastError()));
		}

		return moduleHandle;
	}
}
