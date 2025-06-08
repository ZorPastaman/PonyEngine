/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <string_view>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:IModule;

import :IModuleContext;

export namespace PonyEngine::Core
{
	/// @brief Module.
	class IModule
	{
		INTERFACE_BODY(IModule)

		/// @brief Invoked on an application start up.
		/// @param context Module context.
		virtual void StartUp(IModuleContext& context) = 0;
		/// @brief Invoked on an application shut down.
		/// @param context Module context.
		virtual void ShutDown(const IModuleContext& context) = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
	};

	/// @brief Module getter.
	using ModuleGetter = IModule*(*)();
}
