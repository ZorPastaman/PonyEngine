/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Log.Implementation:ConsoleSubLoggerDestroyer;

import PonyEngine.Log.Factory;

import :ConsoleSubLogger;

export namespace PonyEngine::Log
{
	/// @brief Console sub-logger destroyer.
	struct ConsoleSubLoggerDestroyer final : ISubLoggerDestroyer
	{
		virtual void Destroy(ISubLogger* subLogger) noexcept override;
	};
}

namespace PonyEngine::Log
{
	void ConsoleSubLoggerDestroyer::Destroy(ISubLogger* const subLogger) noexcept
	{
		assert(dynamic_cast<ConsoleSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type.");
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}
}
