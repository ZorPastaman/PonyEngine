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

import :WindowParams;

export namespace PonyEngine::Window
{
	/// @brief Window factory.
	class IWindowFactory : public Core::ISystemFactory
	{
	public:
		/// @brief Gets a next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual WindowParams& NextWindowParams() noexcept = 0;
		/// @brief Gets a next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual const WindowParams& NextWindowParams() const noexcept = 0;

	protected:
		~IWindowFactory() noexcept = default;
	};
}
