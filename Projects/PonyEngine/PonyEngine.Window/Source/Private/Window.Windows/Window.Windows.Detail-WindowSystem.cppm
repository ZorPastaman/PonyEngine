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

export module PonyEngine.Window.Windows.Detail:WindowSystem;

import <array>;
import <cstdint>;
import <memory>;
import <stdexcept>;

import PonyBase.Utility.Windows;

import PonyMath.Core;
import PonyMath.Shape;
import PonyMath.Utility;

import PonyEngine.Core;
import PonyEngine.Screen;
import PonyEngine.Window.Windows;

import :Cursor;
import :IWindowSystemContext;
import :MessagePump;
import :RawInputManager;
import :Utility;
import :TitleBar;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows window system.
	class WindowSystem final : public Core::TickableSystem, public IWindowSystem, private IWindowSystemContext, private IMessageObserver
	{
	public:
		/// @brief Creates a @p WindowSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param windowParams Windows window system parameters.
		[[nodiscard("Pure constructor")]]
		WindowSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowSystemParams& windowParams);
		WindowSystem(const WindowSystem&) = delete;
		WindowSystem(WindowSystem&&) = delete;

		virtual ~WindowSystem() noexcept override;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual ITitleBar& TitleBar() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ITitleBar& TitleBar() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ICursor& Cursor() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ICursor& Cursor() const noexcept override;

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
		virtual IMessagePump& MessagePump() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IMessagePump& MessagePump() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRawInputManager& RawInputManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRawInputManager& RawInputManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND WindowHandle() const noexcept override;

		WindowSystem& operator =(const WindowSystem&) = delete;
		WindowSystem& operator =(WindowSystem&&) = delete;

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
		RECT GetWindowRect(const WindowStyle& style, const Window::WindowRect& rect) const;

		std::shared_ptr<Class> windowsClass; ///< Windows class.
		HMODULE moduleHandle; ///< Window module.
		HWND hWnd; ///< Window handler.

		std::unique_ptr<class TitleBar> titleBar; ///< Windows window title bar.
		std::unique_ptr<class MessagePump> messagePump; ///< Windows message pump.
		std::unique_ptr<class RawInputManager> rawInputManager; ///< Windows raw input manager.
		std::unique_ptr<class Cursor> cursor; ///< Windows cursor.
	};
}

namespace PonyEngine::Window::Windows
{
	WindowSystem::WindowSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowSystemParams& windowParams) :
		TickableSystem(engine, systemParams),
		windowsClass(windowParams.windowsClass),
		moduleHandle{ PonyBase::Utility::Windows::GetModule()}
	{
		assert(windowsClass && "The windows class is nullptr.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create message pump.");
		messagePump = std::make_unique<class MessagePump>(*static_cast<IWindowSystemContext*>(this));
		messagePump->AddMessageObserver(*this, std::array<UINT, 1>{ WM_DESTROY });
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Message pump created.");

		const auto [position, resolution] = ConvertToPositionResolution(GetWindowRect(windowParams.windowsWindowStyle, windowParams.rect));
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create window of class '0x{:X}'. Style: '0x{:X}'; Extended style: '0x{:X}'; Title: '{}'; Position: '{}'; Resolution: '{}'; HInstance: '0x{:X}'.",
			windowsClass->ClassHandle(), windowParams.windowsWindowStyle.style, windowParams.windowsWindowStyle.extendedStyle, windowParams.title, position.ToString(), resolution.ToString(), reinterpret_cast<std::uintptr_t>(moduleHandle));
		hWnd = CreateWindowExW(
			windowParams.windowsWindowStyle.extendedStyle,
			reinterpret_cast<LPCWSTR>(windowsClass->ClassHandle()),
			PonyBase::Utility::ConvertToWideString(windowParams.title).c_str(),
			windowParams.windowsWindowStyle.style,
			position.X(), position.Y(),
			resolution.X(), resolution.Y(),
			nullptr,
			nullptr,
			moduleHandle,
			static_cast<IMessageHandler*>(messagePump.get())
		);
		if (!hWnd)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Window created. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create window title bar.");
		titleBar = std::make_unique<class TitleBar>(*static_cast<IWindowSystemContext*>(this), windowParams.title);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Window title bar created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create raw input manager.");
		rawInputManager = std::make_unique<class RawInputManager>(*static_cast<IWindowSystemContext*>(this));
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Raw input manager created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(rawInputManager.get()));

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create cursor.");
		cursor = std::make_unique<class Cursor>(*static_cast<IWindowSystemContext*>(this), windowParams.cursorParams);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Cursor created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Show window with command '{}'.", windowParams.cmdShow);
		::ShowWindow(hWnd, windowParams.cmdShow);
	}

	WindowSystem::~WindowSystem() noexcept
	{
		if (IsWindow(hWnd))
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy window. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			if (!DestroyWindow(hWnd)) [[unlikely]]
			{
				PONY_LOG(Logger(), PonyDebug::Log::LogType::Error, "Error on destroying window. Error code: '0x{:X}'.", GetLastError());
			}
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Window destroyed.");
		}
		else
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Skip destroying window 'cause it's already been destroyed.");
		}

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy cursor.");
		cursor.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Cursor destroyed.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy raw input manager.");
		rawInputManager.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Raw input manager destroyed.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy message pump.");
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

	void WindowSystem::Begin() noexcept
	{
	}

	void WindowSystem::End() noexcept
	{
	}

	void WindowSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Pump messages.");
		messagePump->Pump();
	}

	ITitleBar& WindowSystem::TitleBar() noexcept
	{
		return *titleBar;
	}

	const ITitleBar& WindowSystem::TitleBar() const noexcept
	{
		return *titleBar;
	}

	ICursor& WindowSystem::Cursor() noexcept
	{
		return *cursor;
	}

	const ICursor& WindowSystem::Cursor() const noexcept
	{
		return *cursor;
	}

	bool WindowSystem::IsVisible() const noexcept
	{
		return IsWindowVisible(hWnd);
	}

	void WindowSystem::ShowWindow() noexcept
	{
		::ShowWindow(hWnd, SW_SHOW);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Show window.");
	}

	void WindowSystem::HideWindow() noexcept
	{
		::ShowWindow(hWnd, SW_HIDE);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Hide window.");
	}

	PonyMath::Shape::Rect<std::int32_t> WindowSystem::WindowRect() const
	{
		RECT rect;
		if (!::GetWindowRect(hWnd, &rect)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		return ConvertToRect(rect);
	}

	PonyMath::Shape::Rect<std::int32_t> WindowSystem::WindowClientRect() const
	{
		RECT rect;
		if (!GetClientRect(hWnd, &rect)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get client rect. Error code: '0x{:X}'.", GetLastError()));
		}

		auto leftTop = POINT{.x = rect.left, .y = rect.top};
		auto rightBottom = POINT{.x = rect.right, .y = rect.bottom};
		if (!::ClientToScreen(hWnd, &leftTop) || !::ClientToScreen(hWnd, &rightBottom)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		rect.left = leftTop.x;
		rect.top = leftTop.y;
		rect.right = rightBottom.x;
		rect.bottom = rightBottom.y;

		return ConvertToRect(rect);
	}

	PonyMath::Core::Vector2<std::int32_t> WindowSystem::ClientToScreen(const PonyMath::Core::Vector2<std::int32_t>& clientPoint) const
	{
		auto screenPoint = POINT{.x = static_cast<LONG>(clientPoint.X()), .y = static_cast<LONG>(clientPoint.Y())};
		if (!::ClientToScreen(hWnd, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		return PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(screenPoint.x), static_cast<std::int32_t>(screenPoint.y));
	}

	PonyMath::Core::Vector2<std::int32_t> WindowSystem::ScreenToClient(const PonyMath::Core::Vector2<std::int32_t>& screenPoint) const
	{
		auto clientPoint = POINT{.x = static_cast<LONG>(screenPoint.X()), .y = static_cast<LONG>(screenPoint.Y())};
		if (!::ScreenToClient(hWnd, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get client point. Error code: '0x{:X}'.", GetLastError()));
		}

		return PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(clientPoint.x), static_cast<std::int32_t>(clientPoint.y));
	}

	IMessagePump& WindowSystem::MessagePump() noexcept
	{
		return *messagePump;
	}

	const IMessagePump& WindowSystem::MessagePump() const noexcept
	{
		return *messagePump;
	}

	IRawInputManager& WindowSystem::RawInputManager() noexcept
	{
		return *rawInputManager;
	}

	const IRawInputManager& WindowSystem::RawInputManager() const noexcept
	{
		return *rawInputManager;
	}

	HWND WindowSystem::WindowHandle() const noexcept
	{
		return hWnd;
	}

	PonyDebug::Log::ILogger& WindowSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& WindowSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	void WindowSystem::Observe(const UINT uMsg, const WPARAM, const LPARAM) noexcept
	{
		assert(uMsg == WM_DESTROY && "The incorrect window message has been received.");

		Destroy();
	}

	void WindowSystem::Destroy() const noexcept
	{
		Engine().Stop();
	}

	PonyMath::Core::Vector2<int> WindowSystem::GetTargetPosition(const Window::WindowRect& rect) noexcept
	{
		return rect.fullscreen
			? PonyMath::Core::Vector2<int>(0, 0)
			: rect.position;
	}

	PonyMath::Core::Vector2<int> WindowSystem::GetTargetResolution(const Window::WindowRect& rect) const
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

	RECT WindowSystem::GetWindowRect(const WindowStyle& style, const Window::WindowRect& rect) const
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
