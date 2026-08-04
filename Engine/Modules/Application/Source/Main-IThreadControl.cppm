/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application:IThreadControl;

import std;

export namespace PonyEngine::Application
{
	/// @brief Thread control.
	class IThreadControl
	{
		PONY_INTERFACE_BODY(IThreadControl)

		/// @brief Gets a current role.
		/// @return Role.
		[[nodiscard("Pure function")]]
		virtual std::string_view Role() const noexcept = 0;
		/// @brief Sets the role.
		/// @param role Role to set. Empty role means a default role.
		/// @note In case of an exception, a default role will be applied.
		virtual void Role(std::string_view role) = 0;
	};
}
