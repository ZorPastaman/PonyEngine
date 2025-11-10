/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Keyboard.Impl:KeyboardProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Input.Ext;

import :KeyboardProvider;

export namespace PonyEngine::Input
{
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
		InputProviderHandle keyboardProviderHandle;
	};
}

namespace PonyEngine::Input
{
	void KeyboardProviderModule::StartUp(Application::IModuleContext& context)
	{
		IInputModuleContext* inputModuleContext = context.GetData<IInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Input module context not found.");
		}

		keyboardProviderHandle = inputModuleContext->AddProvider([&](IInputContext& input)
		{
#if PONY_WINDOWS
			return std::make_shared<Windows::KeyboardProvider>(input);
#else
#error "Unsupported platform!"
#endif
		});
	}

	void KeyboardProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IInputModuleContext* inputModuleContext = context.GetData<IInputModuleContext>();
		if (!inputModuleContext) [[unlikely]]
		{
			throw std::logic_error("Input module context not found.");
		}

		inputModuleContext->RemoveProvider(keyboardProviderHandle);
	}
}
