/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <span>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:IModuleContext;

import PonyEngine.Log;

import :IModule;

export namespace PonyEngine::Core
{
	/// @brief Module context. It exists at module initialization phase only.
	class IModuleContext
	{
		INTERFACE_BODY(IModuleContext)

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the registered modules.
		/// @return Modules.
		[[nodiscard("Pure function")]]
		virtual std::span<IModule*> Modules() const noexcept = 0;
	};
}
