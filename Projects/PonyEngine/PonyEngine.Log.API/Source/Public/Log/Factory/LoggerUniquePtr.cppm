/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Factory:LoggerUniquePtr;

import <memory>;

import :ILoggerDestroyer;

export namespace PonyEngine::Log
{
	/// @brief Logger deleter.
	class LoggerDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoggerDeleter() noexcept = default;
		/// @brief Creates a @p LoggerDeleter.
		/// @param loggerDestroyer Logger destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit LoggerDeleter(ILoggerDestroyer& loggerDestroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		LoggerDeleter(const LoggerDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LoggerDeleter(LoggerDeleter&& other) noexcept = default;

		~LoggerDeleter() noexcept = default;

		/// @brief Gets the logger destroyer.
		/// @return Logger destroyer.
		[[nodiscard("Pure function")]]
		ILoggerDestroyer* LoggerDestroyer() const noexcept;

		/// @brief Destroys the @p logger.
		/// @param logger Logger to destroy.
		void operator ()(ILogger* logger) const noexcept;

		LoggerDeleter& operator =(const LoggerDeleter& other) noexcept = default;
		LoggerDeleter& operator =(LoggerDeleter&& other) noexcept = default;

	private:
		ILoggerDestroyer* loggerDestroyer; ///< Logger destroyer.
	};

	using LoggerUniquePtr = std::unique_ptr<ILogger, LoggerDeleter>; ///< Logger unique_ptr typedef.
}

namespace PonyEngine::Log
{
	LoggerDeleter::LoggerDeleter(ILoggerDestroyer& loggerDestroyer) noexcept :
		loggerDestroyer{&loggerDestroyer}
	{
	}

	ILoggerDestroyer* LoggerDeleter::LoggerDestroyer() const noexcept
	{
		return loggerDestroyer;
	}

	void LoggerDeleter::operator ()(ILogger* const logger) const noexcept
	{
		if (loggerDestroyer)
		{
			loggerDestroyer->Destroy(logger);
		}
	}

}
