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

export import PonyEngine.Log.Factory;

import :ConsoleSubLogger;
import :FileSubLogger;
import :Logger;

export namespace PonyEngine::Log
{
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

	using ConsoleSubLoggerUniquePtr = std::unique_ptr<ISubLogger, ConsoleSubLoggerDeleter>; ///< Console sub-logger unique_ptr typedef.
	using FileSubLoggerUniquePtr = std::unique_ptr<ISubLogger, FileSubLoggerDeleter>; ///< File sub-logger unique_ptr typedef.

	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT LoggerUniquePtr CreateLogger(); // TODO: Return struct with unique_ptr and interfaces.

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
	/// @brief Logger destroyer.
	struct LoggerDestroyer final : ILoggerDestroyer
	{
		/// @brief Destroys the @p logger.
		/// @param logger Logger to destroy.
		virtual void Destroy(ILogger* logger) noexcept override;
	}
	LoggerDestroyer;

	void ConsoleSubLoggerDeleter::operator ()(ISubLogger* const subLogger) const noexcept
	{
		assert((dynamic_cast<ConsoleSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type."));
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}

	void FileSubLoggerDeleter::operator ()(ISubLogger* const subLogger) const noexcept
	{
		assert((dynamic_cast<FileSubLogger*>(subLogger) && "Tried to destroy a sub-logger of the wrong type."));
		delete static_cast<FileSubLogger*>(subLogger);
	}

	LoggerUniquePtr CreateLogger()
	{
		return LoggerUniquePtr(new Logger(), LoggerDeleter(LoggerDestroyer));
	}

	ConsoleSubLoggerUniquePtr CreateConsoleSubLogger()
	{
		return std::unique_ptr<ISubLogger, ConsoleSubLoggerDeleter>(new ConsoleSubLogger());
	}

	FileSubLoggerUniquePtr CreateFileSubLogger(const std::filesystem::path& path)
	{
		return std::unique_ptr<ISubLogger, FileSubLoggerDeleter>(new FileSubLogger(path));
	}

	void LoggerDestroyer::Destroy(ILogger* const logger) noexcept
	{
		assert((dynamic_cast<Logger*>(logger) && "Tried to destroy a logger of the wrong type."));
		delete static_cast<Logger*>(logger);
	}
}
