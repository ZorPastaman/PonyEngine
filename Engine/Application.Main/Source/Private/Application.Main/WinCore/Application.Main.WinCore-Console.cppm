/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/WinCore/Framework.h"

export module PonyEngine.Application.Main.WinCore:Console;

import std;

export namespace PonyEngine::Application::WinCore
{
	/// @brief Log to WinCore console.
	/// @param message Message.
	void LogToConsole(std::string_view message) noexcept;
}

namespace PonyEngine::Application::WinCore
{
	void LogToConsole(const std::string_view message) noexcept
	{
		OutputDebugStringA(message.data());
	}
}
