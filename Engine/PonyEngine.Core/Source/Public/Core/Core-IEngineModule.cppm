/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:IEngineModule;

import :IApplicationContext;
import :IEngine;
import :IModule;
import :IModuleContext;

export namespace PonyEngine::Core
{
	/// @brief Engine module.
	class IEngineModule : public IModule
	{
		INTERFACE_BODY(IEngineModule)

		/// @brief Creates an engine.
		/// @param moduleContext Module context.
		/// @param applicationContext Application context.
		/// @return Engine.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IEngine> CreateEngine(const IModuleContext& moduleContext, IApplicationContext& applicationContext) = 0;
	};
}
