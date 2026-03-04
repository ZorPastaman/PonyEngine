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

export module PonyEngine.RenderDevice:ICommandList;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Command list.
	class ICommandList
	{
		PONY_INTERFACE_BODY(ICommandList)

		/// @brief Resets and opens the command list.
		virtual void Reset() = 0;
		/// @brief Closes the command list and make it available for execution.
		virtual void Close() = 0;
		/// @brief Checks if the command list is open.
		/// @return @a True if it's open; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsOpen() const noexcept = 0;

		/// @brief Gets the command list name.
		/// @return Command list name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the command list name.
		/// @param name Command list name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
