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

export namespace PonyEngine::Log
{
	/// @brief Console sub-logger factory.
	class ConsoleSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		/// @brief Creates a console sub-logger factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit ConsoleSubLoggerFactory(Application::IModuleContext& context) noexcept;
		ConsoleSubLoggerFactory(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory(ConsoleSubLoggerFactory&&) = delete;

		~ConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual SubLoggerData CreateSubLogger(ILoggerContext& logger) override;

		ConsoleSubLoggerFactory& operator =(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory& operator =(ConsoleSubLoggerFactory&&) = delete;

	private:
		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	ConsoleSubLoggerFactory::ConsoleSubLoggerFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	SubLoggerData ConsoleSubLoggerFactory::CreateSubLogger(ILoggerContext&)
	{
		PONY_LOG(context->Logger(), LogType::Info, "Constructing '{}'...", typeid(ConsoleSubLogger).name());
		const auto consoleSubLogger = std::make_shared<ConsoleSubLogger>();
		SubLoggerData data;
		data.subLogger = consoleSubLogger;
		PONY_LOG(context->Logger(), LogType::Info, "Constructing '{}' done.", typeid(ConsoleSubLogger).name());

		return data;
	}
}
