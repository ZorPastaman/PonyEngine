/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factory:IWindowFactory;

import <string>;

import PonyEngine.Core.Factory;

import :WindowParams;

export namespace PonyEngine::Window
{
	/// @brief Window factory.
	class IWindowFactory : public Core::ISystemFactory
	{
	public:
		IWindowFactory(const IWindowFactory&) = delete;
		IWindowFactory(IWindowFactory&&) = delete;

		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual WindowParams& NextWindowParams() noexcept = 0;
		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual const WindowParams& NextWindowParams() const noexcept = 0;

		IWindowFactory& operator =(const IWindowFactory&) = delete;
		IWindowFactory& operator =(IWindowFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowFactory() noexcept = default;

		~IWindowFactory() noexcept = default;
	};
}
