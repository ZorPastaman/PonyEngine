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

export module PonyEngine.Application.Impl.Windows:Process;

import std;

export namespace PonyEngine::Application::Windows
{
	/// @brief Sets the process priority.
	/// @param priority Process priority.
	void SetProcessPriority(DWORD priority);
}

namespace PonyEngine::Application::Windows
{
	void SetProcessPriority(const DWORD priority)
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set process priority to '0x{:X}': ErrorCode = '0x{:X}'", priority, GetLastError()));
		}
	}
}
