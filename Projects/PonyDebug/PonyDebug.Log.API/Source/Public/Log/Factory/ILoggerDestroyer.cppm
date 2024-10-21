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

		/// @brief Checks the logger compatibility.
		/// @param logger Logger.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(ILogger* logger) const noexcept = 0;

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
