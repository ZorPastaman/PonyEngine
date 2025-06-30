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

import PonyEngine.Core;
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
		explicit ConsoleSubLoggerFactory(Core::IModuleContext& context) noexcept;
		ConsoleSubLoggerFactory(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory(ConsoleSubLoggerFactory&&) = delete;

		~ConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ISubLogger> CreateSubLogger(ILoggerContext& logger) override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept override;

		ConsoleSubLoggerFactory& operator =(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory& operator =(ConsoleSubLoggerFactory&&) = delete;

	private:
		Core::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	ConsoleSubLoggerFactory::ConsoleSubLoggerFactory(Core::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	std::shared_ptr<ISubLogger> ConsoleSubLoggerFactory::CreateSubLogger(ILoggerContext&)
	{
		PONY_LOG(context->Logger(), LogType::Debug, "Constructing console sub-logger.");
		return std::make_shared<ConsoleSubLogger>();
	}

	std::int32_t ConsoleSubLoggerFactory::Order() const noexcept
	{
		return PONY_ENGINE_LOG_CONSOLE_ORDER;
	}
}
