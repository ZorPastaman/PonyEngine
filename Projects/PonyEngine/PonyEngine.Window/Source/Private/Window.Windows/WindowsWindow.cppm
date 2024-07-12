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

#include "PonyEngine/Log/EngineLog.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindow;

import <algorithm>;
import <format>;
import <exception>;
import <stdexcept>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Log;
import PonyEngine.Input;
import PonyEngine.Window;
import PonyEngine.Window.Windows;

import :CreateWindowParams;
import :IWindowProc;
import :KeyCodeUtility;

export namespace PonyEngine::Window
{
	/// @brief Windows window.
	class WindowsWindow final : public Core::ISystem, public IWindowsWindow, public IWindowProc, public Input::IKeyboardProvider
	{
	public:
		/// @brief Creates a @p WindowsWindow.
		/// @param engine Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(Core::IEngine& engine, HINSTANCE hInstance, ATOM className, const CreateWindowParams& windowParams);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;

		~WindowsWindow() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept override;
		virtual void SetTitle(const wchar_t* title) override;

		virtual void ShowWindow() override;
		virtual void HideWindow() override;

		[[nodiscard("Pure function")]]
		virtual HWND GetWindowHandle() const noexcept override;

		virtual void AddKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver) override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

		static constexpr const char* StaticName = "PonyEngine::Window::WindowsWindow"; ///< Class name.

	private:
		/// @brief Responds to a destroy message.
		void Destroy() noexcept;

		/// @brief Sends a keyboard message to the @p keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown) const;

		std::vector<Input::IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.

		Core::IEngine* const engine; ///< Engine that owns the window.

		std::wstring title;
		HWND hWnd; ///< Window handler.
		bool isAlive; ///< Is the system window alive?
	};
}

namespace PonyEngine::Window
{
	WindowsWindow::WindowsWindow(Core::IEngine& engine, const HINSTANCE hInstance, const ATOM className, const CreateWindowParams& windowParams) :
		engine{&engine},
		title(windowParams.title),
		isAlive{false}
	{
		PONY_LOG(this->engine, Log::LogType::Info, std::format("Create Windows window of the class '{}'.", className).c_str());
		hWnd = CreateWindowEx(
			windowParams.extendedStyle,
			reinterpret_cast<LPCTSTR>(className),
			title.c_str(),
			windowParams.style,
			windowParams.horizontalPosition, windowParams.verticalPosition,
			windowParams.width, windowParams.height,
			NULL,
			NULL,
			hInstance,
			this
		);

		if (hWnd == NULL)
		{
			throw std::logic_error(std::format("Windows hasn't created a window. Error code: '{}'.", GetLastError()));
		}

		PONY_LOG(this->engine, Log::LogType::Info, std::format("Windows window of the class '{}' created. Window handle: '{}'.", className, reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		isAlive = true;
		::ShowWindow(hWnd, windowParams.cmdShow);
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
		PONY_LOG(engine, Log::LogType::Info, std::format("Destroy Windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		try
		{
			DestroyWindow(hWnd);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(engine, e, "On destroying a window");
		}
		PONY_LOG(engine, Log::LogType::Info, std::format("Windows window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
	}

	void WindowsWindow::Begin()
	{
	}

	void WindowsWindow::End()
	{
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

	bool WindowsWindow::IsWindowAlive() const noexcept
	{
		return isAlive;
	}

	const char* WindowsWindow::GetName() const noexcept
	{
		return StaticName;
	}

	const wchar_t* WindowsWindow::GetTitle() const noexcept
	{
		return title.c_str();
	}

	void WindowsWindow::SetTitle(const wchar_t* const title)
	{
		if (!SetWindowText(hWnd, title))
		{
			throw std::logic_error(std::format("Couldn't set a new window title. Error code: '{}'.", GetLastError()));
		}

		this->title = title;
	}

	void WindowsWindow::ShowWindow()
	{
		::ShowWindow(hWnd, SW_SHOW);
	}

	void WindowsWindow::HideWindow()
	{
		::ShowWindow(hWnd, SW_HIDE);
	}

	HWND WindowsWindow::GetWindowHandle() const noexcept
	{
		return hWnd;
	}

	void WindowsWindow::AddKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver)
	{
		assert((keyboardMessageObserver && "The observer is nullptr."));
		assert((std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver) == keyboardMessageObservers.cend() && "The observer is already added."));

		PONY_LOG(engine, Log::LogType::Info, std::format("Add keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
		keyboardMessageObservers.push_back(keyboardMessageObserver);
		PONY_LOG(engine, Log::LogType::Info, "Keyboard message observer added.");
	}

	void WindowsWindow::RemoveKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver)
	{
		PONY_LOG_IF(keyboardMessageObserver == nullptr, engine, Log::LogType::Warning, "Tried to remove a nullptr keyboard message observer.");

		if (const auto position = std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver); position != keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(engine, Log::LogType::Info, std::format("Remove a keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
			keyboardMessageObservers.erase(position);
			PONY_LOG(engine, Log::LogType::Info, "Keyboard message observer removed.");
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver != nullptr, engine, Log::LogType::Warning, std::format("Tried to remove a not added keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
		}
	}

	LRESULT WindowsWindow::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_CREATE:
			PONY_LOG(engine, Log::LogType::Info, "Create command.");
			break;
		case WM_DESTROY:
			PONY_LOG(engine, Log::LogType::Info, "Destroy command.");
			Destroy();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Key down command with the code '{}' and param '{}'.", wParam, lParam).c_str());
			PushKeyboardKeyMessage(lParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Key up command with the code '{}' and param '{}'.", wParam, lParam).c_str());
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
		engine->Stop();
	}

	void WindowsWindow::PushKeyboardKeyMessage(const LPARAM lParam, const bool isDown) const
	{
		if (const Input::KeyboardKeyCode keyCode = ConvertToKeyCode(lParam); keyCode != Input::KeyboardKeyCode::None)
		{
			const Input::KeyboardMessage keyboardMessage(keyCode, isDown);
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Push a keyboard message '{}' to the observers.", keyboardMessage.ToString()).c_str());

			for (Input::IKeyboardObserver* const observer : keyboardMessageObservers)
			{
				try
				{
					observer->Observe(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(engine, e, "On observing a keyboard key message");
				}
			}
		}
	}
}
