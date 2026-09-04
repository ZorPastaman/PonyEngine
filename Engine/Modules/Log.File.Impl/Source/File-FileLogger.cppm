/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.File.Impl:FileLogger;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log::File
{
	/// @brief Logger that logs to a file.
	class FileLogger final : public ILogger
	{
	public:
		/// @brief Creates a file logger.
		/// @param path Log file path.
		[[nodiscard("Pure constructor")]]
		explicit FileLogger(const std::filesystem::path& path);
		FileLogger(const FileLogger&) = delete;
		FileLogger(FileLogger&&) = delete;

		~FileLogger() noexcept = default;

		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept override;

		FileLogger& operator =(const FileLogger&) = delete;
		FileLogger& operator =(FileLogger&&) = delete;

	private:
		std::ofstream logFile; ///< Log file.
	};
}

namespace PonyEngine::Log::File
{
	FileLogger::FileLogger(const std::filesystem::path& path) :
		logFile(path)
	{
		if (!logFile) [[unlikely]]
		{
			throw std::runtime_error("Failed to open log file");
		}
	}

	void FileLogger::Log(const std::string_view formattedMessage, const LogEntry& logEntry) noexcept
	{
		try
		{
			logFile << formattedMessage;
		}
		catch (...)
		{
			// Strange but nothing to do.
		}
	}
}
