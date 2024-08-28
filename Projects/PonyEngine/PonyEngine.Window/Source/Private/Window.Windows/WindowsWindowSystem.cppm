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
	/// @brief Windows window system.
	class WindowsWindowSystem final : public Core::ISystem, public Core::ITickableSystem, public IWindowsWindow, public IWindowProc, public Input::IKeyboardProvider
	{
	public:
		/// @brief Creates a @p WindowsWindowSystem.
		/// @param engineToUse Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystem(Core::IEngine& engineToUse, HINSTANCE hInstance, ATOM className, const CreateWindowParams& windowParams);
		WindowsWindowSystem(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem(WindowsWindowSystem&&) = delete;

		~WindowsWindowSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* Title() const noexcept override;
		virtual void Title(const wchar_t* title) override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void ShowWindow() noexcept override;
		virtual void HideWindow() noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept override;

		virtual void AddKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardObserver(Input::IKeyboardObserver* keyboardMessageObserver) override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindowSystem& operator =(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem& operator =(WindowsWindowSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Window::WindowsWindowSystem"; ///< Class name.

	private:
		/// @brief Responds to a destroy message.
		void Destroy() const noexcept;

		/// @brief Sends a keyboard message to the @p keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown) const;

		std::vector<Input::IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.

		Core::IEngine* const engine; ///< Engine that owns the window.

		std::wstring windowTitle; ///< Window title cache.
		HWND hWnd; ///< Window handler.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystem::WindowsWindowSystem(Core::IEngine& engineToUse, const HINSTANCE hInstance, const ATOM className, const CreateWindowParams& windowParams) :
		engine{&engineToUse},
		windowTitle(windowParams.title)
	{
		PONY_LOG(engine, Log::LogType::Info, "Create Windows window of class '{}'.", className);
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

		if (!hWnd)
		{
			throw std::logic_error(std::format("Windows hasn't created window. Error code: '{}'.", GetLastError()));
		}

		PONY_LOG(engine, Log::LogType::Info, "Windows window of class '{}' created. Window handle: '{}'.", className, reinterpret_cast<std::uintptr_t>(hWnd));
		::ShowWindow(hWnd, windowParams.cmdShow);
	}

	WindowsWindowSystem::~WindowsWindowSystem() noexcept
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(engine, Log::LogType::Info, "Destroy Windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			if (!DestroyWindow(hWnd))
			{
				PONY_LOG(engine, Log::LogType::Error, "Error on destroying Windows window. Error code: '{}'.", GetLastError());
			}
			PONY_LOG(engine, Log::LogType::Info, "Windows window destroyed.");
		}
		else
		{
			PONY_LOG(engine, Log::LogType::Info, "Skip destroying Windows windows 'cause it's already been destroyed.");
		}
	}

	void WindowsWindowSystem::Begin()
	{
	}

	void WindowsWindowSystem::End()
	{
	}

	void WindowsWindowSystem::Tick()
	{
		PONY_LOG(engine, Log::LogType::Verbose, "Dispatch messages.");

		MSG message;
		while (PeekMessageW(&message, hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}

	bool WindowsWindowSystem::IsWindowAlive() const noexcept
	{
		return IsWindow(hWnd);
	}

	const wchar_t* WindowsWindowSystem::Title() const noexcept
	{
		return windowTitle.c_str();
	}

	void WindowsWindowSystem::Title(const wchar_t* const title)
	{
		if (!SetWindowTextW(hWnd, title))
		{
			throw std::logic_error(std::format("Couldn't set new window title. Error code: '{}'.", GetLastError()));
		}

		windowTitle = title;
	}

	bool WindowsWindowSystem::IsVisible() const noexcept
	{
		return IsWindowVisible(hWnd);
	}

	void WindowsWindowSystem::ShowWindow() noexcept
	{
		::ShowWindow(hWnd, SW_SHOW);
	}

	void WindowsWindowSystem::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
	}

	HWND WindowsWindowSystem::WindowHandle() const noexcept
	{
		return hWnd;
	}

	void WindowsWindowSystem::AddKeyboardObserver(Input::IKeyboardObserver* const keyboardMessageObserver)
	{
		assert((keyboardMessageObserver && "The observer is nullptr."));
		assert((std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver) == keyboardMessageObservers.cend() && "The observer has already been added."));
		PONY_LOG(engine, Log::LogType::Info, "Add '{}' keyboard message observer.", keyboardMessageObserver->Name());
		keyboardMessageObservers.push_back(keyboardMessageObserver);
		PONY_LOG(engine, Log::LogType::Info, "Keyboard message observer added.");
	}

	void WindowsWindowSystem::RemoveKeyboardObserver(Input::IKeyboardObserver* const keyboardMessageObserver)
	{
		PONY_LOG_IF(!keyboardMessageObserver, engine, Log::LogType::Warning, "Tried to remove nullptr keyboard message observer.");

		if (const auto position = std::ranges::find(std::as_const(keyboardMessageObservers), keyboardMessageObserver); position != keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(engine, Log::LogType::Info, "Remove '{}' keyboard message observer.", keyboardMessageObserver->Name());
			keyboardMessageObservers.erase(position);
			PONY_LOG(engine, Log::LogType::Info, "Keyboard message observer removed.");
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver, engine, Log::LogType::Warning, "Tried to remove not added keyboard message observer '{}'.", keyboardMessageObserver->Name());
		}
	}

	const char* WindowsWindowSystem::Name() const noexcept
	{
		return StaticName;
	}

	LRESULT WindowsWindowSystem::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
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
			PONY_LOG(engine, Log::LogType::Verbose, "Received key down command with code '{}'.", lParam);
			PushKeyboardKeyMessage(lParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(engine, Log::LogType::Verbose, "Received key up command with code '{}'.", lParam);
			PushKeyboardKeyMessage(lParam, false);
			break;
		default:
			PONY_LOG(engine, Log::LogType::Verbose, "Received unhandled message. Type: '{}'", uMsg);
			break;
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindowSystem::Destroy() const noexcept
	{
		engine->Stop();
	}

	void WindowsWindowSystem::PushKeyboardKeyMessage(const LPARAM lParam, const bool isDown) const
	{
		if (const Input::KeyboardKeyCode keyCode = ConvertToKeyCode(lParam); keyCode != Input::KeyboardKeyCode::None)
		{
			const auto keyboardMessage = Input::KeyboardMessage{.keyCode = keyCode, .isDown = isDown};
			PONY_LOG(engine, Log::LogType::Verbose, "Push keyboard message '{}' to observers.", keyboardMessage.ToString());

			for (Input::IKeyboardObserver* const observer : keyboardMessageObservers)
			{
				try
				{
					observer->Observe(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(engine, e, "On observing keyboard key message");
				}
			}
		}
	}
}
