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

export module PonyEngine.RawInput.Mouse.Impl.Windows:MouseProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :MouseProvider;

export namespace PonyEngine::Input::Windows
{
	/// @brief Mouse provider module.
	class MouseProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		MouseProviderModule() noexcept = default;
		MouseProviderModule(const MouseProviderModule&) = delete;
		MouseProviderModule(MouseProviderModule&&) = delete;

		~MouseProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		MouseProviderModule& operator =(const MouseProviderModule&) = delete;
		MouseProviderModule& operator =(MouseProviderModule&&) = delete;

	private:
		InputProviderHandle mouseProviderHandle; ///< Mouse provider handle.
	};
}

namespace PonyEngine::Input::Windows
{
	void MouseProviderModule::StartUp(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(MouseProvider).name());
		mouseProviderHandle = inputModuleContext->AddProvider([&](IRawInputContext& input)
			{
				return std::make_shared<MouseProvider>(input);
			});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(MouseProvider).name());
	}

	void MouseProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(MouseProvider).name());
		inputModuleContext->RemoveProvider(mouseProviderHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(MouseProvider).name());
	}
}
