/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:WindowSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Window
{
	/// @brief Window system factory.
	class WindowSystemFactory : public Core::ISystemFactory
	{
	public:
		WindowSystemFactory(const WindowSystemFactory&) = delete;
		WindowSystemFactory(WindowSystemFactory&&) = delete;

		virtual ~WindowSystemFactory() noexcept = default;

		WindowSystemFactory& operator =(const WindowSystemFactory&) = delete;
		WindowSystemFactory& operator =(WindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		WindowSystemFactory() noexcept = default;
	};
}
