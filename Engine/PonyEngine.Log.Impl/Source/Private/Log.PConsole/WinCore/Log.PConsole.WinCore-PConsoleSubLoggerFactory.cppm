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

import PonyEngine.Core;
import PonyEngine.Log.Extension;

import :PlatformConsoleSubLogger;

export namespace PonyEngine::Log::WinCore
{
	/// @brief WinCore platform console sub-logger factory.
	class PlatformConsoleSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		/// @brief Creates a platform console sub-logger factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLoggerFactory(Core::IModuleContext& context) noexcept;
		PlatformConsoleSubLoggerFactory(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory(PlatformConsoleSubLoggerFactory&&) = delete;

		~PlatformConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ISubLogger> CreateSubLogger(ILoggerContext& logger) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept override;

		PlatformConsoleSubLoggerFactory& operator =(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory& operator =(PlatformConsoleSubLoggerFactory&&) = delete;

	private:
		Core::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log::WinCore
{
	PlatformConsoleSubLoggerFactory::PlatformConsoleSubLoggerFactory(Core::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	std::shared_ptr<ISubLogger> PlatformConsoleSubLoggerFactory::CreateSubLogger(ILoggerContext&)
	{
		PONY_LOG(context->Logger(), LogType::Debug, "Constructing WinCore console sub-logger.");
		return std::make_shared<PlatformConsoleSubLogger>();
	}

	std::int32_t PlatformConsoleSubLoggerFactory::Order() const noexcept
	{
		return PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER;
	}
}
