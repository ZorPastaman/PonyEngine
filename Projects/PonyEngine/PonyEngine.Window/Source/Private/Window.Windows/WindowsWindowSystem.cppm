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

export module PonyEngine.Window.Windows.Implementation:WindowsWindowSystem;

import <algorithm>;
import <exception>;
import <stdexcept>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Log;
import PonyEngine.Input;
import PonyEngine.Math;
import PonyEngine.StringUtility;
import PonyEngine.Window.Windows.Factory;

import :IWindowProc;
import :KeyCodeUtility;

export namespace PonyEngine::Window
{
	/// @brief Windows window system.
	class WindowsWindowSystem final : public Core::ISystem, public Core::ITickableSystem, public IWindowsWindowSystem, public IWindowProc, public Input::IKeyboardProvider
	{
	public:
		/// @brief Creates a @p WindowsWindowSystem.
		/// @param engineToUse Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystem(Core::IEngine& engineToUse, HINSTANCE hInstance, ATOM className, const WindowsWindowParams& windowParams);
		WindowsWindowSystem(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem(WindowsWindowSystem&&) = delete;

		~WindowsWindowSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* MainTitle() const noexcept override;
		virtual void MainTitle(const wchar_t* title) override;

		[[nodiscard("Pure function")]] virtual const wchar_t* SecondaryTitle() const noexcept override;
		virtual void SecondaryTitle(const wchar_t* title) override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void ShowWindow() noexcept override;
		virtual void HideWindow() noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept override;

		virtual void AddKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver) override;
		virtual void RemoveKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver) override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindowSystem& operator =(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem& operator =(WindowsWindowSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Window::WindowsWindowSystem"; ///< Class name.

	private:
		/// @brief Update the window title.
		void UpdateWindowTitle() const;

		/// @brief Responds to a destroy message.
		void Destroy() const noexcept;

		/// @brief Sends a keyboard message to the @p keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown) const;

		Core::IEngine* const engine; ///< Engine that owns the window.
		const HWND hWnd; ///< Window handler.

		std::wstring mainTitle; ///< Window main title cache.
		std::wstring secondaryTitle; ///< Window title text cache.

		std::vector<Input::IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.
	};
}

namespace PonyEngine::Window
{
	/// @brief Creates a Windows window.
	/// @param engine Engine.
	/// @param windowProc Window proc.
	/// @param hInstance Instance.
	/// @param className Window class name.
	/// @param windowParams Window parameters.
	/// @return Created Windows window.
	[[nodiscard("Pure function")]]
	HWND CreateWindowsWindow(const Core::IEngine& engine, IWindowProc& windowProc, HINSTANCE hInstance, ATOM className, const WindowsWindowParams& windowParams);

	WindowsWindowSystem::WindowsWindowSystem(Core::IEngine& engineToUse, const HINSTANCE hInstance, const ATOM className, const WindowsWindowParams& windowParams) :
		engine{&engineToUse},
		mainTitle(windowParams.title),
		hWnd{CreateWindowsWindow(*engine, *this, hInstance, className, windowParams)}
	{
		PONY_LOG(engine, Log::LogType::Debug, "Show window with command '{}'.", windowParams.cmdShow);
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
			PONY_LOG(engine, Log::LogType::Info, "Skip destroying Windows window 'cause it's already been destroyed.");
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

	const wchar_t* WindowsWindowSystem::MainTitle() const noexcept
	{
		return mainTitle.c_str();
	}

	void WindowsWindowSystem::MainTitle(const wchar_t* const title)
	{
		mainTitle = title;
		UpdateWindowTitle();
	}

	const wchar_t* WindowsWindowSystem::SecondaryTitle() const noexcept
	{
		return secondaryTitle.c_str();
	}

	void WindowsWindowSystem::SecondaryTitle(const wchar_t* title)
	{
		secondaryTitle = title;
		UpdateWindowTitle();
	}

	bool WindowsWindowSystem::IsVisible() const noexcept
	{
		return IsWindowVisible(hWnd);
	}

	void WindowsWindowSystem::ShowWindow() noexcept
	{
		::ShowWindow(hWnd, SW_SHOW);
		PONY_LOG(engine, Log::LogType::Debug, "Show window.");
	}

	void WindowsWindowSystem::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
		PONY_LOG(engine, Log::LogType::Debug, "Hide window.");
	}

	HWND WindowsWindowSystem::WindowHandle() const noexcept
	{
		return hWnd;
	}

	void WindowsWindowSystem::AddKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver)
	{
		assert(std::ranges::find(std::as_const(keyboardMessageObservers), &keyboardMessageObserver) == keyboardMessageObservers.cend() && "The observer has already been added.");
		keyboardMessageObservers.push_back(&keyboardMessageObserver);
		PONY_LOG(engine, Log::LogType::Debug, "'{}' keyboard message observer added.", keyboardMessageObserver.Name());
	}

	void WindowsWindowSystem::RemoveKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver)
	{
		if (const auto position = std::ranges::find(std::as_const(keyboardMessageObservers), &keyboardMessageObserver); position != keyboardMessageObservers.cend()) [[likely]]
		{
			keyboardMessageObservers.erase(position);
			PONY_LOG(engine, Log::LogType::Debug, "{} keyboard message observer removed.", keyboardMessageObserver.Name());
		}
		else [[unlikely]]
		{
			PONY_LOG(engine, Log::LogType::Warning, "Tried to remove not added keyboard message observer '{}'.", keyboardMessageObserver.Name());
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

	void WindowsWindowSystem::UpdateWindowTitle() const
	{
		const std::wstring titleToSet = secondaryTitle.length() > 0 ? mainTitle + L" - " + secondaryTitle : mainTitle;

		if (!SetWindowTextW(hWnd, titleToSet.c_str()))
		{
			throw std::logic_error(Utility::SafeFormat("Couldn't set new window title. Error code: '{}'.", GetLastError()));
		}

		PONY_LOG(engine, Log::LogType::Verbose, "Window title set to {}.", Utility::ConvertToString(titleToSet));
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

	HWND CreateWindowsWindow(const Core::IEngine& engine, IWindowProc& windowProc, const HINSTANCE hInstance, const ATOM className, const WindowsWindowParams& windowParams)
	{
		PONY_LOG(&engine, Log::LogType::Info, "Create Windows window of class '{}'. Style: '{}'; Extended style: '{}'; Title: '{}'; Position: '{}'; Size: '{}'; HInstance: '{}'.",
			className, windowParams.style, windowParams.extendedStyle, Utility::ConvertToString(windowParams.title), windowParams.position.ToString(), windowParams.size.ToString(), reinterpret_cast<std::uintptr_t>(hInstance));
		const HWND hWnd = CreateWindowExW(
			windowParams.extendedStyle,
			reinterpret_cast<LPCWSTR>(className),
			windowParams.title.c_str(),
			windowParams.style,
			windowParams.position.X(), windowParams.position.Y(),
			windowParams.size.X(), windowParams.size.Y(),
			NULL,
			NULL,
			hInstance,
			&windowProc
		);
		if (!hWnd)
		{
			throw std::logic_error(Utility::SafeFormat("Windows hasn't created window. Error code: '{}'.", GetLastError()));
		}
		PONY_LOG(&engine, Log::LogType::Info, "Windows window created. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));

		return hWnd;
	}
}
