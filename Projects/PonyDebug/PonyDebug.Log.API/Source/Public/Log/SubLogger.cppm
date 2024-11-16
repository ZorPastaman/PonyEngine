/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:SubLogger;

import :ISubLogger;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger.
	class SubLogger : public ISubLogger
	{
	public:
		SubLogger(const SubLogger&) = delete;
		SubLogger(SubLogger&&) = delete;

		virtual ~SubLogger() noexcept = default;

		SubLogger& operator =(const SubLogger&) = delete;
		SubLogger& operator =(SubLogger&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		SubLogger() noexcept = default;
	};
}
