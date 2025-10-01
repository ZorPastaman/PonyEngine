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

export namespace PonyEngine::Log::WinCore
{
	/// @brief WinCore platform console sub-logger factory.
	class PlatformConsoleSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		/// @brief Creates a platform console sub-logger factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit PlatformConsoleSubLoggerFactory(Application::IModuleContext& context) noexcept;
		PlatformConsoleSubLoggerFactory(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory(PlatformConsoleSubLoggerFactory&&) = delete;

		~PlatformConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual SubLoggerData CreateSubLogger(ILoggerContext& logger) override;

		PlatformConsoleSubLoggerFactory& operator =(const PlatformConsoleSubLoggerFactory&) = delete;
		PlatformConsoleSubLoggerFactory& operator =(PlatformConsoleSubLoggerFactory&&) = delete;

	private:
		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log::WinCore
{
	PlatformConsoleSubLoggerFactory::PlatformConsoleSubLoggerFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	SubLoggerData PlatformConsoleSubLoggerFactory::CreateSubLogger(ILoggerContext&)
	{
		PONY_LOG(context->Logger(), LogType::Info, "Constructing '{}'...", typeid(PlatformConsoleSubLogger).name());
		const auto platformConsoleSubLogger = std::make_shared<PlatformConsoleSubLogger>();
		SubLoggerData data;
		data.subLogger = platformConsoleSubLogger;
		PONY_LOG(context->Logger(), LogType::Info, "Constructing '{}' done.", typeid(PlatformConsoleSubLogger).name());

		return data;
	}
}
