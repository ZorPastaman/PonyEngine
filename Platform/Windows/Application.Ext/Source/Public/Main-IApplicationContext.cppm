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

export module PonyEngine.Application.Ext.Windows:IApplicationContext;

import PonyEngine.Application.Ext;

export namespace PonyEngine::Application::Windows
{
	/// @brief Windows application context.
	/// @note All the functions here are thread-safe.
	class IApplicationContext : public Application::IApplicationContext
	{
		PONY_INTERFACE_BODY(IApplicationContext)

		/// @brief Gets the instance handle of the application.
		/// @return Instance handle of the application.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept = 0;
		/// @brief Gets the previous instance handle of the application.
		/// @return Previous instance handle of the application.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE PrevInstance() const noexcept = 0;
		/// @brief Gets the show command for the application.
		/// @return Show command.
		[[nodiscard("Pure function")]]
		virtual int ShowCommand() const noexcept = 0;

		/// @brief Gets the application icon.
		/// @return Application icon.
		[[nodiscard("Pure function")]]
		virtual HICON AppIcon() const noexcept = 0;
		/// @brief Gets the application cursor.
		/// @return Application cursor.
		[[nodiscard("Pure function")]]
		virtual HCURSOR AppCursor() const noexcept = 0;
	};
}
