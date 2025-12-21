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

export module PonyEngine.RawInput.Impl:RawInputServiceModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput;

import :RawInputService;

export namespace PonyEngine::Input
{
	/// @brief Raw input service module.
	class RawInputServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		RawInputServiceModule() noexcept = default;
		RawInputServiceModule(const RawInputServiceModule&) = delete;
		RawInputServiceModule(RawInputServiceModule&&) = delete;

		~RawInputServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		RawInputServiceModule& operator =(const RawInputServiceModule&) = delete;
		RawInputServiceModule& operator =(RawInputServiceModule&&) = delete;

	private:
		Application::ModuleDataHandle inputServiceModuleHandle; ///< Input service module handle.
		Application::ServiceHandle inputServiceHandle; ///< Input service handle.
	};
}

namespace PonyEngine::Input
{
	void RawInputServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(RawInputService).name());
		try
		{
			inputServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
			{
				const auto input = std::make_shared<RawInputService>(application);
				inputServiceModuleHandle = context.AddData(std::shared_ptr<IRawInputModuleContext>(input, input.get()));
				
				return input;
			});
		}
		catch (...)
		{
			if (inputServiceModuleHandle.IsValid())
			{
				context.RemoveData(inputServiceModuleHandle);
			}
			throw;
		}
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(RawInputService).name());
	}

	void RawInputServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(RawInputService).name());
		context.ServiceModuleContext().RemoveService(inputServiceHandle);
		context.RemoveData(inputServiceModuleHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(RawInputService).name());
	}
}
