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

export module PonyEngine.Log.PlatformConsole.WinCore:PlatformConsoleSubLoggerFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Extension;

import :PlatformConsoleSubLogger;

export namespace PonyEngine::Log::PlatformConsole::WinCore
{
	/// @brief WinCore platform console sub-logger factory.
	class PlatformConsoleSubLoggerFactory final : public Extension::ISubLoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLoggerFactory() noexcept = default;
		PlatformConsoleSubLoggerFactory(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory(PlatformConsoleSubLoggerFactory&&) = delete;

		~PlatformConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Extension::ISubLogger> CreateSubLogger(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept override;

		PlatformConsoleSubLoggerFactory& operator =(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory& operator =(PlatformConsoleSubLoggerFactory&&) = delete;
	};
}

namespace PonyEngine::Log::PlatformConsole::WinCore
{
	std::shared_ptr<Extension::ISubLogger> PlatformConsoleSubLoggerFactory::CreateSubLogger(const Core::IModuleContext& context)
	{
		PONY_LOG(context.Application().Logger(), LogType::Debug, "Constructing WinCore console sub-logger.");
		return std::make_shared<PlatformConsoleSubLogger>();
	}

	std::int32_t PlatformConsoleSubLoggerFactory::Order() const noexcept
	{
		return PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER;
	}
}
