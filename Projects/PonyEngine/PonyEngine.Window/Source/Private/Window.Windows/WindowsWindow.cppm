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
		/// @param engineToUse Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(Core::IEngine& engineToUse, HINSTANCE hInstance, ATOM className, const CreateWindowParams& windowParams);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;

		~WindowsWindow() noexcept;

		[[nodiscard("Pure function")]]
		virtual Core::ObjectInterfaces GetPublicInterfaces() noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool GetIsTickable() const noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept override;
		virtual void SetTitle(const wchar_t* title) override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void ShowWindow() noexcept override;
		virtual void HideWindow() noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND GetWindowHandle() const noexcept override;

		virtual void AddKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver) override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Window::WindowsWindow"; ///< Class name.

	private:
		/// @brief Responds to a destroy message.
		void Destroy() noexcept;

		/// @brief Sends a keyboard message to the @p keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown) const;

		std::vector<Input::IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.

		Core::IEngine* const engine; ///< Engine that owns the window.

		std::wstring windowTitle; ///< Window title cache.
		HWND hWnd; ///< Window handler.
		bool isAlive; ///< Is the system window alive?
	};
}

namespace PonyEngine::Window
{
	WindowsWindow::WindowsWindow(Core::IEngine& engineToUse, const HINSTANCE hInstance, const ATOM className, const CreateWindowParams& windowParams) :
		engine{&engineToUse},
		windowTitle(windowParams.title),
		isAlive{false}
	{
		PONY_LOG(engine, Log::LogType::Info, std::format("Create Windows window of class '{}'.", className).c_str());
		hWnd = CreateWindowExW(
			windowParams.extendedStyle,
			reinterpret_cast<LPCWSTR>(className),
			windowTitle.c_str(),
			windowParams.style,
			windowParams.horizontalPosition, windowParams.verticalPosition,
			windowParams.width, windowParams.height,
			NULL,
			NULL,
			hInstance,
			static_cast<IWindowProc*>(this)
		);

		if (hWnd == NULL)
		{
			throw std::logic_error(std::format("Windows hasn't created a window. Error code: '{}'.", GetLastError()));
		}

		PONY_LOG(engine, Log::LogType::Info, std::format("Windows window of class '{}' created. Window handle: '{}'.", className, reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

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
		PONY_LOG(engine, Log::LogType::Info, "Windows window destroyed.");
	}

	Core::ObjectInterfaces WindowsWindow::GetPublicInterfaces() noexcept
	{
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddObjectInterfacesDeduced<IWindow, IWindowsWindow, IKeyboardProvider>(*this);

		return interfaces;
	}

	bool WindowsWindow::GetIsTickable() const noexcept
	{
		return true;
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
		while (PeekMessageW(&message, hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}

	bool WindowsWindow::IsWindowAlive() const noexcept
	{
		return isAlive;
	}

	const wchar_t* WindowsWindow::GetTitle() const noexcept
	{
		return windowTitle.c_str();
	}

	void WindowsWindow::SetTitle(const wchar_t* const title)
	{
		if (!SetWindowTextW(hWnd, title))
		{
			throw std::logic_error(std::format("Couldn't set a new window title. Error code: '{}'.", GetLastError()));
		}

		windowTitle = title;
	}

	bool WindowsWindow::IsVisible() const noexcept
	{
		return IsWindowVisible(hWnd);
	}

	void WindowsWindow::ShowWindow() noexcept
	{
		::ShowWindow(hWnd, SW_SHOW);
	}

	void WindowsWindow::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
	}

	HWND WindowsWindow::GetWindowHandle() const noexcept
	{
		return hWnd;
	}

	void WindowsWindow::AddKeyboardObserver(Input::IKeyboardObserver* const keyboardMessageObserver)
	{
		assert((keyboardMessageObserver && "The observer is nullptr."));
		assert((std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver) == keyboardMessageObservers.cend() && "The observer has already been added."));
		PONY_LOG(engine, Log::LogType::Info, std::format("Add '{}' keyboard message observer.", keyboardMessageObserver->GetName()).c_str());
		keyboardMessageObservers.push_back(keyboardMessageObserver);
		PONY_LOG(engine, Log::LogType::Info, "Keyboard message observer added.");
	}

	void WindowsWindow::RemoveKeyboardObserver(Input::IKeyboardObserver* const keyboardMessageObserver)
	{
		PONY_LOG_IF(!keyboardMessageObserver, engine, Log::LogType::Warning, "Tried to remove a nullptr keyboard message observer.");

		if (const auto position = std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver); position != keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(engine, Log::LogType::Info, std::format("Remove '{}' keyboard message observer.", keyboardMessageObserver->GetName()).c_str());
			keyboardMessageObservers.erase(position);
			PONY_LOG(engine, Log::LogType::Info, "Keyboard message observer removed.");
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver, engine, Log::LogType::Warning, std::format("Tried to remove a not added keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
		}
	}

	const char* WindowsWindow::GetName() const noexcept
	{
		return StaticName;
	}

	LRESULT WindowsWindow::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_CREATE:
			PONY_LOG(engine, Log::LogType::Info, "Received create command.");
			break;
		case WM_DESTROY:
			PONY_LOG(engine, Log::LogType::Info, "Received destroy command.");
			Destroy();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Received key down command with the code '{}'.", lParam).c_str());
			PushKeyboardKeyMessage(lParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Received key up command with the code '{}'.", lParam).c_str());
			PushKeyboardKeyMessage(lParam, false);
			break;
		default:
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Received an unhandled message. Type: '{}'", uMsg).c_str());
			break;
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
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
			const auto keyboardMessage = Input::KeyboardMessage{.keyCode = keyCode, .isDown = isDown};
			PONY_LOG(engine, Log::LogType::Verbose, std::format("Push keyboard message '{}' to observers.", keyboardMessage.ToString()).c_str());

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
