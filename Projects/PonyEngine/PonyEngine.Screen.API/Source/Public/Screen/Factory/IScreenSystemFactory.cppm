/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Factory:IScreenSystemFactory;

import PonyEngine.Core.Factory;

import :ScreenSystemParams;

export namespace PonyEngine::Screen
{
	class IScreenSystemFactory : public Core::ISystemFactory
	{
	public:
		IScreenSystemFactory(const IScreenSystemFactory&) = delete;
		IScreenSystemFactory(IScreenSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual ScreenSystemParams& SystemParams() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const ScreenSystemParams& SystemParams() const noexcept = 0;

		IScreenSystemFactory& operator =(const IScreenSystemFactory&) = delete;
		IScreenSystemFactory& operator =(IScreenSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IScreenSystemFactory() noexcept = default;

		~IScreenSystemFactory() noexcept = default;
	};
}