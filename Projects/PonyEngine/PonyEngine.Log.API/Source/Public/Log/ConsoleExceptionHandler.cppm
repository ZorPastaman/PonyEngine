/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log:ConsoleExceptionHandler;

import <exception>;

import :LogConsoleHelper;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Passes exceptions to @p PONY_CONSOLE_E_S.
	struct ConsoleExceptionHandler final
	{
		/// @brief Passes exceptions to @p PONY_CONSOLE_E_S.
		/// @param e Exception to pass.
		void operator ()(const std::exception& e) const noexcept;
	};
}

namespace PonyEngine::Log
{
	void ConsoleExceptionHandler::operator ()(const std::exception& e) const noexcept
	{
		PONY_CONSOLE_E_S(e);
	}
}
