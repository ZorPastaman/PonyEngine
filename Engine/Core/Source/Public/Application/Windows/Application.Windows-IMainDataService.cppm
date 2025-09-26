/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Application.Windows:IMainDataService;

export namespace PonyEngine::Application::Windows
{
	/// @brief Main data service. It provides access to WinMain parameters.
	class IMainDataService
	{
		INTERFACE_BODY(IMainDataService)

		/// @brief Gets the instance handle of the application.
		/// @return Instance handle of the application.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept = 0;
		/// @brief Gets the previous instance handle of the application.
		/// @return Previous instance handle of the application.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE PrevInstance() const noexcept = 0;
		/// @brief Gets the command line string for the application, excluding the program name.
		/// @return Command line string for the application.
		[[nodiscard("Pure function")]]
		virtual const char* CommandLine() const noexcept = 0;
		/// @brief Gets the show command for the application.
		/// @return Show command.
		[[nodiscard("Pure function")]]
		virtual int ShowCommand() const noexcept = 0;
	};
}
