/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <stdexcept>

#include "PonyEngine/Platform/Windows/Framework.h"

export module Application.Windows:Process;

import PonyEngine.Utility;

export namespace Application::Windows
{
	/// @brief Sets the process priority.
	/// @param priority Priority to set.
	void SetProcessPriority(DWORD priority);
}

namespace Application::Windows
{
	void SetProcessPriority(const DWORD priority)
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority))
		{
			throw std::runtime_error(PonyEngine::Utility::SafeFormat("Failed to set process priority to '0x{:X}'. Error code: '0x{:X}'.", priority, GetLastError()));
		}
	}
}
