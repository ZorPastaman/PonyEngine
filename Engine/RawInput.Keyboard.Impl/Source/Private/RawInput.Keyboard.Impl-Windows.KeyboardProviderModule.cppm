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

export module PonyEngine.RawInput.Keyboard.Impl:Windows.KeyboardProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :Windows.KeyboardProvider;

export namespace PonyEngine::Input::Windows
{
	/// @brief Keyboard provider module.
	class KeyboardProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		KeyboardProviderModule() noexcept = default;
		KeyboardProviderModule(const KeyboardProviderModule&) = delete;
		KeyboardProviderModule(KeyboardProviderModule&&) = delete;

		~KeyboardProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		KeyboardProviderModule& operator =(const KeyboardProviderModule&) = delete;
		KeyboardProviderModule& operator =(KeyboardProviderModule&&) = delete;

	private:
		InputProviderHandle keyboardProviderHandle; ///< Keyboard provider handle.
	};
}

namespace PonyEngine::Input::Windows
{
	void KeyboardProviderModule::StartUp(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(KeyboardProvider).name());
		keyboardProviderHandle = inputModuleContext->AddProvider([&](IRawInputContext& input)
		{
			return std::make_shared<KeyboardProvider>(input);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(KeyboardProvider).name());
	}

	void KeyboardProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IRawInputModuleContext* inputModuleContext = context.GetData<IRawInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Raw input module context not found");
		}

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(KeyboardProvider).name());
		inputModuleContext->RemoveProvider(keyboardProviderHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(KeyboardProvider).name());
	}
}
