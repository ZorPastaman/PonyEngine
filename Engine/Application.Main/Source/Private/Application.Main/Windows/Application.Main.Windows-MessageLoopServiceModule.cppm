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

export module PonyEngine.Application.Main.Windows:MessageLoopServiceModule;

import PonyEngine.Application.Windows;
import PonyEngine.Log;

import :MessageLoopServiceFactory;

export namespace PonyEngine::Application::Windows
{
	/// @brief Message loop service module
	class MessageLoopServiceModule final : public IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		MessageLoopServiceModule() noexcept = default;
		MessageLoopServiceModule(const MessageLoopServiceModule&) = delete;
		MessageLoopServiceModule(MessageLoopServiceModule&&) = delete;

		~MessageLoopServiceModule() noexcept = default;

		virtual void StartUp(IModuleContext& context) override;
		virtual void ShutDown(const IModuleContext& context) override;

		MessageLoopServiceModule& operator =(const MessageLoopServiceModule&) = delete;
		MessageLoopServiceModule& operator =(MessageLoopServiceModule&&) = delete;
	};
}

namespace PonyEngine::Application::Windows
{
	void MessageLoopServiceModule::StartUp(IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}'...", typeid(MessageLoopServiceFactory).name());
		const auto messageLoopFactory = std::make_shared<MessageLoopServiceFactory>(context);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' done.", typeid(MessageLoopServiceFactory).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(MessageLoopServiceFactory).name());
		context.AddService(messageLoopFactory);
	}

	void MessageLoopServiceModule::ShutDown(const IModuleContext& context)
	{
	}
}
