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

import :WindowSystemParams;

export namespace PonyEngine::Window
{
	/// @brief Window system factory.
	class IWindowSystemFactory : public Core::ISystemFactory
	{
	public:
		IWindowSystemFactory(const IWindowSystemFactory&) = delete;
		IWindowSystemFactory(IWindowSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual WindowSystemParams& SystemParams() noexcept override = 0;
		[[nodiscard("Pure function")]]
		virtual const WindowSystemParams& SystemParams() const noexcept override = 0;

		IWindowSystemFactory& operator =(const IWindowSystemFactory&) = delete;
		IWindowSystemFactory& operator =(IWindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowSystemFactory() noexcept = default;

		~IWindowSystemFactory() noexcept = default;
	};
}
