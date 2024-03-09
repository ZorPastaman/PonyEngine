/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:WindowManager;

import PonyEngine.Core;
import PonyEngine.Window;
import PonyEngine.Window.Factories;

namespace PonyEngine::Core
{
	export class WindowManager final
	{
	public:
		WindowManager(Window::IWindowFactory* windowFactory, IEngine& engine);
		~WindowManager();

		Window::IWindow* GetWindow() const noexcept;

	private:
		Window::IWindow* const m_window;
		Window::IWindowFactory* const m_windowFactory;
	};

	WindowManager::WindowManager(Window::IWindowFactory* windowFactory, IEngine& engine) :
		m_windowFactory{windowFactory},
		m_window{windowFactory != nullptr ? windowFactory->Create(engine) : nullptr}
	{
	}

	WindowManager::~WindowManager()
	{
		if (m_windowFactory != nullptr)
		{
			m_windowFactory->Destroy(m_window);
		}
	}

	Window::IWindow* WindowManager::GetWindow() const noexcept
	{
		return m_window;
	}
}
