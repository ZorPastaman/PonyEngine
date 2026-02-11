/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Console.h"

export module PonyEngine.Log.File.Impl:FileSubLogger;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log::File
{
	/// @brief Sub-logger that writes logs to a file.
	class FileSubLogger final : public ISubLogger
	{
	public:
		/// @brief Creates a file sub-logger.
		/// @param logger Logger context.
		/// @param path Log file path.
		[[nodiscard("Pure constructor")]]
		FileSubLogger(ILoggerContext& logger, const std::filesystem::path& path);
		FileSubLogger(const FileSubLogger&) = delete;
		FileSubLogger(FileSubLogger&&) = delete;

		~FileSubLogger() noexcept;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

	private:
		ILoggerContext* logger; ///< Logger context.

		std::ofstream logFile; ///< Log file.
	};
}

namespace PonyEngine::Log::File
{
	FileSubLogger::FileSubLogger(ILoggerContext& logger, const std::filesystem::path& path) :
		logger{&logger},
		logFile(path)
	{
		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::runtime_error("Failed to open log file");
		}
	}

	FileSubLogger::~FileSubLogger() noexcept
	{
		if (logFile.is_open()) [[likely]]
		{
			try
			{
				logFile.close();
			}
			catch (...)
			{
				PONY_CONSOLE_X(*logger, std::current_exception(), "On closing log file.");
			}
		}
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			logFile << logEntry.formattedMessage;
		}
		catch (...)
		{
			PONY_CONSOLE_X(*logger, std::current_exception(), "On writing to log file.");
		}
	}
}
