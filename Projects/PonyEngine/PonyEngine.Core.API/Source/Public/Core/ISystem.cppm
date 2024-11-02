/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystem;

import <string_view>;

export namespace PonyEngine::Core
{
	/// @brief System.
	class ISystem
	{
	public:
		ISystem(const ISystem&) = delete;
		ISystem(ISystem&&) = delete;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;

		ISystem& operator =(const ISystem&) = delete;
		ISystem& operator =(ISystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ISystem() noexcept = default;

		~ISystem() noexcept = default;
	};
}
