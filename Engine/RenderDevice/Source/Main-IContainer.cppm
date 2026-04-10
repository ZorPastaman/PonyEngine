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

export module PonyEngine.RenderDevice:IContainer;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Container of views.
	class IContainer
	{
		PONY_INTERFACE_BODY(IContainer)

		/// @brief Gets the container size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept = 0;

		/// @brief Gets the container name.
		/// @return Container name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the container name.
		/// @param name Container name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
