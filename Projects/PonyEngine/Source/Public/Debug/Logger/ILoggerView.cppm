/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.ILoggerView;

import <string>;
import <exception>;

import PonyEngine.Debug.ILoggerEntryView;

namespace PonyEngine::Debug
{
	/// <summary>
	/// Logger view interface. A Logger formats logs and sends them to its log entries.
	/// </summary>
	/// <remarks>
	///	This class is supposed to be pointed by external users.
	/// </remarks>
	export class ILoggerView
	{
	public:
		/// <summary>
		/// Formats and sends to log entries a usual log with the <paramref name="message"/>.
		/// </summary>
		/// <param name="message">Log message.</param>
		virtual void Log(const std::string& message) const noexcept = 0;

		/// <summary>
		/// Formats and sends to log entries a warning log with the <paramref name="message"/>.
		/// </summary>
		/// <param name="message">Log message.</param>
		virtual void LogWarning(const std::string& message) const noexcept = 0;

		/// <summary>
		/// Formats and sends to log entries an error log with the <paramref name="message"/>.
		/// </summary>
		/// <param name="message">Log message.</param>
		virtual void LogError(const std::string& message) const noexcept = 0;

		/// <summary>
		/// Formats and sends to log entries an exception log with the <paramref name="exception"/>.
		/// </summary>
		/// <param name="exception">Exception to be logged.</param>
		virtual void LogException(const std::exception& exception) const noexcept = 0;

		/// <summary>
		/// Adds a log entry.
		/// </summary>
		/// <param name="loggerEntry">Log entry to be added. Must be not nullptr.</param>
		virtual void AddLoggerEntry(ILoggerEntryView* loggerEntry) = 0;

		/// <summary>
		/// Removes a previously added log entry.
		/// </summary>
		/// <param name="loggerEntry">Log entry to be removed.</param>
		virtual void RemoveLoggerEntry(ILoggerEntryView* loggerEntry) = 0;

	protected:
		virtual ~ILoggerView() noexcept = default;
	};
}
