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

export module PonyEngine.Window.Windows.Detail:WindowsWindowSystem;

import <algorithm>;
import <cstdint>;
import <exception>;
import <format>;
import <memory>;
import <ranges>;
import <span>;
import <stdexcept>;
import <string>;
import <string_view>;
import <typeinfo>;
import <utility>;
import <unordered_map>;
import <vector>;

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Screen;

import PonyEngine.Window.Windows;

import :IWindowProc;
import :Utility;
import :WindowProc;

export namespace PonyEngine::Window
{
	/// @brief Windows window system.
	class WindowsWindowSystem final : public Core::TickableSystem, public IWindowsWindowSystem, public IWindowProc
	{
	public:
		/// @brief Creates a @p WindowsWindowSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param windowParams Windows window system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsWindowSystemParams& windowParams);
		WindowsWindowSystem(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem(WindowsWindowSystem&&) = delete;

		virtual ~WindowsWindowSystem() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual std::string_view MainTitle() const noexcept override;
		virtual void MainTitle(std::string_view title) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SecondaryTitle() const noexcept override;
		virtual void SecondaryTitle(std::string_view title) override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void ShowWindow() noexcept override;
		virtual void HideWindow() noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> Position() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept override;

		virtual void AddMessageObserver(IWindowsMessageObserver& observer, std::span<const UINT> messageTypes) override;
		virtual void RemoveMessageObserver(IWindowsMessageObserver& observer) noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindowSystem& operator =(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem& operator =(WindowsWindowSystem&&) = delete;

	private:
		/// @brief Update the window title.
		void UpdateWindowTitle() const;

		/// @brief Responds to a destroy message.
		void Destroy() const noexcept;

		/// @brief Gets a target window position.
		/// @param rect Window rect.
		/// @return Target window position.
		[[nodiscard("Pure function")]]
		static PonyMath::Core::Vector2<int> GetTargetPosition(const WindowRect& rect) noexcept;
		/// @brief Gets a target window resolution.
		/// @param rect Window rect.
		/// @return Target window resolution.
		[[nodiscard("Pure function")]]
		PonyMath::Core::Vector2<int> GetTargetResolution(const WindowRect& rect) const;
		/// @brief Gets a Windows window rect.
		/// @param style Window style.
		/// @param rect Window rect settings.
		/// @return Windows window rect.
		[[nodiscard("Pure function")]]
		RECT GetWindowRect(const WindowsWindowStyle& style, const WindowRect& rect) const;

		std::string mainTitle; ///< Window main title cache.
		std::string secondaryTitle; ///< Window title text cache.

		std::shared_ptr<WindowsClass> windowsClass; ///< Windows class.
		HWND hWnd; ///< Window handler.

		std::unordered_map<UINT, std::vector<IWindowsMessageObserver*>> observers; ///< Message observers.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystem::WindowsWindowSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsWindowSystemParams& windowParams) :
		TickableSystem(engine, systemParams),
		mainTitle(windowParams.title),
		windowsClass(windowParams.windowsClass)
	{
		assert(windowsClass && "The windows class is nullptr.");

		const auto [position, resolution] = PositionResolution(GetWindowRect(windowParams.windowsWindowStyle, windowParams.rect));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Windows window of class '0x{:X}'. Style: '0x{:X}'; Extended style: '0x{:X}'; Title: '{}'; Position: '{}'; Resolution: '{}'; HInstance: '0x{:X}'.",
			windowsClass->Class(), windowParams.windowsWindowStyle.style, windowParams.windowsWindowStyle.extendedStyle, mainTitle, position.ToString(), resolution.ToString(), reinterpret_cast<std::uintptr_t>(windowsClass->Instance()));
		hWnd = CreateWindowExW(
			windowParams.windowsWindowStyle.extendedStyle,
			reinterpret_cast<LPCWSTR>(windowsClass->Class()),
			PonyBase::Utility::ConvertToWideString(mainTitle).c_str(),
			windowParams.windowsWindowStyle.style,
			position.X(), position.Y(),
			resolution.X(), resolution.Y(),
			nullptr,
			nullptr,
			windowsClass->Instance(),
			static_cast<IWindowProc*>(this)
		);
		if (!hWnd)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Windows window created. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Show window with command '{}'.", windowParams.cmdShow);
		::ShowWindow(hWnd, windowParams.cmdShow);
	}

	WindowsWindowSystem::~WindowsWindowSystem() noexcept
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Windows window. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			if (!DestroyWindow(hWnd)) [[unlikely]]
			{
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Error, "Error on destroying Windows window. Error code: '0x{:X}'.", GetLastError());
			}
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Windows window destroyed.");
		}
		else
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Skip destroying Windows window 'cause it's already been destroyed.");
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Release Windows class.");
		windowsClass.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Windows class released.");
	}

	void WindowsWindowSystem::Begin()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Register window proc. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		RegisterWindowProc(hWnd, this);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Window proc registered.");
	}

	void WindowsWindowSystem::End()
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Unregister window proc. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			UnregisterWindowProc(hWnd);
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Window proc unregistered.");
		}
	}

	void WindowsWindowSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Dispatch messages.");

		MSG message;
		while (PeekMessageW(&message, hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}

	std::string_view WindowsWindowSystem::MainTitle() const noexcept
	{
		return mainTitle;
	}

	void WindowsWindowSystem::MainTitle(const std::string_view title)
	{
		mainTitle = title;
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Main title set to '{}'.", mainTitle);
		UpdateWindowTitle();
	}

	std::string_view WindowsWindowSystem::SecondaryTitle() const noexcept
	{
		return secondaryTitle;
	}

	void WindowsWindowSystem::SecondaryTitle(const std::string_view title)
	{
		secondaryTitle = title;
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Secondary title set to '{}'.", secondaryTitle);
		UpdateWindowTitle();
	}

	bool WindowsWindowSystem::IsVisible() const noexcept
	{
		return IsWindowVisible(hWnd);
	}

	void WindowsWindowSystem::ShowWindow() noexcept
	{
		::ShowWindow(hWnd, SW_SHOW);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Show window.");
	}

	void WindowsWindowSystem::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Hide window.");
	}

	PonyMath::Core::Vector2<std::int32_t> WindowsWindowSystem::Position() const noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(rect.left), static_cast<std::int32_t>(rect.right));
	}

	PonyMath::Utility::Resolution<std::uint32_t> WindowsWindowSystem::Resolution() const noexcept
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return PonyMath::Utility::Resolution<std::uint32_t>(static_cast<std::uint32_t>(rect.right - rect.left), static_cast<std::uint32_t>(rect.bottom - rect.top));
	}

	HWND WindowsWindowSystem::WindowHandle() const noexcept
	{
		return hWnd;
	}

	void WindowsWindowSystem::AddMessageObserver(IWindowsMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		for (const auto messageType : messageTypes)
		{
			std::vector<IWindowsMessageObserver*>& observerArray = observers[messageType];
			assert(std::ranges::find(observerArray, &observer) == observerArray.cend() && "The window message observer has already been added.");
			observerArray.push_back(&observer);
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "'{}' window message observer added.", typeid(observer).name());
	}

	void WindowsWindowSystem::RemoveMessageObserver(IWindowsMessageObserver& observer) noexcept
	{
		for (std::vector<IWindowsMessageObserver*>& observerArray : std::ranges::views::values(observers))
		{
			if (const auto position = std::ranges::find(observerArray, &observer); position != observerArray.cend())
			{
				observerArray.erase(position);
			}
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "'{}' window message observer removed.", typeid(observer).name());
	}

	LRESULT WindowsWindowSystem::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Received '{}' command.", uMsg);

		switch (uMsg)
		{
		case WM_CREATE:
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Received create command.");
			break;
		case WM_DESTROY:
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Received destroy command.");
			Destroy();
			break;
		default:
			break;
		}

		if (const auto position = observers.find(uMsg); position != observers.cend())
		{
			for (IWindowsMessageObserver* const observer : position->second)
			{
				observer->Observe(uMsg, wParam, lParam);
			}
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindowSystem::UpdateWindowTitle() const
	{
		const std::string titleToSet = secondaryTitle.length() > 0 ? std::format("{} - {}", mainTitle, secondaryTitle) : mainTitle;

		if (!SetWindowTextW(hWnd, PonyBase::Utility::ConvertToWideString(titleToSet).c_str()))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set new window title. Error code: '0x{:X}'.", GetLastError()));
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Window title set to '{}'.", titleToSet);
	}

	void WindowsWindowSystem::Destroy() const noexcept
	{
		Engine().Stop();
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::GetTargetPosition(const WindowRect& rect) noexcept
	{
		return rect.fullscreen
			? PonyMath::Core::Vector2<int>(0, 0)
			: rect.position;
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::GetTargetResolution(const WindowRect& rect) const
	{
		if (!rect.fullscreen)
		{
			return static_cast<PonyMath::Core::Vector2<int>>(rect.resolution.Vector());
		}

		const auto screenSystem = Engine().SystemManager().FindSystem<Screen::IScreenSystem>();
		if (!screenSystem)
		{
			throw std::runtime_error("Failed to find screen system.");
		}

		return static_cast<PonyMath::Core::Vector2<int>>(screenSystem->DisplayResolution().Vector());
	}

	RECT WindowsWindowSystem::GetWindowRect(const WindowsWindowStyle& style, const WindowRect& rect) const
	{
		PonyMath::Core::Vector2<int> position = GetTargetPosition(rect);
		PonyMath::Core::Vector2<int> resolution = GetTargetResolution(rect);
		auto windowRect = RECT
		{
			.left = static_cast<LONG>(position.X()),
			.top = static_cast<LONG>(position.Y()),
			.right = static_cast<LONG>(position.X() + resolution.X()),
			.bottom = static_cast<LONG>(position.Y() + resolution.Y())
		};
		if (!AdjustWindowRectEx(&windowRect, style.style, false, style.extendedStyle))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		return windowRect;
	}
}
