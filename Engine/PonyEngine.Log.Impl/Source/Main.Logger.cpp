/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <memory>
#include <stdexcept>
#include <string_view>

#include "PonyEngine/Core/Module.h"

import PonyEngine.Core;

class LoggerModuleApp final : public PonyEngine::Core::ILoggerModule
{
public:
	[[nodiscard("Pure function")]]
	virtual std::shared_ptr<PonyEngine::Log::ILogger> CreateLogger(
		const PonyEngine::Core::IModuleContext& moduleContext, PonyEngine::Core::IApplicationContext& applicationContext) override;

	[[nodiscard("Pure function")]]
	virtual std::string_view Name() const noexcept override;
};
PONY_MODULE_LOG(LoggerModuleApp, PonyEngineLogger);

std::shared_ptr<PonyEngine::Log::ILogger> LoggerModuleApp::CreateLogger(
	const PonyEngine::Core::IModuleContext& moduleContext, PonyEngine::Core::IApplicationContext& applicationContext)
{
	throw std::runtime_error("Not implemented yet!");
}

std::string_view LoggerModuleApp::Name() const noexcept
{
	return "PonyEngineLogger";
}
