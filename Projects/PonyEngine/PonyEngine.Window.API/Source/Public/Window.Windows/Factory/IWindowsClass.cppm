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

export module PonyEngine.Window.Windows.Factory:IWindowsClass;

export namespace PonyEngine::Window
{
	/// @brief Windows class.
	class IWindowsClass
	{
	public:
		IWindowsClass(const IWindowsClass&) = delete;
		IWindowsClass(IWindowsClass&&) = delete;

		/// @brief Gets a module instance.
		/// @return Module instance.
		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept = 0;
		/// @brief Gets a registered class.
		/// @return Registered class.
		[[nodiscard("Pure function")]]
		virtual ATOM Class() const noexcept = 0;

		IWindowsClass& operator =(const IWindowsClass&) = delete;
		IWindowsClass& operator =(IWindowsClass&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowsClass() noexcept = default;

		~IWindowsClass() noexcept = default;
	};
}
