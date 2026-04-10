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

export module PonyEngine.RawInput.XInput.Impl.Windows:XInputProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :XInputProvider;

export namespace PonyEngine::RawInput::XInput::Windows
{
	/// @brief XInput gamepad provider module.
	class XInputProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		XInputProviderModule() noexcept = default;
		XInputProviderModule(const XInputProviderModule&) = delete;
		XInputProviderModule(XInputProviderModule&&) = delete;

		~XInputProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		XInputProviderModule& operator =(const XInputProviderModule&) = delete;
		XInputProviderModule& operator =(XInputProviderModule&&) = delete;

	private:
		InputProviderHandle controllerProviderHandle; ///< Controller provider handle.
	};
}

namespace PonyEngine::RawInput::XInput::Windows
{
	void XInputProviderModule::StartUp(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
#ifndef NDEBUG
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found.");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(XInputProvider).name());
		controllerProviderHandle = inputModuleContext->AddProvider([&](IRawInputContext& input)
		{
			return std::make_shared<XInputProvider>(input);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(XInputProvider).name());
	}

	void XInputProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
#ifndef NDEBUG
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found.");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(XInputProvider).name());
		inputModuleContext->RemoveProvider(controllerProviderHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(XInputProvider).name());
	}
}
