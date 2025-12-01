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

export module PonyEngine.RawInput.Ext:IRawInputModuleContext;

import std;

import :IRawInputContext;
import :IRawInputProvider;
import :RawInputProviderHandle;

export namespace PonyEngine::Input
{
	/// @brief Raw input module context.
	class IRawInputModuleContext
	{
		INTERFACE_BODY(IRawInputModuleContext)

		/// @brief Adds an input provider.
		/// @param factory Input provider factory.
		/// @return Input provider handle.
		[[nodiscard("Must be used to remove")]]
		virtual RawInputProviderHandle AddProvider(const std::function<std::shared_ptr<IRawInputProvider>(IRawInputContext&)>& factory) = 0;
		/// @brief Removes an input provider.
		/// @param handle 
		virtual void RemoveProvider(RawInputProviderHandle handle) = 0;
	};
}
