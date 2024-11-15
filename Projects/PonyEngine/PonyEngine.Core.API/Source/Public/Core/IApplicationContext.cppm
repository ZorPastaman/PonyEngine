/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IApplicationContext;

import <string_view>;

import PonyDebug.Log;

export namespace PonyEngine::Core
{
	/// @brief Application context.
	class IApplicationContext
	{
	public:
		IApplicationContext(const IApplicationContext&) = delete;
		IApplicationContext(IApplicationContext&&) = delete;

		/// @brief Gets the application logger.
		/// @return Application logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the application name.
		/// @return Application name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;

		IApplicationContext& operator =(const IApplicationContext&) = delete;
		IApplicationContext& operator =(IApplicationContext&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IApplicationContext() noexcept = default;

		~IApplicationContext() noexcept = default;
	};
}
