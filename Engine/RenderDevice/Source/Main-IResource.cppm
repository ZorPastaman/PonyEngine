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

export module PonyEngine.RenderDevice:IResource;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Resource.
	class IResource
	{
		PONY_INTERFACE_BODY(IResource)

		/// @brief Gets the resource name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the resource name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
