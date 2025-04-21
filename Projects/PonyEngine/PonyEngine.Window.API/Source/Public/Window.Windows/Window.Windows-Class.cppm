/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Window.Windows:Class;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows class.
	class Class
	{
		SIMPLE_BASE_BODY(Class)

	public:
		/// @brief Gets a module handle.
		/// @return Module handle.
		[[nodiscard("Pure function")]]
		virtual HMODULE ModuleHandle() const noexcept = 0;
		/// @brief Gets a registered class handle.
		/// @return Registered class handle.
		[[nodiscard("Pure function")]]
		virtual ATOM ClassHandle() const noexcept = 0;
	};
}
