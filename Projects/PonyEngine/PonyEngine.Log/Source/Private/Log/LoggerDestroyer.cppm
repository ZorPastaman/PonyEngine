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

export module PonyEngine.Log.Implementation:LoggerDestroyer;

import PonyEngine.Log.Factory;

import :Logger;

export namespace PonyEngine::Log
{
	/// @brief Logger destroyer.
	struct LoggerDestroyer final : ILoggerDestroyer
	{
		virtual void Destroy(ILogger* logger) noexcept override;
	};
}

namespace PonyEngine::Log
{
	void LoggerDestroyer::Destroy(ILogger* const logger) noexcept
	{
		assert(dynamic_cast<Logger*>(logger) && "Tried to destroy a logger of the wrong type.");
		delete static_cast<Logger*>(logger);
	}
}