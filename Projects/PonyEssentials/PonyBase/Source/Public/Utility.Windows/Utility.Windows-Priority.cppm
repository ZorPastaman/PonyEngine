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

export module PonyBase.Utility.Windows:Priority;

import <stdexcept>;

import PonyBase.Utility;

export namespace PonyBase::Utility::Windows
{
	/// @brief Sets the process priority.
	/// @param priority Priority to set.
	void SetProcessPriority(DWORD priority);
}

namespace PonyBase::Utility::Windows
{
	void SetProcessPriority(const DWORD priority)
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority))
		{
			throw std::runtime_error(SafeFormat("Failed to set process priority to '0x{:X}'. Error code: '0x{:X}'.", priority, GetLastError()));
		}
	}
}
