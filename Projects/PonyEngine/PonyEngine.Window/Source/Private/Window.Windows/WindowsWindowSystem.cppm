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
		virtual void AddRawInputObserver(IWindowsRawInputObserver& observer, std::span<const DWORD> rawInputTypes) override;
		virtual void RemoveRawInputObserver(IWindowsRawInputObserver& observer) noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindowSystem& operator =(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem& operator =(WindowsWindowSystem&&) = delete;

	private:
		/// @brief Update the window title.
		void UpdateWindowTitle() const;

		/// @brief Registers the raw input type.
		/// @param rawInputType Raw input type to register. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		void RegisterRawInputType(DWORD rawInputType);
		/// @brief Unregisters the raw input type.
		/// @param rawInputType Raw input type to unregister. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		void UnregisterRawInputType(DWORD rawInputType);
		/// @brief Registers the raw input type.
		/// @param rawInputType Raw input type to register. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		/// @param flags Registation flags.
		/// @param windowHandle Window handle.
		void RegisterRawInputType(DWORD rawInputType, DWORD flags, HWND windowHandle);

		/// @brief Responds to a destroy message.
		void Destroy() const noexcept;

		/// @brief Calls message observers.
		/// @param uMsg Message type.
		/// @param wParam WParam.
		/// @param lParam LParam.
		void ObserveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) const noexcept;
		/// @brief Calls raw input observers.
		/// @param lParam LParam.
		void ObserveRawInput(LPARAM lParam) const noexcept;

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

		std::unordered_map<UINT, std::vector<IWindowsMessageObserver*>> messageObservers; ///< Message observers.
		std::unordered_map<DWORD, std::vector<IWindowsRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		mutable std::vector<BYTE> rawInput; ///< Raw input cache.
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
		for (const UINT messageType : messageTypes)
		{
			std::vector<IWindowsMessageObserver*>& observerArray = messageObservers[messageType];
			assert(std::ranges::find(observerArray, &observer) == observerArray.cend() && "The window message observer has already been added.");
			observerArray.push_back(&observer);
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "'{}' window message observer added.", typeid(observer).name());
	}

	void WindowsWindowSystem::RemoveMessageObserver(IWindowsMessageObserver& observer) noexcept
	{
		for (std::vector<IWindowsMessageObserver*>& observerArray : std::ranges::views::values(messageObservers))
		{
			if (const auto position = std::ranges::find(observerArray, &observer); position != observerArray.cend())
			{
				observerArray.erase(position);
			}
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "'{}' window message observer removed.", typeid(observer).name());
	}

	void WindowsWindowSystem::AddRawInputObserver(IWindowsRawInputObserver& observer, const std::span<const DWORD> rawInputTypes)
	{
		for (const DWORD rawInputType : rawInputTypes)
		{
			assert(rawInputType == RIM_TYPEMOUSE || rawInputType == RIM_TYPEMOUSE && "Incorrect raw input type: '{}'. But only RIM_TYPEMOUSE and RIM_TYPEMOUSE are supported.");

			if (const auto typePosition = rawInputObservers.find(rawInputType); typePosition == rawInputObservers.cend() || typePosition->second.empty())
			{
				RegisterRawInputType(rawInputType);
			}

			std::vector<IWindowsRawInputObserver*>& observers = rawInputObservers[rawInputType];
			assert(std::ranges::find(observers, &observer) == observers.cend() && "The raw input observer has already been added.");
			observers.push_back(&observer);
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "'{}' raw input observer added.", typeid(observer).name());
	}

	void WindowsWindowSystem::RemoveRawInputObserver(IWindowsRawInputObserver& observer) noexcept
	{
		for (auto& [inputType, observers] : rawInputObservers)
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);

				if (observers.empty())
				{
					try
					{
						UnregisterRawInputType(inputType);
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(Engine().Logger(), e, "On unregistering raw input type {}.", inputType);
					}
				}
			}
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "'{}' raw input observer removed.", typeid(observer).name());
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
		case WM_INPUT:
			ObserveRawInput(lParam);
			break;
		default:
			break;
		}

		ObserveMessage(uMsg, wParam, lParam);

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

	void WindowsWindowSystem::RegisterRawInputType(const DWORD rawInputType)
	{
		RegisterRawInputType(rawInputType, DWORD{0}, hWnd);
	}

	void WindowsWindowSystem::UnregisterRawInputType(const DWORD rawInputType)
	{
		RegisterRawInputType(rawInputType, RIDEV_REMOVE, nullptr);
	}

	void WindowsWindowSystem::RegisterRawInputType(const DWORD rawInputType, const DWORD flags, const HWND windowHandle)
	{
		auto rid = RAWINPUTDEVICE{.dwFlags = flags, .hwndTarget = windowHandle};

		switch (rawInputType)
		{
		case RIM_TYPEMOUSE:
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			break;
		case RIM_TYPEKEYBOARD:
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x06;
			break;
		default:
			return;
		}

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to register raw input device. Flags: '0x{:X}'. Error code: '0x{:X}'.", flags, GetLastError()));
		}
	}

	void WindowsWindowSystem::Destroy() const noexcept
	{
		Engine().Stop();
	}

	void WindowsWindowSystem::ObserveMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) const noexcept
	{
		if (const auto position = messageObservers.find(uMsg); position != messageObservers.cend())
		{
			for (IWindowsMessageObserver* const observer : position->second)
			{
				try
				{
					observer->Observe(uMsg, wParam, lParam);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(Engine().Logger(), e, "On calling '{}' Windows message observer.", typeid(*observer).name());
				}
			}
		}
	}

	void WindowsWindowSystem::ObserveRawInput(const LPARAM lParam) const noexcept
	{
		const auto hRawInput = reinterpret_cast<HRAWINPUT>(lParam);

		UINT size = 0u;
		if (GetRawInputData(hRawInput, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)))
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Error, "Failed to get raw input size. Error code: '0x{:X}'.", GetLastError());

			return;
		}
		if (size < 1u)
		{
			return;
		}

		rawInput.reserve(size);
		if (GetRawInputData(hRawInput, RID_INPUT, rawInput.data(), &size, sizeof(RAWINPUTHEADER)) != size)
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());

			return;
		}

		const auto input = reinterpret_cast<RAWINPUT*>(rawInput.data());
		if (const auto observerPosition = rawInputObservers.find(input->header.dwType); observerPosition != rawInputObservers.cend())
		{
			for (IWindowsRawInputObserver* const observer : observerPosition->second)
			{
				try
				{
					observer->Observe(*input);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(Engine().Logger(), e, "On calling '{}' Windows raw input observer.", typeid(*observer).name());
				}
			}
		}
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
