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

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Log.Windows.Implementation;

import <memory>;

export import PonyEngine.Log.Implementation;

import :OutputDebugStringSubLogger;

export namespace PonyEngine::Log
{
	struct PONY_DLL_EXPORT OutputDebugStringSubLoggerDeleter final
	{
		void operator ()(ISubLogger* subLogger) const noexcept;
	};

	using OutputDebugStringSubLoggerUniquePtr = std::unique_ptr<ISubLogger, OutputDebugStringSubLoggerDeleter>;

	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT OutputDebugStringSubLoggerUniquePtr CreateOutputDebugStringSubLogger();
}

namespace PonyEngine::Log
{
	void OutputDebugStringSubLoggerDeleter::operator()(ISubLogger* const subLogger) const noexcept
	{
		assert((dynamic_cast<OutputDebugStringSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type."));
		delete static_cast<OutputDebugStringSubLogger*>(subLogger);
	}

	OutputDebugStringSubLoggerUniquePtr CreateOutputDebugStringSubLogger()
	{
		return std::unique_ptr<ISubLogger, OutputDebugStringSubLoggerDeleter>(new OutputDebugStringSubLogger());
	}
}
