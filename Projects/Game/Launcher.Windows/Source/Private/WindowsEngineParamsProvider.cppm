/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher.Windows:WindowsEngineParamsProvider;

import PonyEngine.Core.Factories;
import PonyEngine.Window.Factories;
import PonyEngine.Window.Windows.Factories;
import PonyEngine.Window.Windows.Implementation;

import Launcher;

namespace Launcher
{
	/// @brief Windows engine params provider.
	export class WindowsEngineParamsProvider final : public IPlatformEngineParamsProvider
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsEngineParamsProvider();
		WindowsEngineParamsProvider(const WindowsEngineParamsProvider&) = delete;
		WindowsEngineParamsProvider(WindowsEngineParamsProvider&&) = delete;

		virtual ~WindowsEngineParamsProvider() noexcept;

		virtual void Modify(PonyEngine::Core::EngineParams& engineParams) const override;

		WindowsEngineParamsProvider& operator =(const WindowsEngineParamsProvider&) = delete;
		WindowsEngineParamsProvider& operator =(WindowsEngineParamsProvider&&) = delete;

	private:
		// Set all platform-dependent factories here.
		PonyEngine::Window::IWindowsWindowFactory* m_windowsWindowFactory;
	};

	WindowsEngineParamsProvider::WindowsEngineParamsProvider()
	{
		// Create all platform-dependent factories here.
		PonyEngine::Window::WindowClassParams windowClassParams(L"Pony Engine Game");
		m_windowsWindowFactory = PonyEngine::Window::CreateWindowsWindowFactory(windowClassParams);
		m_windowsWindowFactory->SetTitle(L"Pony Engine Game");
	}

	WindowsEngineParamsProvider::~WindowsEngineParamsProvider() noexcept
	{
		// Destroy all platform-dependent factories here.
		PonyEngine::Window::DestroyWindowsWindowFactory(m_windowsWindowFactory);
	}

	void WindowsEngineParamsProvider::Modify(PonyEngine::Core::EngineParams& engineParams) const
	{
		// Set platform-dependent engine parameters here.
		engineParams.windowFactory = m_windowsWindowFactory;
	}
}
