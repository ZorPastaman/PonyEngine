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

export module PonyEngine.Application.Impl:Process;

import std;

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Sets the process priority.
	/// @param priority Process priority.
	void SetProcessPriority(DWORD priority);
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	void SetProcessPriority(const DWORD priority)
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set process priority to '0x{:X}'. Error code: '0x{:X}'.", priority, GetLastError()));
		}
	}
}
#endif
