/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Factory:IWindowSystemFactory;

import :WindowParams;

export namespace PonyEngine::Window
{
	/// @brief Window factory.
	class IWindowSystemFactory
	{
	public:
		IWindowSystemFactory(const IWindowSystemFactory&) = delete;
		IWindowSystemFactory(IWindowSystemFactory&&) = delete;

		/// @brief Gets the next window params.
		/// @return Next window params.
		[[nodiscard("Pure function")]]
		virtual WindowParams NextWindowParams() const noexcept = 0;
		/// @brief Sets the next window params.
		/// @param params Next window params to set.
		virtual void NextWindowParams(const WindowParams& params) noexcept = 0;

		IWindowSystemFactory& operator =(const IWindowSystemFactory&) = delete;
		IWindowSystemFactory& operator =(IWindowSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IWindowSystemFactory() noexcept = default;

		~IWindowSystemFactory() noexcept = default;
	};
}
