/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Windows:IMainData;

export namespace PonyEngine::Application::Windows
{
	/// @brief Provides data from @p WinMain().
	class IMainData
	{
		PONY_INTERFACE_BODY(IMainData)

		/// @brief Gets the instance handle of the application.
		/// @return Instance handle of the application.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept = 0;
		/// @brief Gets the previous instance handle of the application.
		/// @return Previous instance handle of the application.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE PrevInstance() const noexcept = 0;
		/// @brief Gets the command line.
		/// @return Command line.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual PSTR CommandLine() const noexcept = 0;
		/// @brief Gets the show command for the application.
		/// @return Show command.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual int ShowCommand() const noexcept = 0;
	};
}
