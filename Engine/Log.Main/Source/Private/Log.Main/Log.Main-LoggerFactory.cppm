/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.Main:LoggerFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Core;
import PonyEngine.Log.Extension;

import :Logger;

export namespace PonyEngine::Log
{
	/// @brief Logger factory.
	class LoggerFactory final : public Core::ILoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit LoggerFactory(Core::IModuleContext& context) noexcept;
		LoggerFactory(const LoggerFactory&) = delete;
		LoggerFactory(LoggerFactory&&) = delete;

		~LoggerFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<Core::ILogger> Create() override;

		LoggerFactory& operator =(const LoggerFactory&) = delete;
		LoggerFactory& operator =(LoggerFactory&&) = delete;

	private:
		Core::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Log
{
	LoggerFactory::LoggerFactory(Core::IModuleContext& context) noexcept :
		context{&context}
	{
	}

	std::shared_ptr<Core::ILogger> LoggerFactory::Create()
	{
		PONY_LOG(context->Logger(), LogType::Info, "Getting sub-logger factories.");
		const std::size_t subLoggerFactoryCount = context->DataCount<ISubLoggerFactory>();
		std::vector<ISubLoggerFactory*> subLoggerFactories;
		subLoggerFactories.reserve(subLoggerFactoryCount);
		for (std::size_t i = 0z; i < subLoggerFactoryCount; ++i)
		{
			subLoggerFactories.push_back(context->GetData<ISubLoggerFactory>(i).get());
		}

		PONY_LOG(context->Logger(), LogType::Info, "Constructing logger.");
		return std::make_shared<Logger>(context->Application(), subLoggerFactories);
	}
}
