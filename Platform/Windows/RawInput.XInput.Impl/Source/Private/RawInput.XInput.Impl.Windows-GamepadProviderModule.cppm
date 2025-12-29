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

export module PonyEngine.RawInput.XInput.Impl.Windows:GamepadProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :GamepadProvider;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad provider module.
	class GamepadProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		GamepadProviderModule() noexcept = default;
		GamepadProviderModule(const GamepadProviderModule&) = delete;
		GamepadProviderModule(GamepadProviderModule&&) = delete;

		~GamepadProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		GamepadProviderModule& operator =(const GamepadProviderModule&) = delete;
		GamepadProviderModule& operator =(GamepadProviderModule&&) = delete;

	private:
		InputProviderHandle controllerProviderHandle; ///< Controller provider handle.
	};
}

namespace PonyEngine::Input::Windows
{
	void GamepadProviderModule::StartUp(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found.");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(GamepadProvider).name());
		controllerProviderHandle = inputModuleContext->AddProvider([&](IRawInputContext& input)
		{
			return std::make_shared<GamepadProvider>(input);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(GamepadProvider).name());
	}

	void GamepadProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found.");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(GamepadProvider).name());
		inputModuleContext->RemoveProvider(controllerProviderHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(GamepadProvider).name());
	}
}
