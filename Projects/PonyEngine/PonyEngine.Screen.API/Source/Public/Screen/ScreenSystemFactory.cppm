/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen:ScreenSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Screen
{
	/// @brief Screen system factory.
	class ScreenSystemFactory : public Core::ISystemFactory
	{
	public:
		ScreenSystemFactory(const ScreenSystemFactory&) = delete;
		ScreenSystemFactory(ScreenSystemFactory&&) = delete;

		virtual ~ScreenSystemFactory() noexcept = default;

		ScreenSystemFactory& operator =(const ScreenSystemFactory&) = delete;
		ScreenSystemFactory& operator =(ScreenSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ScreenSystemFactory() noexcept = default;
	};
}