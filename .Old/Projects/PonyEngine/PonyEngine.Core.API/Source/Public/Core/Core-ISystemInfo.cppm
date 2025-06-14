/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Core:ISystemInfo;

import <cstddef>;
import <typeinfo>;

export namespace PonyEngine::Core
{
	/// @brief System info.
	class ISystemInfo
	{
		INTERFACE_BODY(ISystemInfo)

		/// @brief Gets a system type.
		/// @return System type.
		[[nodiscard("Pure function")]]
		virtual const std::type_info& SystemType() const noexcept = 0;

		/// @brief Is the system tickable?
		/// @return @a True if it's tickable; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept = 0;
		/// @brief How many public interfaces the system has.
		/// @return Public interface count.
		[[nodiscard("Pure function")]]
		virtual std::size_t InterfaceCount() const noexcept = 0;
	};
}
