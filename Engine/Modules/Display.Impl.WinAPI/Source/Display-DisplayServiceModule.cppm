/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display.Impl.WinAPI:DisplayServiceModule;

import std;

import PonyEngine.Application;
import PonyEngine.Utility;

import :DisplayService;

export namespace PonyEngine::Display
{
	/// @brief Display service module.
	class DisplayServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		DisplayServiceModule() noexcept = default;
		DisplayServiceModule(const DisplayServiceModule&) = delete;
		DisplayServiceModule(DisplayServiceModule&&) = delete;

		~DisplayServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		DisplayServiceModule& operator =(const DisplayServiceModule&) = delete;
		DisplayServiceModule& operator =(DisplayServiceModule&&) = delete;

	private:
		std::unique_ptr<DisplayService> displayService;
	};
}

namespace PonyEngine::Display
{
	void DisplayServiceModule::StartUp(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		displayService = std::make_unique<DisplayService>(context.Application());
		const auto displayServiceScopeGuard = Utility::ScopeGuard([&]() noexcept { displayService.reset(); }, scopeGuardFlag);
		context.AddInterface<IDisplayService>(*displayService);

		scopeGuardFlag.Release();
	}

	void DisplayServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IDisplayService>(*displayService);
		displayService.reset();
	}
}
