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

import <array>;
import <cstdint>;
import <memory>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Shape;
import PonyMath.Utility;

import PonyEngine.Core;
import PonyEngine.Screen;
import PonyEngine.Window.Windows;

import :IWindowsWindowSystemContext;
import :WindowsCursor;
import :WindowsMessagePump;
import :WindowsRawInputManager;
import :WindowsUtility;
import :WindowsWindowTitleBar;

export namespace PonyEngine::Window
{
	/// @brief Windows window system.
	class WindowsWindowSystem final : public Core::TickableSystem, public IWindowsWindowSystem, private IWindowsWindowSystemContext, private IWindowsMessageObserver
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

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual IWindowsWindowTitleBar& TitleBar() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IWindowsWindowTitleBar& TitleBar() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IWindowsCursor& Cursor() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IWindowsCursor& Cursor() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void ShowWindow() noexcept override;
		virtual void HideWindow() noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<std::int32_t> WindowRect() const override;
		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<std::int32_t> WindowClientRect() const override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> ClientToScreen(const PonyMath::Core::Vector2<std::int32_t>& clientPoint) const override;
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> ScreenToClient(const PonyMath::Core::Vector2<std::int32_t>& screenPoint) const override;

		[[nodiscard("Pure function")]]
		virtual IWindowsMessagePump& MessagePump() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IWindowsMessagePump& MessagePump() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IWindowsRawInputManager& RawInputManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IWindowsRawInputManager& RawInputManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual RECT WindowRectWindows() const override;
		[[nodiscard("Pure function")]]
		virtual RECT WindowClientRectWindows() const override;

		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept override;

		WindowsWindowSystem& operator =(const WindowsWindowSystem&) = delete;
		WindowsWindowSystem& operator =(WindowsWindowSystem&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept override;

		/// @brief Responds to a destroy message.
		void Destroy() const noexcept;

		/// @brief Gets a target window position.
		/// @param rect Window rect.
		/// @return Target window position.
		[[nodiscard("Pure function")]]
		static PonyMath::Core::Vector2<int> GetTargetPosition(const Window::WindowRect& rect) noexcept;
		/// @brief Gets a target window resolution.
		/// @param rect Window rect.
		/// @return Target window resolution.
		[[nodiscard("Pure function")]]
		PonyMath::Core::Vector2<int> GetTargetResolution(const Window::WindowRect& rect) const;
		/// @brief Gets a Windows window rect.
		/// @param style Window style.
		/// @param rect Window rect settings.
		/// @return Windows window rect.
		[[nodiscard("Pure function")]]
		RECT GetWindowRect(const WindowsWindowStyle& style, const Window::WindowRect& rect) const;

		std::shared_ptr<WindowsClass> windowsClass; ///< Windows class.
		HWND hWnd; ///< Window handler.

		std::unique_ptr<WindowsWindowTitleBar> titleBar; ///< Windows window title bar.
		std::unique_ptr<WindowsMessagePump> messagePump; ///< Windows message pump.
		std::unique_ptr<WindowsRawInputManager> rawInputManager; ///< Windows raw input manager.
		std::unique_ptr<WindowsCursor> cursor; ///< Windows cursor.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystem::WindowsWindowSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsWindowSystemParams& windowParams) :
		TickableSystem(engine, systemParams),
		windowsClass(windowParams.windowsClass)
	{
		assert(windowsClass && "The windows class is nullptr.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create message pump.");
		messagePump = std::make_unique<WindowsMessagePump>(*static_cast<IWindowsWindowSystemContext*>(this));
		messagePump->AddMessageObserver(*this, std::array<UINT, 1>{ WM_DESTROY });
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Message pump created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(messagePump.get()));

		const auto [position, resolution] = ConvertToPositionResolution(GetWindowRect(windowParams.windowsWindowStyle, windowParams.rect));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create window of class '0x{:X}'. Style: '0x{:X}'; Extended style: '0x{:X}'; Title: '{}'; Position: '{}'; Resolution: '{}'; HInstance: '0x{:X}'.",
			windowsClass->Class(), windowParams.windowsWindowStyle.style, windowParams.windowsWindowStyle.extendedStyle, windowParams.title, position.ToString(), resolution.ToString(), reinterpret_cast<std::uintptr_t>(windowsClass->Instance()));
		hWnd = CreateWindowExW(
			windowParams.windowsWindowStyle.extendedStyle,
			reinterpret_cast<LPCWSTR>(windowsClass->Class()),
			PonyBase::Utility::ConvertToWideString(windowParams.title).c_str(),
			windowParams.windowsWindowStyle.style,
			position.X(), position.Y(),
			resolution.X(), resolution.Y(),
			nullptr,
			nullptr,
			windowsClass->Instance(),
			static_cast<IWindowsMessageHandler*>(messagePump.get())
		);
		if (!hWnd)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Window created. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create window title bar.");
		titleBar = std::make_unique<WindowsWindowTitleBar>(*static_cast<IWindowsWindowSystemContext*>(this), windowParams.title);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Window title bar created at '0x{:X}.", reinterpret_cast<std::uintptr_t>(titleBar.get()));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create raw input manager.");
		rawInputManager = std::make_unique<WindowsRawInputManager>(*static_cast<IWindowsWindowSystemContext*>(this));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Raw input manager created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(rawInputManager.get()));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create cursor.");
		cursor = std::make_unique<WindowsCursor>(*static_cast<IWindowsWindowSystemContext*>(this), windowParams.cursorParams);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Cursor created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(cursor.get()));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Show window with command '{}'.", windowParams.cmdShow);
		::ShowWindow(hWnd, windowParams.cmdShow);
	}

	WindowsWindowSystem::~WindowsWindowSystem() noexcept
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy window. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			if (!DestroyWindow(hWnd)) [[unlikely]]
			{
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Error, "Error on destroying window. Error code: '0x{:X}'.", GetLastError());
			}
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Window destroyed.");
		}
		else
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Skip destroying window 'cause it's already been destroyed.");
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy cursor.");
		cursor.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Cursor destroyed.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy raw input manager.");
		rawInputManager.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Raw input manager destroyed.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy message pump.");
		try
		{
			messagePump->RemoveMessageObserver(*this);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(Engine().Logger(), e, "On removing message observer.");
		}
		messagePump.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Message pump destroyed.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy window title bar.");
		titleBar.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Window title bar destroyed.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Release Windows class.");
		windowsClass.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Windows class released.");
	}

	void WindowsWindowSystem::Begin() noexcept
	{
	}

	void WindowsWindowSystem::End() noexcept
	{
	}

	void WindowsWindowSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Pump messages.");
		messagePump->Pump();
	}

	IWindowsWindowTitleBar& WindowsWindowSystem::TitleBar() noexcept
	{
		return *titleBar;
	}

	const IWindowsWindowTitleBar& WindowsWindowSystem::TitleBar() const noexcept
	{
		return *titleBar;
	}

	IWindowsCursor& WindowsWindowSystem::Cursor() noexcept
	{
		return *cursor;
	}

	const IWindowsCursor& WindowsWindowSystem::Cursor() const noexcept
	{
		return *cursor;
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

	PonyMath::Shape::Rect<std::int32_t> WindowsWindowSystem::WindowRect() const
	{
		return ConvertToRect(WindowRectWindows());
	}

	PonyMath::Shape::Rect<std::int32_t> WindowsWindowSystem::WindowClientRect() const
	{
		return ConvertToRect(WindowClientRectWindows());
	}

	PonyMath::Core::Vector2<std::int32_t> WindowsWindowSystem::ClientToScreen(const PonyMath::Core::Vector2<std::int32_t>& clientPoint) const
	{
		auto screenPoint = POINT{.x = static_cast<LONG>(clientPoint.X()), .y = static_cast<LONG>(clientPoint.Y())};
		if (!::ClientToScreen(hWnd, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		return PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(screenPoint.x), static_cast<std::int32_t>(screenPoint.y));
	}

	PonyMath::Core::Vector2<std::int32_t> WindowsWindowSystem::ScreenToClient(const PonyMath::Core::Vector2<std::int32_t>& screenPoint) const
	{
		auto clientPoint = POINT{.x = static_cast<LONG>(screenPoint.X()), .y = static_cast<LONG>(screenPoint.Y())};
		if (!::ScreenToClient(hWnd, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get client point. Error code: '0x{:X}'.", GetLastError()));
		}

		return PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(clientPoint.x), static_cast<std::int32_t>(clientPoint.y));
	}

	IWindowsMessagePump& WindowsWindowSystem::MessagePump() noexcept
	{
		return *messagePump;
	}

	const IWindowsMessagePump& WindowsWindowSystem::MessagePump() const noexcept
	{
		return *messagePump;
	}

	IWindowsRawInputManager& WindowsWindowSystem::RawInputManager() noexcept
	{
		return *rawInputManager;
	}

	const IWindowsRawInputManager& WindowsWindowSystem::RawInputManager() const noexcept
	{
		return *rawInputManager;
	}

	RECT WindowsWindowSystem::WindowRectWindows() const
	{
		RECT rect;
		if (!::GetWindowRect(hWnd, &rect)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		return rect;
	}

	RECT WindowsWindowSystem::WindowClientRectWindows() const
	{
		RECT rect;
		if (!GetClientRect(hWnd, &rect)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get client rect. Error code: '0x{:X}'.", GetLastError()));
		}

		auto leftTop = POINT{ .x = rect.left, .y = rect.top };
		auto rightBottom = POINT{ .x = rect.right, .y = rect.bottom };
		if (!::ClientToScreen(hWnd, &leftTop) || !::ClientToScreen(hWnd, &rightBottom)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		rect.left = leftTop.x;
		rect.top = leftTop.y;
		rect.right = rightBottom.x;
		rect.bottom = rightBottom.y;

		return rect;
	}

	HWND WindowsWindowSystem::WindowHandle() const noexcept
	{
		return hWnd;
	}

	PonyDebug::Log::ILogger& WindowsWindowSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& WindowsWindowSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	void WindowsWindowSystem::Observe(const UINT uMsg, const WPARAM, const LPARAM) noexcept
	{
		assert(uMsg == WM_DESTROY && "The incorrect window message has been received.");

		Destroy();
	}

	void WindowsWindowSystem::Destroy() const noexcept
	{
		Engine().Stop();
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::GetTargetPosition(const Window::WindowRect& rect) noexcept
	{
		return rect.fullscreen
			? PonyMath::Core::Vector2<int>(0, 0)
			: rect.position;
	}

	PonyMath::Core::Vector2<int> WindowsWindowSystem::GetTargetResolution(const Window::WindowRect& rect) const
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

	RECT WindowsWindowSystem::GetWindowRect(const WindowsWindowStyle& style, const Window::WindowRect& rect) const
	{
		PonyMath::Core::Vector2<int> position = GetTargetPosition(rect);
		PonyMath::Core::Vector2<int> resolution = GetTargetResolution(rect);
		RECT windowRect = ConvertToWindowsRect(PonyMath::Shape::Rect<int>(position, resolution));
		if (!AdjustWindowRectEx(&windowRect, style.style, false, style.extendedStyle))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		return windowRect;
	}
}
