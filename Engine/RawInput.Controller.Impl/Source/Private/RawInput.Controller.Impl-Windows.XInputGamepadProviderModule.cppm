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

export module PonyEngine.RawInput.Controller.Impl:Windows.XInputGamepadProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :Windows.XInputGamepadProvider;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad provider module.
	class XInputGamepadProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		XInputGamepadProviderModule() noexcept = default;
		XInputGamepadProviderModule(const XInputGamepadProviderModule&) = delete;
		XInputGamepadProviderModule(XInputGamepadProviderModule&&) = delete;

		~XInputGamepadProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		XInputGamepadProviderModule& operator =(const XInputGamepadProviderModule&) = delete;
		XInputGamepadProviderModule& operator =(XInputGamepadProviderModule&&) = delete;

	private:
		InputProviderHandle controllerProviderHandle; ///< Controller provider handle.
	};
}

namespace PonyEngine::Input::Windows
{
	void XInputGamepadProviderModule::StartUp(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found.");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(XInputGamepadProvider).name());
		controllerProviderHandle = inputModuleContext->AddProvider([&](IRawInputContext& input)
			{
				return std::make_shared<XInputGamepadProvider>(input);
			});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(XInputGamepadProvider).name());
	}

	void XInputGamepadProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found.");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(XInputGamepadProvider).name());
		inputModuleContext->RemoveProvider(controllerProviderHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(XInputGamepadProvider).name());
	}
}
