/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:SystemInfo;

import PonyEngine.Core;

import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	/// @brief System info.
	struct SystemInfo final
	{
		ObjectInterfaces interfaces; ///< System public interfaces.
		ISystem* system; ///< System.

		[[nodiscard("Pure constructor")]]
		SystemInfo() noexcept = default;
		[[nodiscard("Pure constructor")]]
		SystemInfo(const SystemInfo& other) = default;
		[[nodiscard("Pure constructor")]]
		SystemInfo(SystemInfo&& other) noexcept = default;

		~SystemInfo() noexcept = default;

		SystemInfo& operator =(const SystemInfo& other) = default;
		SystemInfo& operator =(SystemInfo&& other) noexcept = default;

		bool operator ==(const SystemInfo& other) const noexcept = default;
	};
}
