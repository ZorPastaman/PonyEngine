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

export module PonyDebug.Log.Implementation:LoggerDestroyer;

import PonyDebug.Log.Factory;

import :Logger;

export namespace PonyDebug::Log
{
	/// @brief Logger destroyer.
	struct LoggerDestroyer final : ILoggerDestroyer
	{
		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(ILogger* logger) const noexcept override;

		virtual void Destroy(ILogger* logger) noexcept override;
	};
}

namespace PonyDebug::Log
{
	bool LoggerDestroyer::IsCompatible(ILogger* const logger) const noexcept
	{
		return dynamic_cast<Logger*>(logger);
	}

	void LoggerDestroyer::Destroy(ILogger* const logger) noexcept
	{
		assert(dynamic_cast<Logger*>(logger) && "Tried to destroy a logger of the wrong type.");
		delete static_cast<Logger*>(logger);
	}
}
