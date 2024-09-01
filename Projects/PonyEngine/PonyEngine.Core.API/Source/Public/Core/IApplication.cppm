/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IApplication;

import PonyEngine.Log;

export namespace PonyEngine::Core
{
	/// @brief Main application.
	class IApplication // TODO: Move to Common
	{
	public:
		IApplication(const IApplication&) = delete;
		IApplication(IApplication&&) = delete;

		/// @brief Gets the application logger.
		/// @return Application logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the application name.
		/// @return Application name.
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept = 0;

		IApplication& operator =(const IApplication&) = delete;
		IApplication& operator =(IApplication&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IApplication() noexcept = default;

		~IApplication() noexcept = default;
	};
}
