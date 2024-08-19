/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Factory:ISubLoggerDestroyer;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger destroyer.
	class ISubLoggerDestroyer
	{
	public:
		ISubLoggerDestroyer(const ISubLoggerDestroyer&) = delete;
		ISubLoggerDestroyer(ISubLoggerDestroyer&&) = delete;

		/// @brief Destroys the @p subLogger.
		/// @param subLogger Sub-logger to destroy.
		virtual void Destroy(ISubLogger* subLogger) noexcept = 0;

		ISubLoggerDestroyer& operator =(const ISubLoggerDestroyer&) = delete;
		ISubLoggerDestroyer& operator =(ISubLoggerDestroyer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISubLoggerDestroyer() noexcept = default;

		~ISubLoggerDestroyer() noexcept = default;
	};
}
