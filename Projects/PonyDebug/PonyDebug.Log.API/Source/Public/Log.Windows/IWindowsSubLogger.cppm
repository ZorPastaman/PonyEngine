/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Windows:IWindowsSubLogger;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Windows sub-logger.
	class IWindowsSubLogger : public ISubLogger
	{
	public:
		IWindowsSubLogger(const IWindowsSubLogger&) = delete;
		IWindowsSubLogger(IWindowsSubLogger&&) = delete;

		IWindowsSubLogger& operator =(const IWindowsSubLogger&) = delete;
		IWindowsSubLogger& operator =(IWindowsSubLogger&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsSubLogger() noexcept = default;

		~IWindowsSubLogger() noexcept = default;
	};
}
