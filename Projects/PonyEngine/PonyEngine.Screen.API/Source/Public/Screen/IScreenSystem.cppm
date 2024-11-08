/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen:IScreenSystem;

import <string_view>;

import PonyMath.Utility;

export namespace PonyEngine::Screen
{
	/// @brief Screen system.
	class IScreenSystem
	{
	public:
		IScreenSystem(const IScreenSystem&) = delete;
		IScreenSystem(IScreenSystem&&) = delete;

		/// @brief Gets a display resolution.
		/// @return Display resolution.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<unsigned int> DisplayResolution() const noexcept = 0;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;

		IScreenSystem& operator =(const IScreenSystem&) = delete;
		IScreenSystem& operator =(IScreenSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IScreenSystem() noexcept = default;

		~IScreenSystem() noexcept = default;
	};
}
