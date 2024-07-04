/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factories:IWindowFactory;

import <string>;

import PonyEngine.Core.Factories;

export namespace PonyEngine::Window
{
	/// @brief Window factory.
	class IWindowFactory : public Core::ISystemFactory
	{
	public:
		/// @brief Gets a title of the next created window.
		/// @return Window title.
		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept = 0;
		/// @brief Sets a title of the next created window.
		/// @param title Window title.
		virtual void SetTitle(const wchar_t* title) noexcept = 0;

	protected:
		~IWindowFactory() noexcept = default;
	};
}
