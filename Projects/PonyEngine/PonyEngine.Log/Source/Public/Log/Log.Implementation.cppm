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

export module PonyEngine.Log.Implementation;

import <filesystem>;
import <memory>;

import PonyEngine.Log;

import :ConsoleSubLogger;
import :FileSubLogger;
import :Logger;

export namespace PonyEngine::Log
{
	/// @brief Logger deleter.
	struct PONY_DLL_EXPORT LoggerDeleter final
	{
		/// @brief Deletes the @p logger.
		/// @param logger Logger to delete.
		void operator ()(ILogger* logger) const noexcept;
	};

	/// @brief Console sub-logger deleter.
	struct PONY_DLL_EXPORT ConsoleSubLoggerDeleter final
	{
		/// @brief Deletes the @p subLogger.
		/// @param subLogger Console sub-logger to delete.
		void operator ()(ISubLogger* subLogger) const noexcept;
	};

	/// @brief File sub-logger deleter.
	struct PONY_DLL_EXPORT FileSubLoggerDeleter final
	{
		/// @brief Deletes the @p subLogger.
		/// @param subLogger File sub-logger to delete.
		void operator ()(ISubLogger* subLogger) const noexcept;
	};

	using LoggerUniquePtr = std::unique_ptr<ILogger, LoggerDeleter>; ///< Logger unique_ptr typedef.
	using ConsoleSubLoggerUniquePtr = std::unique_ptr<ISubLogger, ConsoleSubLoggerDeleter>; ///< Console sub-logger unique_ptr typedef.
	using FileSubLoggerUniquePtr = std::unique_ptr<ISubLogger, FileSubLoggerDeleter>; ///< File sub-logger unique_ptr typedef.

	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT LoggerUniquePtr CreateLogger();

	/// @brief Creates a console sub-logger.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ConsoleSubLoggerUniquePtr CreateConsoleSubLogger();

	/// @brief Creates a file sub-logger with the @p path.
	/// @param path Log file path.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FileSubLoggerUniquePtr CreateFileSubLogger(const std::filesystem::path& path);
}

namespace PonyEngine::Log
{
	/// @brief Destroys the logger.
	/// @param logger Logger to destroy.
	void DestroyLogger(ILogger* logger) noexcept;

	/// @brief Destroys the console sub-logger.
	/// @param subLogger Console sub-logger to destroy.
	void DestroyConsoleSubLogger(ISubLogger* subLogger) noexcept;

	/// @brief Destroys the file sub-logger.
	/// @param subLogger File sub-logger to destroy.
	void DestroyFileSubLogger(ISubLogger* subLogger) noexcept;

	void LoggerDeleter::operator ()(ILogger* const logger) const noexcept
	{
		DestroyLogger(logger);
	}

	void ConsoleSubLoggerDeleter::operator ()(ISubLogger* const subLogger) const noexcept
	{
		DestroyConsoleSubLogger(subLogger);
	}

	void FileSubLoggerDeleter::operator ()(ISubLogger* const subLogger) const noexcept
	{
		DestroyFileSubLogger(subLogger);
	}

	LoggerUniquePtr CreateLogger()
	{
		return std::unique_ptr<ILogger, LoggerDeleter>(new Logger());
	}

	ConsoleSubLoggerUniquePtr CreateConsoleSubLogger()
	{
		return std::unique_ptr<ISubLogger, ConsoleSubLoggerDeleter>(new ConsoleSubLogger());
	}

	FileSubLoggerUniquePtr CreateFileSubLogger(const std::filesystem::path& path)
	{
		return std::unique_ptr<ISubLogger, FileSubLoggerDeleter>(new FileSubLogger(path));
	}

	void DestroyLogger(ILogger* const logger) noexcept
	{
		assert((dynamic_cast<Logger*>(logger) && "Tried to destroy a logger of the wrong type."));
		delete static_cast<Logger*>(logger);
	}

	void DestroyConsoleSubLogger(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<ConsoleSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type."));
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}

	void DestroyFileSubLogger(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<FileSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type."));
		delete static_cast<FileSubLogger*>(subLogger);
	}
}
