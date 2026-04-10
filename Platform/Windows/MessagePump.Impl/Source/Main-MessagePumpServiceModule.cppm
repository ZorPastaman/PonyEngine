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

export module PonyEngine.MessagePump.Impl.Windows:MessagePumpServiceModule;

import std;

import :MessagePumpService;

export namespace PonyEngine::MessagePump::Windows
{
	/// @brief Windows message pump service module.
	class MessagePumpServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constuctor")]]
		MessagePumpServiceModule() noexcept = default;
		MessagePumpServiceModule(const MessagePumpServiceModule&) = delete;
		MessagePumpServiceModule(MessagePumpServiceModule&&) = delete;

		~MessagePumpServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		MessagePumpServiceModule& operator =(const MessagePumpServiceModule&) = delete;
		MessagePumpServiceModule& operator =(MessagePumpServiceModule&&) = delete;

	private:
		Application::ServiceHandle pumpServiceHandle; ///< Pump service handle.
	};
}

namespace PonyEngine::MessagePump::Windows
{
	void MessagePumpServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(MessagePumpService).name());
		pumpServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
		{
			return std::make_shared<MessagePumpService>(application);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(MessagePumpService).name());
	}

	void MessagePumpServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(MessagePumpService).name());
		context.ServiceModuleContext().RemoveService(pumpServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(MessagePumpService).name());
	}
}
