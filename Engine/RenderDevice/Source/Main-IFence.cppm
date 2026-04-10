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

export module PonyEngine.RenderDevice:IFence;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Fence.
	class IFence
	{
		PONY_INTERFACE_BODY(IFence)

		/// @brief Gets a completed value.
		/// @return Completed value.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t CompletedValue() const noexcept = 0;
		/// @brief Signals the value.
		/// @details It updates a completed value if the new one is greater than a current completed value.
		/// @param value New value.
		virtual void Signal(std::uint64_t value) = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
