/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Keyboard.Impl.Windows:KeyboardProviderModule;

import std;

import PonyEngine.Application;
import PonyEngine.RawInput.Ext;

import :KeyboardProvider;

export namespace PonyEngine::RawInput::Keyboard
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
		std::unique_ptr<KeyboardProvider> keyboardProvider; ///< Keyboard provider.
	};
}

namespace PonyEngine::RawInput::Keyboard
{
	void KeyboardProviderModule::StartUp(Application::IModuleContext& context)
	{
		keyboardProvider = std::make_unique<KeyboardProvider>(context.Application());
	}

	void KeyboardProviderModule::ShutDown(Application::IModuleContext& context)
	{
		keyboardProvider.reset();
	}
}
