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
import <cstdint>;
import <exception>;
import <stdexcept>;
import <string>;
import <string_view>;
import <utility>;
import <vector>;

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Utility;

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
		WindowsWindowSystem(Core::IEngineContext& engine, HINSTANCE hInstance, ATOM className, const WindowsWindowSystemParams& windowParams);
		WindowsWindowSystem(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem(WindowsWindowSystem&&) = delete;

		~WindowsWindowSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual std::wstring_view MainTitle() const noexcept override;
		virtual void MainTitle(std::wstring_view title) override;

		[[nodiscard("Pure function")]]
		virtual std::wstring_view SecondaryTitle() const noexcept override;
		virtual void SecondaryTitle(std::wstring_view title) override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void ShowWindow() noexcept override;
		virtual void HideWindow() noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<int> Position() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<unsigned int> Resolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept override;

		virtual void AddKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver) override;
		virtual void RemoveKeyboardObserver(Input::IKeyboardObserver& keyboardMessageObserver) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindowSystem& operator =(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem& operator =(WindowsWindowSystem&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Window::WindowsWindowSystem"; ///< Class name.

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
		/// @brief Gets a target window position.
		/// @return Target window position.
		[[nodiscard("Pure function")]]
		PonyMath::Core::Vector2<int> GetTargetPosition() const noexcept;
		/// @brief Gets a target window resolution.
		/// @return Target window resolution.
		[[nodiscard("Pure function")]]
		PonyMath::Utility::Resolution<unsigned int> GetTargetResolution() const noexcept;

		HINSTANCE hInstance; ///< Instance.
		ATOM className; ///< Class name.

		WindowsWindowStyle style; ///< Window style.
		int cmdShow; ///< Window cmdShow.
		WindowRect windowRect; ///< WindowRect.

		std::wstring mainTitle; ///< Window main title cache.
		std::wstring secondaryTitle; ///< Window title text cache.

		Core::IEngineContext* engine; ///< Engine.

		HWND hWnd; ///< Window handler.

		std::vector<Input::IKeyboardObserver*> keyboardMessageObservers; ///< Keyboard message observers.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystem::WindowsWindowSystem(Core::IEngineContext& engine, const HINSTANCE hInstance, const ATOM className, const WindowsWindowSystemParams& windowParams) :
		hInstance{hInstance},
		className{className},
		style{windowParams.windowsWindowStyle},
		cmdShow{windowParams.cmdShow},
		windowRect(windowParams.rect),
		mainTitle(windowParams.title),
		engine{&engine},
		hWnd{nullptr}
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

	std::wstring_view WindowsWindowSystem::MainTitle() const noexcept
	{
		return mainTitle;
	}

	void WindowsWindowSystem::MainTitle(const std::wstring_view title)
	{
		mainTitle = title;
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Main title set to '{}'.", PonyBase::Utility::ConvertToString(mainTitle));
		UpdateWindowTitle();
	}

	std::wstring_view WindowsWindowSystem::SecondaryTitle() const noexcept
	{
		return secondaryTitle;
	}

	void WindowsWindowSystem::SecondaryTitle(const std::wstring_view title)
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
		cmdShow = SW_SHOW;
		::ShowWindow(hWnd, cmdShow);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Show window.");
	}

	void WindowsWindowSystem::HideWindow() noexcept
	{
		cmdShow = SW_HIDE;
		::ShowWindow(hWnd, cmdShow);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Hide window.");
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::Position() const noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return PonyMath::Core::Vector2<int>(static_cast<int>(rect.left), static_cast<int>(rect.right));
	}

	PonyMath::Utility::Resolution<unsigned int> WindowsWindowSystem::Resolution() const noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return PonyMath::Utility::Resolution<unsigned int>(static_cast<unsigned int>(rect.right - rect.left), static_cast<unsigned int>(rect.bottom - rect.top));
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

	std::string_view WindowsWindowSystem::Name() const noexcept
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
		PonyMath::Core::Vector2<int> position = GetTargetPosition();
		PonyMath::Utility::Resolution<unsigned int> resolution = GetTargetResolution();
		auto rect = RECT
		{
			.left = static_cast<LONG>(position.X()),
			.top = static_cast<LONG>(position.Y()),
			.right = static_cast<LONG>(position.X()) + static_cast<LONG>(resolution.Width()),
			.bottom = static_cast<LONG>(position.Y()) + static_cast<LONG>(resolution.Height())
		};
		if (!AdjustWindowRectEx(&rect, style.style, false, style.extendedStyle))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}
		position = PonyMath::Core::Vector2<int>(rect.left, rect.top);
		resolution = PonyMath::Utility::Resolution<unsigned int>(rect.right - rect.left, rect.bottom - rect.top);

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window of class '0x{:X}'. Style: '0x{:X}'; Extended style: '0x{:X}'; Title: '{}'; Position: '{}'; Resolution: '{}'; HInstance: '0x{:X}'.",
			className, style.style, style.extendedStyle, PonyBase::Utility::ConvertToString(mainTitle), position.ToString(), resolution.ToString(), reinterpret_cast<std::uintptr_t>(hInstance));

		const HWND windowHandle = CreateWindowExW(
			style.extendedStyle,
			reinterpret_cast<LPCWSTR>(className),
			mainTitle.c_str(),
			style.style,
			position.X(), position.Y(),
			resolution.Width(), resolution.Height(),
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
		try
		{
			RegisterWindowProc(windowHandle, this);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(engine->Logger(), e, "On registering window proc.");
			DestroyWindow(windowHandle);

			throw;
		}
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Window proc registered.");

		return windowHandle;
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::GetTargetPosition() const noexcept
	{
		return windowRect.fullscreen
			? PonyMath::Core::Vector2<int>(0, 0)
			: windowRect.position;
	}

	PonyMath::Utility::Resolution<unsigned int> WindowsWindowSystem::GetTargetResolution() const noexcept
	{
		if (!windowRect.fullscreen)
		{
			return windowRect.resolution;
		}

		const auto screenSystem = engine->SystemManager().FindSystem<Screen::IScreenSystem>();
		if (!screenSystem)
		{
			throw std::runtime_error("Failed to find screen system.");
		}

		return screenSystem->DisplayResolution();
	}
}
