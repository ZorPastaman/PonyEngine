/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log.Factory:ILoggerDestroyer;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Logger destroyer.
	class ILoggerDestroyer
	{
	public:
		ILoggerDestroyer(const ILoggerDestroyer&) = delete;
		ILoggerDestroyer(ILoggerDestroyer&&) = delete;

		/// @brief Destroys the @p logger.
		/// @param logger Logger to destroy.
		virtual void Destroy(ILogger* logger) noexcept = 0;

		ILoggerDestroyer& operator =(const ILoggerDestroyer&) = delete;
		ILoggerDestroyer& operator =(ILoggerDestroyer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ILoggerDestroyer() noexcept = default;

		~ILoggerDestroyer() noexcept = default;
	};
}
