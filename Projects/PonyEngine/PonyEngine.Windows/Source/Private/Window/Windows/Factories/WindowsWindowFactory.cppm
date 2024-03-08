/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Factories.Implementation:WindowsWindowFactory;

import <string>;
import <windows.h>;

import PonyEngine.Core;
import PonyEngine.Window;
import PonyEngine.Window.Windows;
import PonyEngine.Window.Windows.Factories;
import PonyEngine.Window.Windows.Implementation;

namespace PonyEngine::Window
{
	export class WindowsWindowFactory : public IWindowsWindowFactory
	{
	public:
		WindowsWindowFactory(std::string title);
		~WindowsWindowFactory();

		[[nodiscard("Pure function")]]
		virtual IWindowsWindow* Create(Core::IEngine& engine) override;
		virtual void Destroy(IWindow* window) override;

	private:
		std::string m_title;
	};

	void Dummy();

	WindowsWindowFactory::WindowsWindowFactory(std::string title) :
		m_title(title)
	{
	}

	WindowsWindowFactory::~WindowsWindowFactory()
	{
	}

	IWindowsWindow* WindowsWindowFactory::Create(Core::IEngine& engine)
	{
		HMODULE hModule;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&Dummy), &hModule);
		if (hModule == nullptr)
		{
			throw std::logic_error("Couldn't find a dll module to create a window.");
		}

		return new WindowsWindow(m_title, engine, hModule, SW_NORMAL);
	}

	void WindowsWindowFactory::Destroy(IWindow* window)
	{
		delete static_cast<WindowsWindow*>(window);
	}

	void Dummy()
	{
	}
}
