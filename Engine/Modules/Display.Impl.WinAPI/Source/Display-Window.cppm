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

#include "PonyEngine/Log/Log.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.Display.Impl.WinAPI:Window;

import std;

import PonyEngine.Application;
import PonyEngine.Display;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Utility;

import :DisplayContainer;
import :DisplayState;

export namespace PonyEngine::Display
{
	class Window final : public IWindow
	{
	public:
		static constexpr auto MinWindowSize = Math::Vector2<std::uint32_t>::Zero();
		static constexpr auto MaxWindowSize = Math::Vector2<std::uint32_t>(std::numeric_limits<int>::max());

		[[nodiscard("Pure constructor")]]
		Window(const Application::IApplication& application, const DisplayContainer& displayContainer, ATOM windowClass, HMODULE moduleHandle, const WindowParams& params);
		Window(const Window&) = delete;
		Window(Window&&) = delete;

		~Window() noexcept;

		[[nodiscard("Pure function")]]
		static WNDCLASSEXA MakeWindowClassDesc(HMODULE moduleHandle) noexcept;

		Window& operator =(const Window&) = delete;
		Window& operator =(Window&&) = delete;

	private:
		struct FullscreenPositionSizeMode final
		{
		};
		struct WindowedPositionSizeMode final
		{
			std::optional<Math::Vector2<int>> minSize;
			std::optional<Math::Vector2<int>> maxSize;
			std::optional<float> aspect;
		};
		using PositionSizeMode = std::variant<FullscreenPositionSizeMode, WindowedPositionSizeMode>;

		[[nodiscard("Pure function")]]
		static PositionSizeMode CalculatePositionSizeMode(const WindowMode& mode);

		[[nodiscard("Pure function")]]
		Math::CornerRect<int> CalculateClientRect(const WindowMode& mode) const;
		[[nodiscard("Pure function")]]
		Math::CornerRect<int> CalculateClientRect(const FullscreenWindowMode& mode) const;
		[[nodiscard("Pure function")]]
		static Math::CornerRect<int> CalculateClientRect(const WindowedWindowMode& mode);
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> CalculateClientSize(const WindowedWindowMode& mode);

		[[nodiscard("Pure function")]]
		static Math::CornerRect<int> CalculateWindowRect(const Math::CornerRect<int>& clientRect, DWORD style, DWORD styleEx, UINT dpi);

		[[nodiscard("Pure function")]]
		static Math::CornerRect<int> ToCornerRect(const RECT& rect) noexcept;
		[[nodiscard("Pure function")]]
		static RECT ToRect(const Math::CornerRect<int>& rect) noexcept;

		[[nodiscard("Pure function")]]
		static std::pair<DWORD, DWORD> CalculateStyle(const WindowMode& mode) noexcept;
		[[nodiscard("Pure function")]]
		static std::pair<DWORD, DWORD> CalculateStyle(const FullscreenWindowMode& mode) noexcept;
		[[nodiscard("Pure function")]]
		static std::pair<DWORD, DWORD> CalculateStyle(const WindowedWindowMode& mode) noexcept;

		[[nodiscard("Pure function")]]
		Math::CornerRect<int> GetWindowRect() const;
		void SetWindowRect(const Math::CornerRect<int>& rect);

		[[nodiscard("Pure function")]]
		std::pair<DWORD, DWORD> GetWindowStyle() const;

		[[nodiscard("Must be returned to system")]]
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		[[nodiscard("Must be used")]]
		LRESULT ObserveCreate(WPARAM wParam, LPARAM lParam) noexcept;
		[[nodiscard("Must be used")]]
		LRESULT ObserveDestroy(WPARAM wParam, LPARAM lParam) noexcept;
		[[nodiscard("Must be used")]]
		LRESULT ObserveGetMinMaxInfo(WPARAM wParam, LPARAM lParam) noexcept;
		[[nodiscard("Must be used")]]
		LRESULT ObserveEraseBackground(WPARAM wParam, LPARAM lParam) noexcept;
		[[nodiscard("Must be used")]]
		LRESULT ObservePaint(WPARAM wParam, LPARAM lParam) noexcept;

		static constexpr DWORD ResizableByUserStyle = WS_THICKFRAME & WS_MAXIMIZEBOX;
		static constexpr DWORD FullscreenStyle = WS_POPUP;
		static constexpr DWORD FullscreenStyleEx = WS_EX_APPWINDOW;
		static constexpr DWORD WindowedStyle = WS_OVERLAPPEDWINDOW & ~ResizableByUserStyle;
		static constexpr DWORD WindowedStyleEx = WS_EX_APPWINDOW;

		const Application::IApplication* application;
		const Log::ILogService* logService;

		const DisplayContainer* displayContainer;

		HWND windowHandle;

		PositionSizeMode positionSizeMode;
		bool quitOnDestroy;
	};
}

namespace PonyEngine::Display
{
	Window::Window(const Application::IApplication& application, const DisplayContainer& displayContainer, const ATOM windowClass, const HMODULE moduleHandle,
		const WindowParams& params) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		displayContainer{&displayContainer},
		positionSizeMode(CalculatePositionSizeMode(params.mode)),
		quitOnDestroy{params.quitOnDestroy}
	{
		const Math::CornerRect<int> clientRect = CalculateClientRect(params.mode);
		const auto [style, styleEx] = CalculateStyle(params.mode);
		const std::string_view title = params.title ? *params.title : this->application->ProjectTitle();

		windowHandle = CreateWindowExA(styleEx, reinterpret_cast<LPCSTR>(windowClass), title.data(), style,
			clientRect.Position().X(), clientRect.Position().Y(), clientRect.Size().X(), clientRect.Size().Y(), nullptr, nullptr, moduleHandle, this);
		if (!windowHandle) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create window: Error code = '0x{:X}'", GetLastError()));
		}

		if (const UINT dpi = GetDpiForWindow(windowHandle)) [[likely]]
		{
			try
			{
				const Math::CornerRect<int> currentWindowRect = GetWindowRect();
				const Math::CornerRect<int> windowRect = CalculateWindowRect(currentWindowRect, style, styleEx, dpi);
				SetWindowRect(windowRect);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On adjusting window rect");
			}
		}
		else [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get window dpi.");
		}

		if (!params.hidden)
		{
			ShowWindow(windowHandle, SW_NORMAL);
		}
	}

	Window::~Window() noexcept
	{
		if (IsWindow(windowHandle))
		{
			if (!DestroyWindow(windowHandle)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to destroy window. Error code: '0x{:X}'.", GetLastError());
			}
		}
	}

	WNDCLASSEXA Window::MakeWindowClassDesc(const HMODULE moduleHandle) noexcept
	{
		return WNDCLASSEXA
		{
			.cbSize = sizeof(WNDCLASSEXA),
			.style = 0u,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = moduleHandle,
			.hIcon = nullptr,
			.hCursor = nullptr,
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = "PonyEngineWindow",
			.hIconSm = nullptr
		};
	}

	Window::PositionSizeMode Window::CalculatePositionSizeMode(const WindowMode& mode)
	{
		return std::visit<PositionSizeMode>(Utility::Overload
		{
			[](const FullscreenWindowMode& mode) noexcept
			{
				return FullscreenPositionSizeMode{};
			},
			[](const WindowedWindowMode& mode)
			{
				if (mode.minSize)
				{
					if (mode.minSize->X() > MaxWindowSize.X() || mode.minSize->Y() > MaxWindowSize.Y()) [[unlikely]]
					{
						throw std::invalid_argument("Invalid min size");
					}
				}
				if (mode.maxSize)
				{
					if (mode.maxSize->X() > MaxWindowSize.X() || mode.maxSize->Y() > MaxWindowSize.Y()) [[unlikely]]
					{
						throw std::invalid_argument("Invalid max size");
					}
				}
				if (mode.minSize && mode.maxSize)
				{
					if (mode.minSize->X() > mode.maxSize->X() || mode.minSize->Y() > mode.maxSize->Y()) [[unlikely]]
					{
						throw std::invalid_argument("Invalid min/max size");
					}
				}

				return WindowedPositionSizeMode
				{
					.minSize = mode.minSize ? static_cast<Math::Vector2<int>>(*mode.minSize) : std::optional<Math::Vector2<int>>(),
					.maxSize = mode.maxSize ? static_cast<Math::Vector2<int>>(*mode.maxSize) : std::optional<Math::Vector2<int>>(),
				};
			}
		}, mode);
	}

	Math::CornerRect<int> Window::CalculateClientRect(const WindowMode& mode) const
	{
		return std::visit(Utility::Overload
		{
			[this](const FullscreenWindowMode& mode) noexcept
			{
				return CalculateClientRect(mode);
			},
			[this](const WindowedWindowMode& mode) noexcept
			{
				return CalculateClientRect(mode);
			}
		}, mode);
	}

	Math::CornerRect<int> Window::CalculateClientRect(const FullscreenWindowMode& mode) const
	{
		if (mode.displays.empty()) [[unlikely]]
		{
			throw std::invalid_argument("No display set");
		}

		for (const DisplayHandle displayHandle : mode.displays)
		{
			assert(displayHandle.id < displayContainer->Size() && displayHandle.version == 1u && "Invalid display handle.");
		}

		auto minCorner = Math::Vector2<int>(std::numeric_limits<int>::max());
		auto maxCorner = Math::Vector2<int>(std::numeric_limits<int>::min());
		for (const DisplayHandle displayHandle : mode.displays)
		{
			const DisplayState& state = displayContainer->State(displayHandle.id);
			const auto displayMinCorner = static_cast<Math::Vector2<int>>(state.position);
			const auto displayMaxCorner = displayMinCorner + static_cast<Math::Vector2<int>>(state.resolution);
			minCorner = Math::Min(minCorner, displayMinCorner);
			maxCorner = Math::Max(maxCorner, displayMaxCorner);
		}

		return Math::CornerRect<int>(minCorner, maxCorner - minCorner);
	}

	Math::CornerRect<int> Window::CalculateClientRect(const WindowedWindowMode& mode)
	{
		constexpr auto position = Math::Vector2<int>(CW_USEDEFAULT, CW_USEDEFAULT);
		return Math::CornerRect<int>(position, CalculateClientSize(mode));
	}

	Math::Vector2<int> Window::CalculateClientSize(const WindowedWindowMode& mode)
	{
		if (!mode.size)
		{
			return Math::Vector2<int>(CW_USEDEFAULT, CW_USEDEFAULT);
		}

		if (mode.size->X() > MaxWindowSize.X() || mode.size->Y() > MaxWindowSize.Y()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid window size");
		}

		return static_cast<Math::Vector2<int>>(*mode.size);
	}

	Math::CornerRect<int> Window::CalculateWindowRect(const Math::CornerRect<int>& clientRect, const DWORD style, const DWORD styleEx, const UINT dpi)
	{
		auto rect = ToRect(clientRect);
		if (!AdjustWindowRectExForDpi(&rect, style, FALSE, styleEx, dpi)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to adjust window rect: Error code = '0x{:X}'", GetLastError()));
		}

		return ToCornerRect(rect);
	}

	Math::CornerRect<int> Window::ToCornerRect(const RECT& rect) noexcept
	{
		return Math::CornerRect<int>(Math::Vector2<int>(static_cast<int>(rect.left), static_cast<int>(rect.top)),
			Math::Vector2<int>(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top)));
	}

	RECT Window::ToRect(const Math::CornerRect<int>& rect) noexcept
	{
		return RECT
		{
			.left = rect.Position().X(),
			.top = rect.Position().Y(),
			.right = rect.Position().X() + rect.Size().X(),
			.bottom = rect.Position().Y() + rect.Size().Y()
		};
	}

	std::pair<DWORD, DWORD> Window::CalculateStyle(const WindowMode& mode) noexcept
	{
		return std::visit(Utility::Overload
		{
			[](const FullscreenWindowMode& mode) noexcept
			{
				return CalculateStyle(mode);
			},
			[](const WindowedWindowMode& mode) noexcept
			{
				return CalculateStyle(mode);
			}
		}, mode);
	}

	std::pair<DWORD, DWORD> Window::CalculateStyle(const FullscreenWindowMode& mode) noexcept
	{
		return std::pair(FullscreenStyle, FullscreenStyleEx);
	}

	std::pair<DWORD, DWORD> Window::CalculateStyle(const WindowedWindowMode& mode) noexcept
	{
		DWORD style = WindowedStyle;
		style |= mode.resizableByUser ? ResizableByUserStyle : 0;
		return std::pair(style, WindowedStyleEx);
	}

	Math::CornerRect<int> Window::GetWindowRect() const
	{
		RECT rect;
		if (!::GetWindowRect(windowHandle, &rect)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get window rect: Error code = '0x{:X}'", GetLastError()));
		}

		return ToCornerRect(rect);
	}

	void Window::SetWindowRect(const Math::CornerRect<int>& rect)
	{
		if (!SetWindowPos(windowHandle, HWND_TOP, rect.Position().X(), rect.Position().Y(), rect.Size().X(), rect.Size().Y(), SWP_NOZORDER | SWP_NOSENDCHANGING)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set window rect: Error code = '0x{:X}'", GetLastError()));
		}
	}

	std::pair<DWORD, DWORD> Window::GetWindowStyle() const
	{
		SetLastError(ERROR_SUCCESS);

		const LONG_PTR style = GetWindowLongPtrW(windowHandle, GWL_STYLE);
		if (!style) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_SUCCESS) [[likely]]
			{
				throw std::runtime_error(std::format("Failed to get style: Error code = '0x{:X}'", error));
			}
		}

		const LONG_PTR styleEx = GetWindowLongPtrW(windowHandle, GWL_EXSTYLE);
		if (!styleEx) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_SUCCESS) [[likely]]
			{
				throw std::runtime_error(std::format("Failed to get style ex: Error code = '0x{:X}'", error));
			}
		}

		return std::pair(static_cast<DWORD>(style), static_cast<DWORD>(styleEx));
	}

	LRESULT Window::WindowProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (msg == WM_CREATE) [[unlikely]]
		{
			const auto window = static_cast<Window*>(reinterpret_cast<CREATESTRUCTA*>(lParam)->lpCreateParams);
			SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		}

		if (const auto window = reinterpret_cast<Window*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA))) [[likely]]
		{
			switch (msg)
			{
			case WM_CREATE:
				return window->ObserveCreate(wParam, lParam);
			case WM_DESTROY:
				return window->ObserveDestroy(wParam, lParam);
			case WM_GETMINMAXINFO:
				return window->ObserveGetMinMaxInfo(wParam, lParam);
			case WM_ERASEBKGND:
				return window->ObserveEraseBackground(wParam, lParam);
			case WM_PAINT:
				return window->ObservePaint(wParam, lParam);
			default:
				break;
			}
		}

		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}

	LRESULT Window::ObserveCreate(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		return 0;
	}

	LRESULT Window::ObserveDestroy(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (quitOnDestroy)
		{
			PostQuitMessage(0);
		}

		return 0;
	}

	LRESULT Window::ObserveGetMinMaxInfo(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto minMaxInfo = reinterpret_cast<MINMAXINFO*>(lParam);
		try
		{
			std::visit(Utility::Overload
			{
				[&](const FullscreenPositionSizeMode& mode)
				{
					const Math::CornerRect<int> windowRect = GetWindowRect();
					minMaxInfo->ptMaxSize = POINT{.x = windowRect.Size().X(), .y = windowRect.Size().Y()};
					minMaxInfo->ptMaxPosition = POINT{.x = windowRect.Position().X(), .y = windowRect.Position().Y()};
					minMaxInfo->ptMinTrackSize = POINT{.x = windowRect.Size().X(), .y = windowRect.Size().Y()};
					minMaxInfo->ptMaxTrackSize = POINT{.x = windowRect.Size().X(), .y = windowRect.Size().Y()};
				},
				[&](const WindowedPositionSizeMode& mode)
				{
					const auto [style, styleEx] = GetWindowStyle();
					const UINT dpi = GetDpiForWindow(windowHandle);

					if (mode.minSize)
					{
						const auto clientRect = Math::CornerRect<int>(Math::Vector2<int>(mode.minSize->X(), mode.minSize->Y()));
						const auto windowRect = CalculateWindowRect(clientRect, style, styleEx, dpi);
						minMaxInfo->ptMinTrackSize = POINT{.x = windowRect.Size().X(), .y = windowRect.Size().Y()};
					}

					if (mode.maxSize)
					{
						const auto clientRect = Math::CornerRect<int>(Math::Vector2<int>(mode.maxSize->X(), mode.maxSize->Y()));
						const auto windowRect = CalculateWindowRect(clientRect, style, styleEx, dpi);
						const LONG maxWidth = std::min(minMaxInfo->ptMaxSize.x, static_cast<LONG>(windowRect.Size().X()));
						const LONG maxHeight = std::min(minMaxInfo->ptMaxSize.y, static_cast<LONG>(windowRect.Size().Y()));
						minMaxInfo->ptMaxPosition.x += (minMaxInfo->ptMaxSize.x - maxWidth) / 2;
						minMaxInfo->ptMaxPosition.y += (minMaxInfo->ptMaxSize.y - maxHeight) / 2;
						minMaxInfo->ptMaxTrackSize = POINT{.x = windowRect.Size().X(), .y = windowRect.Size().Y()};
					}
				}
			}, positionSizeMode);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On getting min max info.")
		}

		return 0;
	}

	LRESULT Window::ObserveEraseBackground(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		return 1;
	}

	LRESULT Window::ObservePaint(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (!ValidateRect(windowHandle, nullptr)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to validate rect. Error code: '0x{:X}'.", GetLastError());
		}

		return 0;
	}
}
