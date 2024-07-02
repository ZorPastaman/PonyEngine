/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/LogMacro.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindow;

import <algorithm>;
import <cstdint>;
import <format>;
import <exception>;
import <ranges>;
import <stdexcept>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Log;
import PonyEngine.Window;
import PonyEngine.Window.Windows;

import :IWindowProc;
import :WindowParams;
import :WindowsKeyCodeUtility;

export namespace PonyEngine::Window
{
	/// @brief Engine window for @p Windows platform.
	class WindowsWindow final : public Core::ISystem, public IWindowsWindow, public IWindowProc
	{
	public:
		/// @brief Creates a @p WindowsWindow.
		/// @param engine Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(Core::IEngine& engine, HINSTANCE hInstance, ATOM className, const WindowParams& windowParams);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;

		~WindowsWindow() noexcept;

		virtual void Begin() override;
		virtual void End() override;
		[[nodiscard("Pure function")]]
		virtual bool IsTickable() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept override;
		virtual void SetTitle(const wchar_t* title) override;

		virtual void AddKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;

		virtual void ShowWindow() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual HWND GetWindowHandle() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

	private:
		/// @brief Responds to a destroy message.
		void Destroy() noexcept;

		/// @brief Sends a keyboard message to the @p keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown) const;

	public:
		static const char* const Name; ///< WindowsWindow class name.

	private:
		std::vector<IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.

		std::wstring title; ///< Window title.
		HWND hWnd; ///< Window handler.
		const int nCmdShow; ///< Show type.
		bool isAlive; ///< Is the system window alive?

		Core::IEngine& engine; ///< Engine that owns the window.
	};
}

namespace PonyEngine::Window
{
	WindowsWindow::WindowsWindow(Core::IEngine& engine, const HINSTANCE hInstance, const ATOM className, const WindowParams& windowParams) :
		title(windowParams.title),
		nCmdShow{windowParams.cmdShow},
		isAlive{false},
		engine{engine}
	{
		PONY_LOG(engine, Log::LogType::Info, std::format("Create a system window of the class id '{}'.", className).c_str());
		hWnd = CreateWindowEx(
			0,
			reinterpret_cast<LPCTSTR>(className),
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (hWnd == NULL)
		{
			throw std::logic_error(std::format("Windows hasn't created a window. Error code: '{}'.", GetLastError()));
		}

		isAlive = true;
		PONY_LOG(engine, Log::LogType::Info, std::format("System window of the class id '{}' created. Window handle: '{}'.", className, reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, std::format("Destroy a system window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		try
		{
			DestroyWindow(hWnd);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(engine, e, "On a window destroy.");
		}
		PONY_LOG(engine, Log::LogType::Info, std::format("System window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
	}

	void WindowsWindow::Begin()
	{
	}

	void WindowsWindow::End()
	{
	}

	bool WindowsWindow::IsTickable() const noexcept
	{
		return true;
	}

	const char* WindowsWindow::GetName() const noexcept
	{
		return Name;
	}

	const wchar_t* WindowsWindow::GetTitle() const noexcept
	{
		return title.c_str(); // TODO: Get an actual window name.
	}

	void WindowsWindow::SetTitle(const wchar_t* const title)
	{
		if (!SetWindowText(hWnd, title))
		{
			throw std::logic_error(std::format("Couldn't set a new window title. Error code: '{}'.", GetLastError()));
		}

		this->title = title;
	}

	void WindowsWindow::AddKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		assert((keyboardMessageObserver != nullptr));
		assert((std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver) == keyboardMessageObservers.cend()));
		PONY_LOG(engine, Log::LogType::Info, std::format("Add a keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());

		keyboardMessageObservers.push_back(keyboardMessageObserver);
	}

	void WindowsWindow::RemoveKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		PONY_LOG_IF(keyboardMessageObserver == nullptr, engine, Log::LogType::Warning, "Tried to remove a nullptr keyboard message observer.");

		if (const auto position = std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver); position != keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(engine, Log::LogType::Info, std::format("Remove a keyboard message observer '{}'", keyboardMessageObserver->GetName()).c_str());
			keyboardMessageObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver != nullptr, engine, Log::LogType::Warning, std::format("Tried to remove a not added keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
		}
	}

	void WindowsWindow::ShowWindow()
	{
		::ShowWindow(hWnd, nCmdShow);
	}

	void WindowsWindow::Tick()
	{
		PONY_LOG(engine, Log::LogType::Verbose, "Dispatch messages.");

		MSG message;
		while (PeekMessage(&message, hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	HWND WindowsWindow::GetWindowHandle() const noexcept
	{
		return hWnd;
	}

	bool WindowsWindow::IsWindowAlive() const noexcept
	{
		return isAlive;
	}

	LRESULT WindowsWindow::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_DESTROY:
			PONY_LOG(engine, Log::LogType::Info, "Received a destroy command.");
			Destroy();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Received a key down command with the code '{}' and param '{}'.", wParam, lParam).c_str());
			PushKeyboardKeyMessage(lParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Received a key up command with the code '{}' and param '{}'.", wParam, lParam).c_str());
			PushKeyboardKeyMessage(lParam, false);
			break;
		default: 
			break;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::Destroy() noexcept
	{
		isAlive = false;
		engine.Stop();
	}

	void WindowsWindow::PushKeyboardKeyMessage(const LPARAM lParam, const bool isDown) const
	{
		if (const KeyboardKeyCode keyCode = ConvertToKeyCode(lParam); keyCode != KeyboardKeyCode::None)
		{
			const KeyboardMessage keyboardMessage(keyCode, isDown);
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Push a keyboard message '{}' to the observers.", keyboardMessage.ToString()).c_str());

			for (IKeyboardObserver* const observer : keyboardMessageObservers)
			{
				try
				{
					observer->Observe(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(engine, e, "On observing to a keyboard key message.");
				}
			}
		}
	}

	const char* const WindowsWindow::Name = "PonyEngine::Window::WindowsWindow";
}
