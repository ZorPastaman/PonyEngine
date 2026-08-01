/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl.Windows:MouseProviderModule;

import std;

import PonyEngine.Application;
import PonyEngine.RawInput.Ext;

import :MouseProvider;

export namespace PonyEngine::RawInput::Mouse
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
		std::unique_ptr<MouseProvider> mouseProvider; ///< Mouse provider.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	void MouseProviderModule::StartUp(Application::IModuleContext& context)
	{
		mouseProvider = std::make_unique<MouseProvider>(context.Application());
	}

	void MouseProviderModule::ShutDown(Application::IModuleContext& context)
	{
		mouseProvider.reset();
	}
}
