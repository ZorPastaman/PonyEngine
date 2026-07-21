/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.File.Impl:FileSubLogger;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log::File
{
	/// @brief Sub-logger that writes logs to a file.
	class FileSubLogger final : public ILogger
	{
	public:
		/// @brief Creates a file sub-logger.
		/// @param logger Logger context.
		/// @param path Log file path.
		[[nodiscard("Pure constructor")]]
		FileSubLogger(const ILoggerContext& logger, const std::filesystem::path& path);
		FileSubLogger(const FileSubLogger&) = delete;
		FileSubLogger(FileSubLogger&&) = delete;

		~FileSubLogger() noexcept = default;

		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept override;

		FileSubLogger& operator =(const FileSubLogger&) = delete;
		FileSubLogger& operator =(FileSubLogger&&) = delete;

	private:
		const ILoggerContext* logger; ///< Logger context.

		std::ofstream logFile; ///< Log file.
	};
}

namespace PonyEngine::Log::File
{
	FileSubLogger::FileSubLogger(const ILoggerContext& logger, const std::filesystem::path& path) :
		logger{&logger},
		logFile(path)
	{
		if (!logFile.is_open()) [[unlikely]]
		{
			throw std::runtime_error("Failed to open log file");
		}
	}

	void FileSubLogger::Log(const std::string_view formattedMessage, const LogEntry& logEntry) noexcept
	{
		try
		{
			logFile << formattedMessage;
		}
		catch (...)
		{
		}
	}
}
