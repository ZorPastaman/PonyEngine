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

export module PonyEngine.MessagePump.Impl:Windows.PumpServiceModule;

import std;

import :Windows.PumpService;

export namespace PonyEngine::MessagePump::Windows
{
	/// @brief Windows pump service module.
	class PumpServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constuctor")]]
		PumpServiceModule() noexcept = default;
		PumpServiceModule(const PumpServiceModule&) = delete;
		PumpServiceModule(PumpServiceModule&&) = delete;

		~PumpServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		PumpServiceModule& operator =(const PumpServiceModule&) = delete;
		PumpServiceModule& operator =(PumpServiceModule&&) = delete;

	private:
		Application::ServiceHandle pumpServiceHandle; ///< Pump service handle.
	};
}

namespace PonyEngine::MessagePump::Windows
{
	void PumpServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(PumpService).name());
		pumpServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
		{
			const auto pump = std::make_shared<PumpService>(application);

			Application::ServiceData data;
			data.SetService(pump, PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER);
			data.AddInterface(&pump->PublicPumpService());

			return data;
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(PumpService).name());
	}

	void PumpServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(PumpService).name());
		context.ServiceModuleContext().RemoveService(pumpServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(PumpService).name());
	}
}
