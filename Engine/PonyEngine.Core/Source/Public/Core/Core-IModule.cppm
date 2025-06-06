/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <string_view>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:IModule;

export namespace PonyEngine::Core
{
	/// @brief Module.
	class IModule
	{
		INTERFACE_BODY(IModule)

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
	};
}
