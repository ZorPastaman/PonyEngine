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
#include <string_view>

#include "PonyEngine/Log/Core/LoggerModule.h"
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Log.Core:LoggerModule;

import PonyEngine.Core;

import :LoggerFactory;

export namespace PonyEngine::Log::Core
{
	/// @brief Logger module.
	class LoggerModule final : public PonyEngine::Core::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Core::IModuleContext& context) override;
		virtual void ShutDown(const PonyEngine::Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
	};
}

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
		return PONY_STRINGIFY_VALUE(PONY_LOGGER_MODULE_NAME);
	}
}
