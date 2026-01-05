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

import :IInputProvider;
import :InputProviderHandle;
import :IRawInputContext;

export namespace PonyEngine::Input
{
	/// @brief Raw input module context.
	class IRawInputModuleContext
	{
		PONY_INTERFACE_BODY(IRawInputModuleContext)

		/// @brief Adds an input provider.
		/// @param factory Input provider factory.
		/// @return Input provider handle.
		[[nodiscard("Must be used to remove")]]
		virtual InputProviderHandle AddProvider(const std::function<std::shared_ptr<IInputProvider>(IRawInputContext&)>& factory) = 0;
		/// @brief Removes an input provider.
		/// @param providerHandle Input provider handle.
		virtual void RemoveProvider(InputProviderHandle providerHandle) = 0;
	};
}
