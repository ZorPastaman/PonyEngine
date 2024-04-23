/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:ISubLogger;

import PonyEngine.Utility;

import :LogEntry;

export namespace PonyEngine::Debug::Log
{
	/// @brief SubLogger interface.
	/// @details The sub-logger writes received logs to something.
	class ISubLogger : public Utility::INamed
	{
	public:
		/// @brief Logs the @p logEntry to something.
		/// @param logEntry Log entry to log.
		virtual void Log(const LogEntry& logEntry) noexcept = 0;

	protected:
		~ISubLogger() noexcept = default;
	};
}
