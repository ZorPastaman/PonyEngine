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

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindowSystem;

import <algorithm>;
import <exception>;
import <stdexcept>;
import <string>;
import <vector>;

import PonyBase.StringUtility;

import PonyMath.Core;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
import PonyEngine.Screen;

import PonyEngine.Window.Windows.Factory;

import :IWindowProc;
import :KeyCodeUtility;
import :WindowProcFunction;

export namespace PonyEngine::Window
{
	/// @brief Windows window system.
	class WindowsWindowSystem final : public Core::ITickableEngineSystem, public IWindowsWindowSystem, public IWindowProc, public Input::IKeyboardProvider
	{
	public:
		/// @brief Creates a @p WindowsWindowSystem.
		/// @param engine Engine.
		/// @param hInstance Instance.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystem(Core::IEngine& engine, HINSTANCE hInstance, ATOM className, const WindowsWindowParams& windowParams);
		WindowsWindowSystem(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem(WindowsWindowSystem&&) = delete;

		~WindowsWindowSystem() noexcept = default;

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
		virtual PonyMath::Core::Vector2<int> Position() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Screen::Resolution<unsigned int> Resolution() const noexcept override;

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

		/// @brief Creates a window.
		/// @return Created window.
		[[nodiscard("Pure function")]]
		HWND CreateControlledWindow();

		HINSTANCE hInstance; ///< Instance.
		ATOM className; ///< Class name.
		DWORD style; ///< Window style.
		DWORD extendedStyle; ///< Extended window style.
		int cmdShow; ///< Window cmdShow.

		std::wstring mainTitle; ///< Window main title cache.
		std::wstring secondaryTitle; ///< Window title text cache.

		Core::IEngine* engine; ///< Engine.

		HWND hWnd; ///< Window handler.

		std::vector<Input::IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystem::WindowsWindowSystem(Core::IEngine& engine, const HINSTANCE hInstance, const ATOM className, const WindowsWindowParams& windowParams) :
		hInstance{hInstance},
		className{className},
		style{windowParams.style},
		extendedStyle{windowParams.extendedStyle},
		cmdShow{windowParams.cmdShow},
		mainTitle(windowParams.title),
		engine{&engine},
		hWnd{}
	{
	}

	void WindowsWindowSystem::Begin()
	{
		hWnd = CreateControlledWindow();

		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Debug, "Show window with command '{}'.", cmdShow);
		::ShowWindow(hWnd, cmdShow);
	}

	void WindowsWindowSystem::End()
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Unregister window proc. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			UnregisterWindowProc(hWnd);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Window proc unregistered.");

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Destroy Windows window. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			if (!DestroyWindow(hWnd)) [[unlikely]]
			{
				PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Error, "Error on destroying Windows window. Error code: '0x{:X}'.", GetLastError());
			}
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Windows window destroyed.");
		}
		else
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Skip destroying Windows window 'cause it's already been destroyed.");
		}
	}

	void WindowsWindowSystem::Tick()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Dispatch messages.");

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
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Main title set to '{}'.", PonyBase::Utility::ConvertToString(mainTitle));
		UpdateWindowTitle();
	}

	const wchar_t* WindowsWindowSystem::SecondaryTitle() const noexcept
	{
		return secondaryTitle.c_str();
	}

	void WindowsWindowSystem::SecondaryTitle(const wchar_t* title)
	{
		secondaryTitle = title;
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Secondary title set to '{}'.", PonyBase::Utility::ConvertToString(secondaryTitle));
		UpdateWindowTitle();
	}

	bool WindowsWindowSystem::IsVisible() const noexcept
	{
		return IsWindowVisible(hWnd);
	}

	void WindowsWindowSystem::ShowWindow() noexcept
	{
		::ShowWindow(hWnd, SW_SHOW);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Show window.");
	}

	void WindowsWindowSystem::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Hide window.");
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::Position() const noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return PonyMath::Core::Vector2<int>(static_cast<int>(rect.left), static_cast<int>(rect.right));
	}

	Screen::Resolution<unsigned int> WindowsWindowSystem::Resolution() const noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return Screen::Resolution<unsigned int>(static_cast<unsigned int>(rect.right - rect.left), static_cast<unsigned int>(rect.bottom - rect.top));
	}

	HWND WindowsWindowSystem::WindowHandle() const noexcept
	{
		return hWnd;
	}

	void WindowsWindowSystem::AddKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver)
	{
		assert(std::ranges::find(std::as_const(keyboardMessageObservers), &keyboardMessageObserver) == keyboardMessageObservers.cend() && "The observer has already been added.");
		keyboardMessageObservers.push_back(&keyboardMessageObserver);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "'{}' keyboard message observer added.", keyboardMessageObserver.Name());
	}

	void WindowsWindowSystem::RemoveKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver)
	{
		if (const auto position = std::ranges::find(std::as_const(keyboardMessageObservers), &keyboardMessageObserver); position != keyboardMessageObservers.cend()) [[likely]]
		{
			keyboardMessageObservers.erase(position);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "{} keyboard message observer removed.", keyboardMessageObserver.Name());
		}
		else [[unlikely]]
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Warning, "Tried to remove not added keyboard message observer '{}'.", keyboardMessageObserver.Name());
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
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Received create command.");
			break;
		case WM_DESTROY:
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Received destroy command.");
			Destroy();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Received key down command with code '0x{:X}'.", lParam);
			PushKeyboardKeyMessage(lParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Received key up command with code '0x{:X}'.", lParam);
			PushKeyboardKeyMessage(lParam, false);
			break;
		default:
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Received unhandled message. Type: '0x{:X}'", uMsg);
			break;
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindowSystem::UpdateWindowTitle() const
	{
		const std::wstring titleToSet = secondaryTitle.length() > 0 ? mainTitle + L" - " + secondaryTitle : mainTitle;

		if (!SetWindowTextW(hWnd, titleToSet.c_str()))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set new window title. Error code: '0x{:X}'.", GetLastError()));
		}

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Window title set to '{}'.", PonyBase::Utility::ConvertToString(titleToSet));
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
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Push keyboard message '{}' to observers.", keyboardMessage.ToString());

			for (Input::IKeyboardObserver* const observer : keyboardMessageObservers)
			{
				try
				{
					observer->Observe(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(engine->Logger(), e, "On observing keyboard key message");
				}
			}
		}
	}

	HWND WindowsWindowSystem::CreateControlledWindow()
	{
		const auto screenSystem = engine->SystemManager().FindSystem<Screen::IScreenSystem>();
		if (!screenSystem)
		{
			throw std::logic_error("Failed to find Screen system.");
		}

		const Screen::Resolution<unsigned int> resolution = screenSystem->DisplayResolution();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window of class '0x{:X}'. Style: '0x{:X}'; Extended style: '0x{:X}'; Title: '{}'; Resolution: '{}'; HInstance: '0x{:X}'.",
			className, style, extendedStyle, PonyBase::Utility::ConvertToString(mainTitle), resolution.ToString(), reinterpret_cast<std::uintptr_t>(hInstance));

		auto rect = RECT
		{
			.left = 0L,
			.top = 0L,
			.right = static_cast<LONG>(resolution.Width()),
			.bottom = static_cast<LONG>(resolution.Height())
		};
		if (!AdjustWindowRectEx(&rect, style, false, extendedStyle))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}
		const auto position = PonyMath::Core::Vector2<int>(rect.left, rect.top);
		const auto size = PonyEngine::Screen::Resolution<unsigned int>(rect.right - rect.left, rect.bottom - rect.top);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Actual window position: '{}'. Actual window size: '{}'.", position.ToString(), size.ToString());

		const HWND windowHandle = CreateWindowExW(
			extendedStyle,
			reinterpret_cast<LPCWSTR>(className),
			mainTitle.c_str(),
			style,
			position.X(), position.Y(),
			size.Width(), size.Height(),
			nullptr,
			nullptr,
			hInstance,
			static_cast<IWindowProc*>(this)
		);
		if (!windowHandle)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Windows window created. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Register window proc. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));
		RegisterWindowProc(windowHandle, this);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Window proc registered.");

		return windowHandle;
	}
}
