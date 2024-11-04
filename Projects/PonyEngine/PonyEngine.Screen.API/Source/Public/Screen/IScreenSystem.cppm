/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen:IScreenSystem;

import PonyMath.Utility;

import PonyEngine.Core;

export namespace PonyEngine::Screen
{
	/// @brief Screen system.
	class IScreenSystem : public Core::ISystem
	{
	public:
		IScreenSystem(const IScreenSystem&) = delete;
		IScreenSystem(IScreenSystem&&) = delete;

		/// @brief Gets a display resolution.
		/// @return Display resolution.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<unsigned int> DisplayResolution() const noexcept = 0;

		IScreenSystem& operator =(const IScreenSystem&) = delete;
		IScreenSystem& operator =(IScreenSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IScreenSystem() noexcept = default;

		~IScreenSystem() noexcept = default;
	};
}
