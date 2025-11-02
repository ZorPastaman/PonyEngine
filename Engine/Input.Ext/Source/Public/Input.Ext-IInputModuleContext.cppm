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

export module PonyEngine.Input.Ext:IInputModuleContext;

import std;

import :IInputContext;
import :IInputProvider;
import :InputProviderHandle;

export namespace PonyEngine::Input
{
	/// @brief Input module context.
	class IInputModuleContext
	{
		INTERFACE_BODY(IInputModuleContext)

		/// @brief Adds an input provider.
		/// @param factory Input provider factory.
		/// @return Input provider handle.
		[[nodiscard("Must be used to remove")]]
		virtual InputProviderHandle AddProvider(const std::function<std::shared_ptr<IInputProvider>(IInputContext&)>& factory) = 0;
		/// @brief Removes an input provider.
		/// @param handle 
		virtual void RemoveProvider(InputProviderHandle handle) = 0;
	};
}
