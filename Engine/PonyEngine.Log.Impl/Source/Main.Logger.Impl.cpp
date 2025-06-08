/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <memory>

#include "PonyEngine/Log/Core/LoggerModule.h"

import PonyEngine.Core;
import PonyEngine.Log.Core;

namespace PonyEngine::Log::Core
{
	void LoggerModule::StartUp(PonyEngine::Core::IModuleContext& context)
	{
		context.AddData<PonyEngine::Core::IFactory<ILogger>>(std::make_shared<LoggerFactory>());
	}

	void LoggerModule::ShutDown(const PonyEngine::Core::IModuleContext& context)
	{
	}

	std::string_view LoggerModule::Name() const noexcept
	{
		return "PonyEngineLogger";
	}
}
