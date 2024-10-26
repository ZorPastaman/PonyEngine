/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyDebug.Log.Implementation;

export import PonyDebug.Log.Factory;

import <filesystem>;
import <utility>;

import PonyBase.Memory;

import :ConsoleSubLogger;
import :FileSubLogger;
import :Logger;

export namespace PonyDebug::Log
{
	/// @brief Creates a logger.
	/// @param params Logger parameters.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT LoggerData CreateLogger(const LoggerParams& params);

	/// @brief Creates a console sub-logger.
	/// @param params Console sub-logger parameters.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ConsoleSubLoggerData CreateConsoleSubLogger(const ConsoleSubLoggerParams& params);
	/// @brief Creates a file sub-logger with the @p path.
	/// @param params File sub-logger parameters.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FileSubLoggerData CreateFileSubLogger(const FileSubLoggerParams& params);
}

namespace PonyDebug::Log
{
	LoggerData CreateLogger(const LoggerParams&)
	{
		auto logger = PonyBase::Memory::UniquePointer<Logger>::Create();

		return LoggerData{.logger = PonyBase::Memory::UniquePointer<ILogger>(std::move(logger))};
	}

	ConsoleSubLoggerData CreateConsoleSubLogger(const ConsoleSubLoggerParams&)
	{
		auto consoleSubLogger = PonyBase::Memory::UniquePointer<ConsoleSubLogger>::Create();

		return ConsoleSubLoggerData{.subLogger = PonyBase::Memory::UniquePointer<ISubLogger>(std::move(consoleSubLogger))};
	}

	FileSubLoggerData CreateFileSubLogger(const FileSubLoggerParams& params)
	{
		auto fileSubLogger = PonyBase::Memory::UniquePointer<FileSubLogger>::Create(params.logPath);

		return FileSubLoggerData{.subLogger = PonyBase::Memory::UniquePointer<ISubLogger>(std::move(fileSubLogger))};
	}
}
