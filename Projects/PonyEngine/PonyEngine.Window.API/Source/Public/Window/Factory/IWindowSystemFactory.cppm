/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factory:IWindowSystemFactory;

import PonyEngine.Core.Factory;

import :WindowParams;

export namespace PonyEngine::Window
{
	class IWindowSystemFactory : public Core::ISystemFactory
	{
	public:
		IWindowSystemFactory(const IWindowSystemFactory&) = delete;
		IWindowSystemFactory(IWindowSystemFactory&&) = delete;

		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual WindowParams& SystemParams() noexcept = 0;
		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual const WindowParams& SystemParams() const noexcept = 0;

		IWindowSystemFactory& operator =(const IWindowSystemFactory&) = delete;
		IWindowSystemFactory& operator =(IWindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowSystemFactory() noexcept = default;

		~IWindowSystemFactory() noexcept = default;
	};
}
