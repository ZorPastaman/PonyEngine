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

export module PonyEngine.Application.Windows:Process;

import std;

import PonyEngine.Utility;

export namespace PonyEngine::Application::Windows
{
	/// @brief Sets the process priority.
	/// @param priority Priority to set.
	void SetProcessPriority(DWORD priority);
}

namespace PonyEngine::Application::Windows
{
	void SetProcessPriority(const DWORD priority)
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority))
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set process priority to '0x{:X}'. Error code: '0x{:X}'.", priority, GetLastError()));
		}
	}
}
