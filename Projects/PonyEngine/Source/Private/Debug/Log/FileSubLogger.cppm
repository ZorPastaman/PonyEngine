/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <fstream>

export module PonyEngine.Debug.Log.FileSubLogger;

import <filesystem>;
import <iostream>;

import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogEntry;

namespace PonyEngine::Debug::Log
{
	/// <summary>
	/// Logger entry that logs to a file.
	/// </summary>
	export class FileSubLogger final : public ISubLogger
	{
	public:
		/// <param name="logPath">Path to a log file.</param>
		FileSubLogger(const std::filesystem::path& logPath);
		FileSubLogger(const FileSubLogger&) = delete;
		FileSubLogger(FileSubLogger&& other);

		virtual ~FileSubLogger();

		virtual void Log(const LogEntry& logEntry) noexcept override;

	private:
		std::ofstream m_logFile;
	};

	FileSubLogger::FileSubLogger(const std::filesystem::path& logPath) :
		m_logFile(logPath)
	{
		if (!m_logFile.is_open())
		{
			std::cerr << logPath << " isn't open. Logs won't be written to file!" << std::endl;
		}
	}

	FileSubLogger::FileSubLogger(FileSubLogger&& other) :
		m_logFile(std::move(other.m_logFile))
	{
		if (!m_logFile.is_open())
		{
			std::cerr << "Moved non-opened logFile. Logs won't be written to file!" << std::endl;
		}
	}

	FileSubLogger::~FileSubLogger()
	{
		m_logFile.close();
	}

	void FileSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			m_logFile << logEntry.message << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << " on writing to a log file.";
		}
	}
}
