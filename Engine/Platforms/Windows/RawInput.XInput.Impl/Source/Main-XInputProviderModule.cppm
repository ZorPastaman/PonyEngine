/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.XInput.Impl.Windows:XInputProviderModule;

import std;

import PonyEngine.Application;
import PonyEngine.RawInput.Ext;

import :XInputProvider;

export namespace PonyEngine::RawInput::XInput
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
		std::unique_ptr<XInputProvider> xinputProvider; ///< XInput provider.
	};
}

namespace PonyEngine::RawInput::XInput
{
	void XInputProviderModule::StartUp(Application::IModuleContext& context)
	{
		xinputProvider = std::make_unique<XInputProvider>(context.Application());
	}

	void XInputProviderModule::ShutDown(Application::IModuleContext& context)
	{
		xinputProvider.reset();
	}
}
