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

export namespace PonyEngine::RawInput
{
	/// @brief Raw input module context.
	class IRawInputModuleContext
	{
		PONY_INTERFACE_BODY(IRawInputModuleContext)

		/// @brief Adds an input provider.
		/// @param factory Input provider factory.
		/// @return Input provider handle. Must be used to remove a provider before a destruction of the raw input service.
		/// @note The function must be called on a main thread.
		[[nodiscard("Must be used to remove")]]
		virtual InputProviderHandle AddProvider(const std::function<std::shared_ptr<IInputProvider>(IRawInputContext&)>& factory) = 0;
		/// @brief Removes an input provider.
		/// @param providerHandle Input provider handle.
		/// @note The function must be called on a main thread.
		virtual void RemoveProvider(InputProviderHandle providerHandle) = 0;
	};
}
