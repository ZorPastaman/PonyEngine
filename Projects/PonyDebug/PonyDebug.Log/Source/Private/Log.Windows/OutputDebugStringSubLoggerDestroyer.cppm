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

export module PonyDebug.Log.Windows.Implementation:OutputDebugStringSubLoggerDestroyer;

import PonyDebug.Log.Factory;

import :OutputDebugStringSubLogger;

export namespace PonyDebug::Log
{
	/// @brief Output debug string sub-logger destroyer.
	struct OutputDebugStringSubLoggerDestroyer final : ISubLoggerDestroyer
	{
		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(ISubLogger* subLogger) const noexcept override;

		virtual void Destroy(ISubLogger* subLogger) noexcept override;
	};
}

namespace PonyDebug::Log
{
	bool OutputDebugStringSubLoggerDestroyer::IsCompatible(ISubLogger* const subLogger) const noexcept
	{
		return dynamic_cast<OutputDebugStringSubLogger*>(subLogger);
	}

	void OutputDebugStringSubLoggerDestroyer::Destroy(ISubLogger* const subLogger) noexcept
	{
		assert(dynamic_cast<OutputDebugStringSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type.");
		delete static_cast<OutputDebugStringSubLogger*>(subLogger);
	}
}
