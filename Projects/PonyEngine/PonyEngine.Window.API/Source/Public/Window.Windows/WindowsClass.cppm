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

export module PonyEngine.Window.Windows:WindowsClass;

export namespace PonyEngine::Window
{
	/// @brief Windows class.
	class WindowsClass
	{
	public:
		WindowsClass(const WindowsClass&) = delete;
		WindowsClass(WindowsClass&&) = delete;

		virtual ~WindowsClass() noexcept = default;

		/// @brief Gets a module instance.
		/// @return Module instance.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept = 0;
		/// @brief Gets a registered class.
		/// @return Registered class.
		[[nodiscard("Pure function")]]
		virtual ATOM Class() const noexcept = 0;

		WindowsClass& operator =(const WindowsClass&) = delete;
		WindowsClass& operator =(WindowsClass&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		WindowsClass() noexcept = default;
	};
}
