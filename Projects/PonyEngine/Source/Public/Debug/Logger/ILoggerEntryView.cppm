/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.ILoggerEntryView;

import <string>;
import <exception>;

namespace PonyEngine::Debug
{
	/// <summary>
	/// Logger entry view interface. A log entry accepts formatted logs from its logger and prints them.
	/// </summary>
	/// <remarks>
	///	This class is supposed to be pointed by external users.
	/// </remarks>
	export class ILoggerEntryView
	{
	public:
		/// <summary>
		/// Prints a usual log.
		/// </summary>
		/// <param name="log">Log to be printed.</param>
		virtual void Log(const std::string& log) noexcept = 0;

		/// <summary>
		/// Prints a warning log.
		/// </summary>
		/// <param name="log">Log to be printed.</param>
		virtual void LogWarning(const std::string& log) noexcept = 0;

		/// <summary>
		/// Prints an error log.
		/// </summary>
		/// <param name="log">Log to be printed.</param>
		virtual void LogError(const std::string& log) noexcept = 0;

		/// <summary>
		/// Prints an exception log.
		/// </summary>
		/// <param name="log">Log to be printed.</param>
		/// <param name="exception">Exception which the log is made for.</param>
		/// <remarks>
		/// <paramref name="log"/> is already formatted with the <paramref name="exception"/> info.
		/// </remarks>
		virtual void LogException(const std::string& log, const std::exception& exception) noexcept = 0;

	protected:
		virtual ~ILoggerEntryView() noexcept = default;
	};
}
