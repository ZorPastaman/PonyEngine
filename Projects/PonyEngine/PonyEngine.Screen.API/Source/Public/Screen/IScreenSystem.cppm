/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen:IScreenSystem;

import PonyEngine.Core;

import :Resolution;

export namespace PonyEngine::Screen
{
	class IScreenSystem : public Core::ISystem
	{
	public:
		IScreenSystem(const IScreenSystem&) = delete;
		IScreenSystem(IScreenSystem&&) = delete;

		[[nodiscard("Pure function")]]
		virtual Resolution<unsigned int> DisplayResolution() const noexcept = 0;

		IScreenSystem& operator =(const IScreenSystem&) = delete;
		IScreenSystem& operator =(IScreenSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IScreenSystem() noexcept = default;

		~IScreenSystem() noexcept = default;
	};
}
