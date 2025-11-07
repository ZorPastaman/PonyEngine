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

export module PonyEngine.Input.Impl:InputServiceModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Input;
import PonyEngine.Log;

import :InputService;

export namespace PonyEngine::Input
{
	/// @brief Input service module.
	class InputServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputServiceModule() noexcept = default;
		InputServiceModule(const InputServiceModule&) = delete;
		InputServiceModule(InputServiceModule&&) = delete;

		~InputServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		InputServiceModule& operator =(const InputServiceModule&) = delete;
		InputServiceModule& operator =(InputServiceModule&&) = delete;

	private:
		Application::ModuleDataHandle inputServiceModuleHandle; ///< Input service module handle.
		Application::ServiceHandle inputServiceHandle; ///< Input service handle.
	};
}

namespace PonyEngine::Input
{
	void InputServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(InputService).name());
		try
		{
			inputServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
			{
				const auto input = std::make_shared<InputService>(application);
				inputServiceModuleHandle = context.AddData(std::shared_ptr<IInputModuleContext>(input, &input->PublicInputContext()));
				Application::ServiceData data;
				data.SetService(input, PONY_ENGINE_INPUT_TICK_ORDER);
				data.AddInterface(&input->PublicInputService());

				return data;
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
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(InputService).name());
	}

	void InputServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(InputService).name());
		context.ServiceModuleContext().RemoveService(inputServiceHandle);
		context.RemoveData(inputServiceModuleHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(InputService).name());
	}
}
