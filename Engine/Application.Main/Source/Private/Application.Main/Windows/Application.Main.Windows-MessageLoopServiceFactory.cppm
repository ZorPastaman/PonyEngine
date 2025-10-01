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

export module PonyEngine.Application.Main.Windows:MessageLoopServiceFactory;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;

import :MessageLoopService;

export namespace PonyEngine::Application::Windows
{
	/// @brief Message loop service factory.
	class MessageLoopServiceFactory final : public IServiceFactory
	{
	public:
		/// @brief Creates a message loop service factory.
		/// @param context Module context.
		[[nodiscard("Pure constructor")]]
		explicit MessageLoopServiceFactory(IModuleContext& context) noexcept;
		MessageLoopServiceFactory(const MessageLoopServiceFactory&) = delete;
		MessageLoopServiceFactory(MessageLoopServiceFactory&&) = delete;

		~MessageLoopServiceFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual ServiceData Create(IApplicationContext& application) override;

		MessageLoopServiceFactory& operator =(const MessageLoopServiceFactory&) = delete;
		MessageLoopServiceFactory& operator =(MessageLoopServiceFactory&&) = delete;

	private:
		IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Application::Windows
{
	MessageLoopServiceFactory::MessageLoopServiceFactory(IModuleContext& context) noexcept :
		context{&context}
	{
	}

	ServiceData MessageLoopServiceFactory::Create(IApplicationContext& application)
	{
		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(MessageLoopService).name());
		const auto loop = std::make_shared<MessageLoopService>(context->Application());
		ServiceData data;
		data.service = std::static_pointer_cast<ITickableService>(loop);
		data.publicInterfaces.AddInterface<IMessageLoopService>(loop->PublicMessageLoopService());
		data.tickOrder = PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER;
		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(MessageLoopService).name());

		return data;
	}
}
