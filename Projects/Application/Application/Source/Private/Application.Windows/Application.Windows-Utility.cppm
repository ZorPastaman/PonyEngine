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

#include "PonyDebug/Log/Log.h"

export module Application.Windows:Utility;

import PonyDebug.Log;

export namespace Application // TODO: Move to base
{
	/// @brief Sets the process priority.
	/// @param priority Priority to set.
	void SetProcessPriority(DWORD priority) noexcept;
}

namespace Application
{
	void SetProcessPriority(const DWORD priority) noexcept
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority))
		{
			PONY_CONSOLE(PonyDebug::Log::LogType::Error, "Failed to set current process priority to '0x{:X}'. Error code: '0x{:X}'.", priority, GetLastError());
		}

		PONY_CONSOLE(PonyDebug::Log::LogType::Info, "Current process priority set to '0x{:X}'.", priority);
	}
}
