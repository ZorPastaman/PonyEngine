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

export module PonyEngine.Log.Implementation:FileSubLoggerDestroyer;

import PonyEngine.Log.Factory;

import :FileSubLogger;

export namespace PonyEngine::Log
{
	/// @brief File sub-logger destroyer.
	struct FileSubLoggerDestroyer final : ISubLoggerDestroyer
	{
		virtual void Destroy(ISubLogger* subLogger) noexcept override;
	};
}

namespace PonyEngine::Log
{
	void FileSubLoggerDestroyer::Destroy(ISubLogger* const subLogger) noexcept
	{
		assert(dynamic_cast<FileSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type.");
		delete static_cast<FileSubLogger*>(subLogger);
	}
}
