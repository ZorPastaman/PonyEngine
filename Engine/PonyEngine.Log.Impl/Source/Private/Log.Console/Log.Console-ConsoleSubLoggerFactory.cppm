/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.Console:ConsoleSubLoggerFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Extension;

import :ConsoleSubLogger;

export namespace PonyEngine::Log::Console
{
	/// @brief Console sub-logger factory.
	class ConsoleSubLoggerFactory final : public Extension::ISubLoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleSubLoggerFactory() noexcept = default;
		ConsoleSubLoggerFactory(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory(ConsoleSubLoggerFactory&&) = delete;

		~ConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Extension::ISubLogger> CreateSubLogger(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept override;

		ConsoleSubLoggerFactory& operator =(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory& operator =(ConsoleSubLoggerFactory&&) = delete;
	};
}

namespace PonyEngine::Log::Console
{
	std::shared_ptr<Extension::ISubLogger> ConsoleSubLoggerFactory::CreateSubLogger(const Core::IModuleContext& context)
	{
		PONY_LOG(context.Application().Logger(), LogType::Debug, "Constructing console sub-logger.");
		return std::make_shared<ConsoleSubLogger>();
	}

	std::int32_t ConsoleSubLoggerFactory::Order() const noexcept
	{
		return PONY_ENGINE_LOG_CONSOLE_ORDER;
	}
}
