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

import PonyBase.Math;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;
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
		/// @param engine Engine.
		/// @param hInstance Instance.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystem(Core::IEngine& engine, HINSTANCE hInstance, ATOM className, const WindowsWindowParams& windowParams);
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

		/// @brief Creates a window.
		/// @param hInstance Instance.
		/// @param className Class name.
		/// @param windowParams Window parameters.
		/// @return Created window.
		[[nodiscard("Pure function")]]
		HWND CreateControlledWindow(HINSTANCE hInstance, ATOM className, const WindowsWindowParams& windowParams);

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
		mainTitle(windowParams.title),
		engine{&engine},
		hWnd{CreateControlledWindow(hInstance, className, windowParams)}
	{
		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Debug, "Show window with command '{}'.", windowParams.cmdShow);
		::ShowWindow(hWnd, windowParams.cmdShow);
	}

	WindowsWindowSystem::~WindowsWindowSystem() noexcept
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Destroy Windows window. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			if (!DestroyWindow(hWnd))
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

	void WindowsWindowSystem::Begin()
	{
	}

	void WindowsWindowSystem::End()
	{
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
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Show window.");
	}

	void WindowsWindowSystem::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Hide window.");
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
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Couldn't set new window title. Error code: '0x{:X}'.", GetLastError()));
		}

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Window title set to {}.", PonyBase::Utility::ConvertToString(titleToSet));
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

	HWND WindowsWindowSystem::CreateControlledWindow(const HINSTANCE hInstance, const ATOM className, const WindowsWindowParams& windowParams)
	{
		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window of class '0x{:X}'. Style: '0x{:X}'; Extended style: '0x{:X}'; Title: '{}'; Position: '{}'; Size: '{}'; HInstance: '0x{:X}'.",
			className, windowParams.style, windowParams.extendedStyle, PonyBase::Utility::ConvertToString(windowParams.title), windowParams.position.ToString(), windowParams.size.ToString(), reinterpret_cast<std::uintptr_t>(hInstance));

		auto rect = RECT{.left = windowParams.position.X(), .top = windowParams.position.Y(), .right = windowParams.position.X() + windowParams.size.X(), .bottom = windowParams.position.Y() + windowParams.size.Y()};
		if (!AdjustWindowRectEx(&rect, windowParams.style, false, windowParams.extendedStyle))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}
		const auto position = PonyBase::Math::Vector2<int>(rect.left, rect.top);
		const auto size = PonyBase::Math::Vector2<int>(rect.right - rect.left, rect.bottom - rect.top);
		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Debug, "Actual window position: '{}'. Actual window size: '{}'", position.ToString(), size.ToString());

		const HWND windowHandle = CreateWindowExW(
			windowParams.extendedStyle,
			reinterpret_cast<LPCWSTR>(className),
			mainTitle.c_str(),
			windowParams.style,
			position.X(), position.Y(),
			size.X(), size.Y(),
			nullptr,
			nullptr,
			hInstance,
			static_cast<IWindowProc*>(this)
		);
		if (!windowHandle)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Windows hasn't created window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Windows window created. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));

		return windowHandle;
	}
}
