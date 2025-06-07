/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <memory>
#include <string_view>

#include "PonyEngine/Core/Module.h"
#include "PonyEngine/Log/Log.h"

import PonyEngine.Core;
import PonyEngine.Log;

class LoggerModule final : public PonyEngine::Core::IModule
{
public:
	virtual void StartUp(PonyEngine::Core::IModuleContext& context) override;
	virtual void ShutDown(const PonyEngine::Core::IModuleContext& context) override;

	[[nodiscard("Pure function")]]
	virtual std::string_view Name() const noexcept override;
};
PONY_MODULE_LOG(LoggerModule, PonyEngineLogger);


void LoggerModule::StartUp(PonyEngine::Core::IModuleContext& context)
{
	PONY_LOG(context.Application().Logger(), PonyEngine::Log::LogType::Info, "Logger startup.");
}

void LoggerModule::ShutDown(const PonyEngine::Core::IModuleContext& context)
{
	PONY_LOG(context.Application().Logger(), PonyEngine::Log::LogType::Info, "Logger shutdown.");
}

std::string_view LoggerModule::Name() const noexcept
{
	return "PonyEngineLogger";
}
