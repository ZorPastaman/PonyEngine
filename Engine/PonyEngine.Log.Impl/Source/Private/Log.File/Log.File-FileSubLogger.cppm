/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.File:FileSubLogger;

import std;

import PonyEngine.Log.Extension;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger that writes logs to a file.
	class FileSubLogger final : public ISubLogger
	{
	public:
		/// @brief Creates a file sub-logger.
		/// @param path Log file path.
		[[nodiscard("Pure constructor")]]
		explicit FileSubLogger(const std::filesystem::path& path);
		FileSubLogger(const FileSubLogger&) = delete;
		FileSubLogger(FileSubLogger&&) = delete;

		~FileSubLogger() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

	private:
		std::ofstream logFile; ///< Log file.
	};
}

namespace PonyEngine::Log
{
	FileSubLogger::FileSubLogger(const std::filesystem::path& path) :
		logFile(path)
	{
		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::runtime_error("Failed to open log file.");
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
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On closing log file.");
			}
		}
	}

	void FileSubLogger::Begin()
	{
	}

	void FileSubLogger::End()
	{
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			logFile << logEntry;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On writing to file.");
		}
	}
}
