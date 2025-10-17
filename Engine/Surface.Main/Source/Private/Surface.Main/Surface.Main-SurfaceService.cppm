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

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Surface.Main:SurfaceService;

import std;

import PonyEngine.Application.Extension;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Surface;
import PonyEngine.Type;

import :MessageHandler;
import :WindowClass;

#if PONY_WINDOWS
export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows surface service.
	class SurfaceService final : public Application::IService, private ISurfaceService, private IMessageHandler
	{
	public:
		/// @brief Creates a Windows surface service.
		/// @param application Application context.
		/// @param windowClass Window class.
		/// @param title Window title.
		/// @param rectStyle Rectangle style.
		/// @param cursorClippingRect Cursor clipping rectangle.
		/// @param cursorVisible Is cursor visible?
		/// @param clientRect Client rectangle. Ignored in fullscreen.
		/// @param minimalClientSize Minimal client size.
		[[nodiscard("Pure constructor")]]
		SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, std::string_view title, 
			const Surface::RectStyle& rectStyle, const std::optional<Math::Rect<float>>& cursorClippingRect, bool cursorVisible,
			const Math::Rect<std::int32_t>& clientRect, const Math::Vector2<std::int32_t>& minimalClientSize);
		SurfaceService(const SurfaceService&) = delete;
		SurfaceService(SurfaceService&&) = delete;

		~SurfaceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual Surface::RectStyle RectStyle() const noexcept override;
		virtual void RectStyle(const Surface::RectStyle& rectStyle) override;

		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const override;
		[[nodiscard("Pure function")]]
		virtual Math::Rect<std::int32_t> ClientRect() const override;
		virtual void ClientRect(const Math::Rect<std::int32_t>& clientRect) override;
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> MinimalSize() const override;
		virtual void MinimalSize(const Math::Vector2<std::int32_t>& minimalSize) override;

		[[nodiscard("Pure funtion")]]
		virtual bool IsAlive() const override;
		[[nodiscard("Pure funtion")]]
		virtual bool IsActive() const override;
		[[nodiscard("Pure funtion")]]
		virtual bool IsInFocus() const override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const override;
		virtual void Title(std::string_view title) override;

		[[nodiscard("Pure function")]]
		virtual bool CursorVisibility() const override;
		virtual void CursorVisibility(bool visible) override;
		[[nodiscard("Pure function")]]
		virtual std::optional<Math::Rect<float>> CursorClippingRect() const override;
		virtual void CursorClippingRect(const std::optional<Math::Rect<float>>& clippingRect) override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> CursorPosition() const override;
		virtual void CursorPosition(const Math::Vector2<std::int32_t>& position) override;
		[[nodiscard("Pure function")]]
		virtual bool IsCursorVisible() const override;

		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const override;

		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept override;

		virtual void AddRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) override;
		virtual void AddRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) noexcept override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer) noexcept override;

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		/// @brief Gets the public surface service.
		/// @return Public surface service.
		[[nodiscard("Pure function")]]
		ISurfaceService& PublicSurfaceService() noexcept;
		/// @brief Gets the public surface service.
		/// @return Public surface service.
		[[nodiscard("Pure function")]]
		const ISurfaceService& PublicSurfaceService() const noexcept;

		SurfaceService& operator =(const SurfaceService&) = delete;
		SurfaceService& operator =(SurfaceService&&) = delete;

	private:
		/// @brief Calculates an engine point.
		/// @param windowsPoint Windows point.
		/// @param resolution Resolution.
		/// @return Engine point.
		[[nodiscard("Pure function")]]
		static Math::Vector2<std::int32_t> CalculateEnginePoint(const Math::Vector2<int>& windowsPoint, const Math::Vector2<int>& resolution) noexcept;
		/// @brief Calculates a Windows point.
		/// @param enginePoint Engine point.
		/// @param resolution Resolution.
		/// @return Windows point.
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> CalculateWindowsPoint(const Math::Vector2<std::int32_t>& enginePoint, const Math::Vector2<int>& resolution) noexcept;
		/// @brief Calculates an engine rectangle.
		/// @param position Window client position.
		/// @param size Window client size.
		/// @param resolution Resolution.
		/// @return Engine rectangle.
		[[nodiscard("Pure function")]]
		static Math::Rect<std::int32_t> CalculateEngineRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, const Math::Vector2<int>& resolution) noexcept;
		/// @brief Calculates a Windows rectangle.
		/// @param rect Rectangle.
		/// @param resolution Resolution.
		/// @return Windows position and size.
		[[nodiscard("Pure function")]]
		static std::pair<Math::Vector2<int>, Math::Vector2<int>> CalculateWindowsRect(const Math::Rect<std::int32_t>& rect, const Math::Vector2<int>& resolution) noexcept;
		/// @brief Adjust the rectangle by the style.
		/// @param position Position.
		/// @param size Size.
		/// @param style Style.
		/// @param styleEx Extended style.
		/// @return Adjusted position and size.
		[[nodiscard("Pure function")]]
		static std::pair<Math::Vector2<int>, Math::Vector2<int>> AdjustRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, DWORD style, DWORD styleEx);
		/// @brief Clamps the rect inside the screen.
		/// @param position Position.
		/// @param size Size.
		/// @param resolution Resolution.
		/// @return Clamped position and size.
		[[nodiscard("Pure function")]]
		static std::pair<Math::Vector2<int>, Math::Vector2<int>> ClampInScreen(const Math::Vector2<int>& position, const Math::Vector2<int>& size, const Math::Vector2<int>& resolution) noexcept;
		/// @brief Calculates the client rect.
		/// @return Client position and size.
		[[nodiscard("Pure function")]]
		std::pair<Math::Vector2<int>, Math::Vector2<int>> CalculateClientRect() const;
		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> GetResolution();

		/// @brief Gets a window style.
		/// @return Window style and extended style.
		[[nodiscard("Pure function")]]
		std::pair<DWORD, DWORD> GetStyle() const;
		/// @brief Sets a window style.
		/// @param style Style.
		/// @param styleEx Extended style.
		void SetStyle(DWORD style, DWORD styleEx);
		/// @brief Converts a rectangle style to a Windows style.
		/// @param style Rectangle style.
		/// @return Windows style.
		[[nodiscard("Pure function")]]
		static constexpr DWORD ConvertToWindowsStyle(const Surface::RectStyle& style) noexcept;
		/// @brief Converts a rectangle style to a Windows style ex.
		/// @param style Rectangle style.
		/// @return Windows style ex.
		[[nodiscard("Pure function")]]
		static constexpr DWORD ConvertToWindowsStyleEx(const Surface::RectStyle& style) noexcept;

		/// @brief Clips the cursor to the specified rectangle.
		/// @param clippingRect Clipping rectangle. If std::nullopt, the cursor will be free to move.
		void ClipCursor(const std::optional<Math::Rect<float>>& clippingRect);

		/// @brief Registers a raw input type.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		void RegisterRawInputType(USHORT usagePage, USHORT usage);
		/// @brief Unregisters a raw input type.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		void UnregisterRawInputType(USHORT usagePage, USHORT usage);
		/// @brief Registers/unregisters a raw input type.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		/// @param flags Registration flags.
		void RegisterRawInputType(USHORT usagePage, USHORT usage, DWORD flags);
		/// @brief Gets a hid type from the raw input.
		/// @param input Raw input.
		/// @return Hid type.
		[[nodiscard("Pure function")]]
		static DWORD GetHidType(const RAWINPUT& input);

		/// @brief Observes the WM_CREATE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveCreate(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_DESTROY message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveDestroy(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_ACTIVATE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveActivate(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_SETFOCUS message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveSetFocus(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_KILLFOCUS message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveKillFocus(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_GETMINMAXINFO message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveGetMinMaxInfo(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_ENTERSIZEMOVE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveEnterSizeMove(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_EXITSIZEMOVE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveExitSizeMove(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_WINDOWPOSCHANGING message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveWindowPosChanging(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_WINDOWPOSCHANGED message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveWindowPosChanged(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_STYLECHANGING message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveStyleChanging(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_ERASEBKGND message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveEraseBackground(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_PAINT message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObservePaint(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_INPUT message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveRawInput(WPARAM wParam, LPARAM lParam) noexcept;

		/// @brief Packs the two USHORT values into a DWORD.
		/// @param first High bit value.
		/// @param second Low bit value.
		/// @return Value pack.
		[[nodiscard("Pure function")]]
		static constexpr DWORD Pack(USHORT first, USHORT second) noexcept;
		/// @brief Unpacks the DWORD value into two USHORT values.
		/// @param value Value.
		/// @return High bit value and low bit value.
		[[nodiscard("Pure function")]]
		static constexpr std::pair<USHORT, USHORT> Unpack(DWORD value) noexcept;

		Application::IApplicationContext* application; ///< Application context.

		Surface::RectStyle rectStyle; ///< Client rectangle style.
		Math::Vector2<int> minimalClientSize; ///< Minimal client size.
		Math::Vector2<int> minimalWindowSize; ///< Minimal window size.

		std::optional<Math::Rect<float>> cursorClippingRect; ///< Cursor clipping rectangle.
		bool cursorVisible; ///< Is cursor visible?

		bool styleUnlocked; ///< Is the style changing unlocked?
		bool windowActive; ///< Is the window active?
		bool windowInFocus; ///< Is the window in focus?
		bool windowRepositioning; ///< Is window being moved?
		bool erased; ///< Is the background erased? It's erased only once. A render system must paint the window after that.
		bool painted; ///< Is the window painted? It's painted only once. A render system must paint the window after that.

		std::shared_ptr<WindowClass> windowClass; ///< Window class.

		HWND windowHandle; ///< Window handle.

		std::unordered_map<DWORD, std::vector<IRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		mutable std::string titleCache; ///< Title cache.
		std::vector<BYTE> rawInputCache; ///< Raw input cache.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Surface::Windows
{
	SurfaceService::SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, const std::string_view title, 
		const Surface::RectStyle& rectStyle, const std::optional<Math::Rect<float>>& cursorClippingRect, bool cursorVisible, 
		const Math::Rect<std::int32_t>& clientRect, const Math::Vector2<std::int32_t>& minimalClientSize) :
		application{&application},
		rectStyle(rectStyle),
		minimalClientSize(static_cast<Math::Vector2<int>>(minimalClientSize)),
		cursorClippingRect(cursorClippingRect),
		cursorVisible{cursorVisible},
		styleUnlocked{false},
		windowActive{false},
		windowInFocus{false},
		windowRepositioning{false},
		erased{false},
		painted{false},
		windowClass(windowClass)
	{
		const bool fullscreen = std::holds_alternative<FullscreenRectStyle>(this->rectStyle);

		assert(this->windowClass && "The window class is nullptr.");
		assert((fullscreen || (clientRect.Extent(0) > 0 && clientRect.Extent(1) > 0)) && "The client rect is invalid.");
		assert(this->minimalClientSize.X() > 0 && this->minimalClientSize.Y() > 0 && "The minimal client size is invalid.");

		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Calculating window rect.");
		const Math::Vector2<int> resolution = GetResolution();
		const DWORD style = ConvertToWindowsStyle(this->rectStyle);
		const DWORD styleEx = ConvertToWindowsStyleEx(this->rectStyle);
		const Math::Rect<std::int32_t> actualRect = fullscreen ? Math::Rect<std::int32_t>(static_cast<Math::Vector2<std::int32_t>>(resolution / 2)) : clientRect;
		const auto [clientPosition, clientSize] = CalculateWindowsRect(actualRect, resolution);
		const auto [windowPosition, windowSize] = AdjustRect(clientPosition, clientSize, style, styleEx);
		const auto [clampedWindowPosition, clampedWindowSize] = ClampInScreen(windowPosition, windowSize, resolution);
		const auto [minWindowPosition, minWindowSize] = AdjustRect(Math::Vector2<int>::Zero(), this->minimalClientSize, style, styleEx);
		minimalWindowSize = minWindowSize;
		const auto correctWindowSize = fullscreen ? clampedWindowSize : Math::Max(clampedWindowSize, minimalWindowSize);

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window... Window class: '0x{:X}'; Title: '{}'; Position: '{}'; Size: '{}'; Style: '{}'.", 
			windowClass->ClassHandle(), title, windowPosition, windowSize, style);
		windowHandle = CreateWindowExA(
			styleEx,
			reinterpret_cast<LPCSTR>(this->windowClass->ClassHandle()),
			title.data(),
			style,
			clampedWindowPosition.X(),
			clampedWindowPosition.Y(),
			correctWindowSize.X(),
			correctWindowSize.Y(),
			nullptr,
			nullptr,
			windowClass->ModuleHandle(),
			static_cast<IMessageHandler*>(this)
		);
		if (!windowHandle) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window done. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));
	}

	SurfaceService::~SurfaceService() noexcept
	{
		if (windowInFocus)
		{
			if (cursorClippingRect)
			{
				try
				{
					ClipCursor(std::nullopt);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On freeing cursor.");
				}
			}
			if (!cursorVisible)
			{
				ShowCursor(true);
			}
		}

		if (IsAlive())
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Destroying window... Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));
			if (!DestroyWindow(windowHandle)) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Error on destroying window. Error code: '0x{:X}'.", GetLastError());
			}
			PONY_LOG(application->Logger(), Log::LogType::Info, "Destroying window done.");
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Skip destroying window 'cause it's already been destroyed.");
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing window class...");
		windowClass.reset();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Releasing window class done.");
	}

	void SurfaceService::Begin()
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Show window.");
		ShowWindow(windowHandle, this->application->Native().ShowCommand());
	}

	void SurfaceService::End()
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Hide window.");
		ShowWindow(windowHandle, SW_HIDE);
	}

	Surface::RectStyle SurfaceService::RectStyle() const noexcept
	{
		return rectStyle;
	}

	void SurfaceService::RectStyle(const Surface::RectStyle& rectStyle)
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		const auto [position, size] = std::visit<std::pair<Math::Vector2<int>, Math::Vector2<int>>>(Type::Overload
		{
			[](const FullscreenRectStyle&) noexcept
			{
				return std::pair(Math::Vector2<int>::Zero(), GetResolution());
			},
			[&](const WindowRectStyle&)
			{
				return CalculateClientRect();
			}
		}, rectStyle);

		const DWORD style = ConvertToWindowsStyle(rectStyle);
		const DWORD styleEx = ConvertToWindowsStyleEx(rectStyle);
		const auto [windowPosition, windowSize] = AdjustRect(position, size, style, styleEx);
		const auto [minimalWindowPos, minimalWindowSiz] = AdjustRect(Math::Vector2<int>::Zero(), minimalClientSize, style, styleEx);

		const auto [originalStyle, originalStyleEx] = GetStyle();
		try
		{
			SetStyle(style, styleEx);
			if (!SetWindowPos(windowHandle, nullptr, windowPosition.X(), windowPosition.Y(), windowSize.X(), windowSize.Y(), SWP_NOZORDER)) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to set window rect. Error code: '0x{:X}'.", GetLastError()));
			}
		}
		catch (...)
		{
			SetStyle(originalStyle, originalStyleEx);
			throw;
		}

		this->rectStyle = rectStyle;
		minimalWindowSize = minimalWindowSiz;
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenResolution() const
	{
		return static_cast<Math::Vector2<std::int32_t>>(GetResolution());
	}

	Math::Rect<std::int32_t> SurfaceService::ClientRect() const
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		const auto [position, size] = CalculateClientRect();
		const Math::Vector2<int> resolution = GetResolution();

		return CalculateEngineRect(position, size, resolution);
	}

	void SurfaceService::ClientRect(const Math::Rect<std::int32_t>& clientRect)
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		std::visit(Type::Overload
		{
			[](const FullscreenRectStyle&)
			{
				throw std::logic_error("Rect is fullscreen.");
			},
			[&](const WindowRectStyle& s)
			{
				if (clientRect.Extent(0) <= 0 || clientRect.Extent(1) <= 0) [[unlikely]]
				{
					throw std::invalid_argument("Client rect size on both axes must be greater than zero.");
				}

				const Math::Vector2<int> resolution = GetResolution();
				const auto [position, size] = CalculateWindowsRect(clientRect, resolution);
				if (size.X() < minimalClientSize.X() || size.Y() < minimalClientSize.Y()) [[unlikely]]
				{
					throw std::invalid_argument("Size is less than minimal size.");
				}

				const auto [clientPosition, clientSize] = CalculateClientRect();
				if (!s.movable && clientPosition != position) [[unlikely]]
				{
					throw std::invalid_argument("Can't move unmovable window.");
				}
				if (!s.resizable && clientSize != size) [[unlikely]]
				{
					throw std::invalid_argument("Can't resize non-resizable window.");
				}

				const auto [style, styleEx] = GetStyle();
				const auto [adjustedPosition, adjustedSize] = AdjustRect(position, size, style, styleEx);

				if (!SetWindowPos(windowHandle, nullptr, adjustedPosition.X(), adjustedPosition.Y(), adjustedSize.X(), adjustedSize.Y(), SWP_NOZORDER)) [[unlikely]]
				{
					throw std::runtime_error(Text::FormatSafe("Failed to set window rect. Error code: '0x{:X}'.", GetLastError()));
				}
			}
		}, rectStyle);
	}

	Math::Vector2<std::int32_t> SurfaceService::MinimalSize() const
	{
		return minimalClientSize;
	}

	void SurfaceService::MinimalSize(const Math::Vector2<std::int32_t>& minimalSize)
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}
		if (minimalSize.X() <= 0 || minimalSize.Y() <= 0) [[unlikely]]
		{
			throw std::invalid_argument("Minimal size must be at least one pixel.");
		}

		const auto minSize = static_cast<Math::Vector2<int>>(minimalSize);
		const auto [clientPosition, clientSize] = CalculateClientRect();
		if (clientSize.X() < minSize.X() || clientSize.Y() < minSize.Y()) [[unlikely]]
		{
			throw std::invalid_argument("Minimal size is bigger than current client rect.");
		}

		const auto [style, styleEx] = GetStyle();
		const auto [minWindowPosition, minWindowSize] = AdjustRect(Math::Vector2<int>::Zero(), minSize, style, styleEx);

		minimalClientSize = minSize;
		minimalWindowSize = minWindowSize;
	}

	bool SurfaceService::IsAlive() const
	{
		return IsWindow(windowHandle);
	}

	bool SurfaceService::IsActive() const
	{
		return windowActive;
	}

	bool SurfaceService::IsInFocus() const
	{
		return windowInFocus;
	}

	std::string_view SurfaceService::Title() const
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		SetLastError(DWORD{0});
		const int length = GetWindowTextLengthA(windowHandle);
		if (!length) [[unlikely]]
		{
			if (const DWORD errorCode = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to get window title length. Error code: '0x{:X}'.", errorCode));
			}

			return std::string_view();
		}

		titleCache.clear();
		titleCache.reserve(length + 1);
		const int copied = GetWindowTextA(windowHandle, titleCache.data(), length + 1);
		if (!copied) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get window title. Error code: '0x{:X}'.", GetLastError()));
		}
		titleCache.resize(copied);

		return titleCache;
	}

	void SurfaceService::Title(const std::string_view title)
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		if (!SetWindowTextA(windowHandle, title.data())) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to set window title. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	bool SurfaceService::CursorVisibility() const
	{
		return cursorVisible;
	}

	void SurfaceService::CursorVisibility(const bool visible)
	{
		if (cursorVisible != visible && windowInFocus)
		{
			ShowCursor(visible);
		}

		cursorVisible = visible;
	}

	std::optional<Math::Rect<float>> SurfaceService::CursorClippingRect() const
	{
		return cursorClippingRect;
	}

	void SurfaceService::CursorClippingRect(const std::optional<Math::Rect<float>>& clippingRect)
	{
		if (windowInFocus && !windowRepositioning)
		{
			ClipCursor(clippingRect);
		}

		cursorClippingRect = clippingRect;
	}

	Math::Vector2<std::int32_t> SurfaceService::CursorPosition() const
	{
		POINT position;
		if (!GetCursorPos(&position)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get cursor position. Error code: '0x{:X}'.", GetLastError()));
		}
		const Math::Vector2<int> resolution = GetResolution();

		return CalculateEnginePoint(Math::Vector2<int>(static_cast<int>(position.x), static_cast<int>(position.y)), resolution);
	}

	void SurfaceService::CursorPosition(const Math::Vector2<std::int32_t>& position)
	{
		if (!windowInFocus) [[unlikely]]
		{
			throw std::logic_error("Can't change cursor position when window isn't in focus.");
		}

		const Math::Vector2<int> resolution = GetResolution();
		const Math::Vector2<int> pos = CalculateWindowsPoint(position, resolution);
		if (!SetCursorPos(pos.X(), pos.Y())) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to set cursor position. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	bool SurfaceService::IsCursorVisible() const
	{
		CURSORINFO cursorInfo;
		cursorInfo.cbSize = sizeof(CURSORINFO);
		if (!GetCursorInfo(&cursorInfo)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get cursor visibility. Error code: '0x{:X}'.", GetLastError()));
		}

		return cursorInfo.flags & CURSOR_SHOWING;
	}

	Math::Vector2<std::int32_t> SurfaceService::ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		const Math::Vector2<int> resolution = GetResolution();
		const Math::Vector2<int> windowsClient = CalculateWindowsPoint(clientPoint, resolution);
		auto screenPoint = POINT{.x = static_cast<LONG>(windowsClient.X()), .y = static_cast<LONG>(windowsClient.Y())};
		if (!::ClientToScreen(windowHandle, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		return CalculateEnginePoint(Math::Vector2<int>(static_cast<int>(screenPoint.x), static_cast<int>(screenPoint.y)), resolution);
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		const Math::Vector2<int> resolution = GetResolution();
		const Math::Vector2<int> windowsScreen = CalculateWindowsPoint(screenPoint, resolution);
		auto clientPoint = POINT{.x = static_cast<LONG>(windowsScreen.X()), .y = static_cast<LONG>(windowsScreen.Y())};
		if (!::ScreenToClient(windowHandle, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get client point. Error code: '0x{:X}'.", GetLastError()));
		}

		return CalculateEnginePoint(Math::Vector2<int>(static_cast<int>(clientPoint.x), static_cast<int>(clientPoint.y)), resolution);
	}

	HWND SurfaceService::Handle() noexcept
	{
		return windowHandle;
	}

	void SurfaceService::AddRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage)
	{
		const DWORD usageType = Pack(usagePage, usage);
		const auto typePosition = rawInputObservers.find(usageType);
		std::vector<IRawInputObserver*>& observers = typePosition != rawInputObservers.cend() ? typePosition->second : rawInputObservers[usageType];
		assert(std::ranges::find(observers, &observer) == observers.cend() && "The raw input observer has already been added.");
		observers.push_back(&observer);

		if (observers.size() == 1uz)
		{
			try
			{
				RegisterRawInputType(usagePage, usage);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On registering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
				observers.pop_back();

				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on registering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
				observers.pop_back();

				throw;
			}
		}
	}

	void SurfaceService::AddRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages)
	{
		for (std::size_t i = 0uz; i < rawInputUsages.size(); ++i)
		{
			try
			{
				AddRawInputObserver(observer, rawInputUsages[i].first, rawInputUsages[i].second);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveRawInputObserver(observer, rawInputUsages[i].first, rawInputUsages[i].second);
				}

				throw;
			}
		}
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage) noexcept
	{
		const DWORD usageType = Pack(usagePage, usage);
		if (const auto position = rawInputObservers.find(usageType); position != rawInputObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				if (position->second.empty())
				{
					try
					{
						UnregisterRawInputType(usagePage, usage);
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(application->Logger(), e, "On unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
					catch (...)
					{
						PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
				}

				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove observer of raw input type but it hadn't been added. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept
	{
		for (const auto [usagePage, usage] : rawInputUsages)
		{
			RemoveRawInputObserver(observer, usagePage, usage);
		}
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (auto& [type, observers] : rawInputObservers)
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;

				if (observers.empty())
				{
					const auto [usagePage, usage] = Unpack(type);
					try
					{
						UnregisterRawInputType(usagePage, usage);
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(application->Logger(), e, "On unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
					catch (...)
					{
						PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
				}
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer but it hadn't been added.");
	}

	LRESULT SurfaceService::HandleMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Received '{}' message.", uMsg);

		switch (uMsg)
		{
		case WM_CREATE:
			return ObserveCreate(wParam, lParam);
		case WM_DESTROY:
			return ObserveDestroy(wParam, lParam);
		case WM_ACTIVATE:
			return ObserveActivate(wParam, lParam);
		case WM_SETFOCUS:
			return ObserveSetFocus(wParam, lParam);
		case WM_KILLFOCUS:
			return ObserveKillFocus(wParam, lParam);
		case WM_GETMINMAXINFO:
			return ObserveGetMinMaxInfo(wParam, lParam);
		case WM_ENTERSIZEMOVE:
			return ObserveEnterSizeMove(wParam, lParam);
		case WM_EXITSIZEMOVE:
			return ObserveExitSizeMove(wParam, lParam);
		case WM_WINDOWPOSCHANGING:
			return ObserveWindowPosChanging(wParam, lParam);
		case WM_WINDOWPOSCHANGED:
			return ObserveWindowPosChanged(wParam, lParam);
		case WM_STYLECHANGING:
			return ObserveStyleChanging(wParam, lParam);
		case WM_ERASEBKGND:
			return ObserveEraseBackground(wParam, lParam);
		case WM_PAINT:
			return ObservePaint(wParam, lParam);
		case WM_INPUT:
			return ObserveRawInput(wParam, lParam);
		default:
			return DefWindowProcA(windowHandle, uMsg, wParam, lParam);
		}
	}

	ISurfaceService& SurfaceService::PublicSurfaceService() noexcept
	{
		return *this;
	}

	const ISurfaceService& SurfaceService::PublicSurfaceService() const noexcept
	{
		return *this;
	}

	Math::Vector2<std::int32_t> SurfaceService::CalculateEnginePoint(const Math::Vector2<int>& windowsPoint, const Math::Vector2<int>& resolution) noexcept
	{
		const auto screenCenter = static_cast<Math::Vector2<std::int32_t>>(resolution / 2);
		const auto point = static_cast<Math::Vector2<std::int32_t>>(windowsPoint);

		return Math::Vector2<std::int32_t>(point.X() - screenCenter.X(), screenCenter.Y() - point.Y());
	}

	Math::Vector2<int> SurfaceService::CalculateWindowsPoint(const Math::Vector2<std::int32_t>& enginePoint, const Math::Vector2<int>& resolution) noexcept
	{
		const Math::Vector2<int> screenCenter = resolution / 2;
		const auto point = static_cast<Math::Vector2<int>>(enginePoint);

		return Math::Vector2<int>(point.X() + screenCenter.X(), screenCenter.Y() - point.Y());
	}

	Math::Rect<std::int32_t> SurfaceService::CalculateEngineRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, const Math::Vector2<int>& resolution) noexcept
	{
		const auto extents = static_cast<Math::Vector2<std::int32_t>>(size) / 2;
		const Math::Vector2<std::int32_t> pos = CalculateEnginePoint(position, resolution);
		const auto center = Math::Vector2<std::int32_t>(pos.X() + extents.X(), pos.Y() - extents.Y());

		return Math::Rect<std::int32_t>(center, extents);
	}

	std::pair<Math::Vector2<int>, Math::Vector2<int>> SurfaceService::CalculateWindowsRect(const Math::Rect<std::int32_t>& rect, const Math::Vector2<int>& resolution) noexcept
	{
		const auto extents = static_cast<Math::Vector2<int>>(rect.Extents());
		const Math::Vector2<int> size = extents * 2;
		const Math::Vector2<int> center = CalculateWindowsPoint(rect.Center(), resolution);
		const Math::Vector2<int> position = center - extents;

		return std::pair(position, size);
	}

	std::pair<Math::Vector2<int>, Math::Vector2<int>> SurfaceService::AdjustRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, 
		const DWORD style, const DWORD styleEx)
	{
		auto windowRect = RECT
		{
			.left = static_cast<LONG>(position.X()),
			.top = static_cast<LONG>(position.Y()),
			.right = static_cast<LONG>(position.X() + size.X()),
			.bottom = static_cast<LONG>(position.Y() + size.Y())
		};
		if (!AdjustWindowRectEx(&windowRect, style, false, styleEx)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		const auto adjustedPosition = Math::Vector2<int>(static_cast<int>(windowRect.left), static_cast<int>(windowRect.top));
		const auto adjustedSize = Math::Vector2<int>(static_cast<int>(windowRect.right - windowRect.left), static_cast<int>(windowRect.bottom - windowRect.top));

		return std::pair(adjustedPosition, adjustedSize);
	}

	std::pair<Math::Vector2<int>, Math::Vector2<int>> SurfaceService::ClampInScreen(const Math::Vector2<int>& position, const Math::Vector2<int>& size, 
		const Math::Vector2<int>& resolution) noexcept
	{
		const Math::Vector2<int> clampedSize = Math::Clamp(size, Math::Vector2<int>::Zero(), resolution);
		const Math::Vector2<int> clampedPosition = Math::Clamp(position, Math::Vector2<int>::Zero(), resolution - clampedSize);

		return std::pair(clampedPosition, clampedSize);
	}

	std::pair<Math::Vector2<int>, Math::Vector2<int>> SurfaceService::CalculateClientRect() const
	{
		RECT rect;
		if (!GetClientRect(windowHandle, &rect)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get client rect. Error code: '0x{:X}'.", GetLastError()));
		}
		auto screenPosition = POINT{.x = rect.top, .y = rect.top};
		if (!::ClientToScreen(windowHandle, &screenPosition)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get client position. Error code: '0x{:X}'.", GetLastError()));
		}
		const auto position = Math::Vector2<int>(static_cast<int>(screenPosition.x), static_cast<int>(screenPosition.y));
		const auto size = Math::Vector2<int>(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));

		return std::pair(position, size);
	}

	Math::Vector2<int> SurfaceService::GetResolution()
	{
		Math::Vector2<int> resolution;
		resolution.X() = GetSystemMetrics(SM_CXSCREEN);
		resolution.Y() = GetSystemMetrics(SM_CYSCREEN);
		if (!resolution.X() || !resolution.Y()) [[unlikely]]
		{
			throw std::runtime_error("Failed to get screen resolution.");
		}

		return resolution;
	}

	std::pair<DWORD, DWORD> SurfaceService::GetStyle() const
	{
		SetLastError(DWORD{0});

		const auto style = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_STYLE));
		if (!style) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to get window style. Error code: '0x{:X}'.", error));
			}
		}

		const auto styleEx = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_EXSTYLE));
		if (!styleEx) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to get extended window style. Error code: '0x{:X}'.", error));
			}
		}

		return std::pair(style, styleEx);
	}

	void SurfaceService::SetStyle(const DWORD style, const DWORD styleEx)
	{
		SetLastError(DWORD{0});

		styleUnlocked = true;
		if (!SetWindowLongPtrA(windowHandle, GWL_STYLE, static_cast<LONG_PTR>(style))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				styleUnlocked = false;
				throw std::runtime_error(Text::FormatSafe("Failed to set window style. Error code: '0x{:X}'.", error));
			}
		}

		if (!SetWindowLongPtrA(windowHandle, GWL_EXSTYLE, static_cast<LONG_PTR>(styleEx))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				styleUnlocked = false;
				throw std::runtime_error(Text::FormatSafe("Failed to set extended window style. Error code: '0x{:X}'.", error));
			}
		}
		styleUnlocked = false;
	}

	constexpr DWORD SurfaceService::ConvertToWindowsStyle(const Surface::RectStyle& style) noexcept
	{
		return std::visit<DWORD>(Type::Overload
		{
			[](const FullscreenRectStyle&) noexcept
			{
				return WS_POPUP;
			},
			[](const WindowRectStyle& s) noexcept
			{
				DWORD windowsStyle = 0;
				windowsStyle |= WS_CAPTION & (0 - (s.hasFrame | s.movable));
				windowsStyle |= (WS_CAPTION | WS_THICKFRAME) & (0 - s.resizable);
				windowsStyle |= (WS_CAPTION | WS_SYSMENU) & (0 - s.closable);
				windowsStyle |= (WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX) & (0 - s.maximizable);
				windowsStyle |= (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX) & (0 - s.minimizable);

				return windowsStyle == 0 ? WS_POPUP : windowsStyle;
			}
		}, style);
	}

	constexpr DWORD SurfaceService::ConvertToWindowsStyleEx(const Surface::RectStyle& style) noexcept
	{
		return std::visit<DWORD>(Type::Overload
		{
			[](const FullscreenRectStyle& s) noexcept
			{
				return WS_EX_TOPMOST & (0 - s.alwaysOnTop);
			},
			[](const WindowRectStyle& s) noexcept
			{
				return WS_EX_TOPMOST & (0 - s.alwaysOnTop);
			}
		}, style);
	}

	void SurfaceService::ClipCursor(const std::optional<Math::Rect<float>>& clippingRect)
	{
		if (clippingRect)
		{
			const Math::Rect<std::int32_t> clientRect = ClientRect();
			const Math::Vector2<int> resolution = GetResolution();
			const Math::Vector2<int> clippingPosition = CalculateWindowsPoint(RelativeToAbsolute(clippingRect->Center(), clientRect.Extents()) + clientRect.Center(), resolution);
			const Math::Vector2<std::int32_t> clippingExtents = RelativeToAbsolute(clippingRect->Extents(), clientRect.Extents());

			const auto rect = RECT
			{
				.left = static_cast<LONG>(clippingPosition.X()) - static_cast<LONG>(clippingExtents.X()),
				.top = static_cast<LONG>(clippingPosition.Y()) - static_cast<LONG>(clippingExtents.Y()),
				.right = static_cast<LONG>(clippingPosition.X()) + static_cast<LONG>(clippingExtents.X()),
				.bottom = static_cast<LONG>(clippingPosition.Y()) + static_cast<LONG>(clippingExtents.Y())
			};
			if (!::ClipCursor(&rect)) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to clip cursor. Error code: '0x{:X}'.", GetLastError()));
			}
		}
		else
		{
			if (!::ClipCursor(nullptr)) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to free cursor. Error code: '0x{:X}'.", GetLastError()));
			}
		}
	}

	void SurfaceService::RegisterRawInputType(const USHORT usagePage, const USHORT usage)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering raw input type... Usage page: '{}'; Usage: '{}'.", usagePage, usage);
		RegisterRawInputType(usagePage, usage, DWORD{0});
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering raw input type done. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void SurfaceService::UnregisterRawInputType(const USHORT usagePage, const USHORT usage)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Unregistering raw input type... Usage page: '{}'; Usage: '{}'.", usagePage, usage);
		RegisterRawInputType(usagePage, usage, RIDEV_REMOVE);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Unregistering raw input type done. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void SurfaceService::RegisterRawInputType(const USHORT usagePage, const USHORT usage, const DWORD flags)
	{
		const auto rid = RAWINPUTDEVICE
		{
			.usUsagePage = usagePage,
			.usUsage = usage,
			.dwFlags = flags,
			.hwndTarget = windowHandle
		};

		if (!RegisterRawInputDevices(&rid, 1u, sizeof(rid))) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to register/unregister raw input device. Usage page: '0x{:X}'; Usage: '0x{:X}'; Flags: '0x{:X}'; Window handle: '0x{:X}'. Error code: '0x{:X}'.", rid.usUsagePage, rid.usUsage, rid.dwFlags, reinterpret_cast<std::uintptr_t>(rid.hwndTarget), GetLastError()));
		}
	}

	DWORD SurfaceService::GetHidType(const RAWINPUT& input)
	{
		auto info = RID_DEVICE_INFO{.cbSize = sizeof(RID_DEVICE_INFO)};
		UINT size = sizeof(info);
		if (!GetRawInputDeviceInfoA(input.header.hDevice, RIDI_DEVICEINFO, &info, &size)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get hid device info. Error code: '0x{:X}'.", GetLastError()));
		}

		if (info.dwType != RIM_TYPEHID) [[unlikely]]
		{
			throw std::runtime_error("Wrong hid device.");
		}

		return Pack(info.hid.usUsagePage, info.hid.usUsage);
	}

	LRESULT SurfaceService::ObserveCreate(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Window created. Window hangle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));
		return 0;
	}

	LRESULT SurfaceService::ObserveDestroy(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Window destroyed. Stopping engine. Window hangle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));
		application->Stop();
		PostQuitMessage(0);

		return 0;
	}

	LRESULT SurfaceService::ObserveActivate(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowActive = wParam != WA_INACTIVE;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Window activate changed to '{}'.", windowActive);

		return 0;
	}

	LRESULT SurfaceService::ObserveSetFocus(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowInFocus = true;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Window focus changed to '{}'.", windowInFocus);

		if (!cursorVisible)
		{
			ShowCursor(false);
		}

		if (cursorClippingRect)
		{
			try
			{
				ClipCursor(cursorClippingRect);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On clipping cursor on setting focus.");
				cursorClippingRect = std::nullopt;
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveKillFocus(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowInFocus = false;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Window focus changed to '{}'.", windowInFocus);

		if (!cursorVisible)
		{
			ShowCursor(true);
		}

		if (cursorClippingRect)
		{
			try
			{
				ClipCursor(std::nullopt);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On freeing cursor on killing focus.");
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveGetMinMaxInfo(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		try
		{
			const auto minMax = reinterpret_cast<MINMAXINFO*>(lParam);
			const Math::Vector2<int> resolution = GetResolution();

			minMax->ptMaxSize = POINT{.x = resolution.X(), .y = resolution.Y()};
			minMax->ptMaxPosition = POINT{.x = 0l, .y = 0l};
			minMax->ptMinTrackSize = POINT{.x = minimalWindowSize.X(), .y = minimalWindowSize.Y()};
			minMax->ptMaxTrackSize = POINT{.x = resolution.X(), .y = resolution.Y()};
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On getting min max info.");
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveEnterSizeMove(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowRepositioning = true;

		if (windowInFocus && cursorClippingRect)
		{
			try
			{
				ClipCursor(std::nullopt);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On freeing cursor on window deactivation.");
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveExitSizeMove(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowRepositioning = false;

		if (windowInFocus && cursorClippingRect)
		{
			try
			{
				ClipCursor(cursorClippingRect);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On clipping cursor on window size-move exit.");
				cursorClippingRect = std::nullopt;
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveWindowPosChanging(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto windowPos = reinterpret_cast<WINDOWPOS*>(lParam);
		std::visit(Type::Overload
		{
			[&](const FullscreenRectStyle&) noexcept
			{
				windowPos->flags |= SWP_NOMOVE | SWP_NOSIZE;
			},
			[&](const WindowRectStyle& s) noexcept
			{
				windowPos->cx = std::max(windowPos->cx, minimalWindowSize.X());
				windowPos->cy = std::max(windowPos->cy, minimalWindowSize.Y());
				windowPos->flags |= SWP_NOMOVE & (0 - !s.movable);
				windowPos->flags |= SWP_NOSIZE & (0 - !s.resizable);
			}
		}, rectStyle);

		return 0;
	}

	LRESULT SurfaceService::ObserveWindowPosChanged(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (!windowRepositioning && cursorClippingRect)
		{
			try
			{
				ClipCursor(cursorClippingRect);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On clipping cursor on window repositioning.");
				cursorClippingRect = std::nullopt;
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveStyleChanging(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (styleUnlocked)
		{
			return 0;
		}

		const auto style = reinterpret_cast<STYLESTRUCT*>(lParam);
		style->styleNew = style->styleOld;

		return 0;
	}

	LRESULT SurfaceService::ObserveEraseBackground(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (erased) [[likely]]
		{
			return 1;
		}

		erased = true;
		return DefWindowProcA(windowHandle, WM_ERASEBKGND, wParam, lParam);
	}

	LRESULT SurfaceService::ObservePaint(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (painted) [[likely]]
		{
			if (!ValidateRect(windowHandle, nullptr)) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to validate rect. Error code: '0x{:X}'.", GetLastError());
			}

			return 0;
		}

		painted = true;
		return DefWindowProcA(windowHandle, WM_PAINT, wParam, lParam);
	}

	LRESULT SurfaceService::ObserveRawInput(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto rawInputInfo = reinterpret_cast<HRAWINPUT>(lParam);
		UINT size = 0u;
		if (GetRawInputData(rawInputInfo, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER))) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input size. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}
		if (size < 1u) [[unlikely]]
		{
			return 0;
		}
		try
		{
			rawInputCache.resize(size);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On resizing raw input cache.");
			return 0;
		}
		if (GetRawInputData(rawInputInfo, RID_INPUT, rawInputCache.data(), &size, sizeof(RAWINPUTHEADER)) != rawInputCache.size()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}

		const RAWINPUT* const input = reinterpret_cast<RAWINPUT*>(rawInputCache.data());
		DWORD usageType;
		switch (input->header.dwType)
		{
		case RIM_TYPEMOUSE:
			usageType = Pack(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
			break;
		case RIM_TYPEKEYBOARD:
			usageType = Pack(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
			break;
		case RIM_TYPEHID:
			try
			{
				usageType = GetHidType(*input);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On getting hid type.");
				return 0;
			}
			break;
		default: [[unlikely]]
			PONY_LOG(application->Logger(), Log::LogType::Error, "Unexpected raw input type.");
			return 0;
		}

		if (const auto observerPosition = rawInputObservers.find(usageType); observerPosition != rawInputObservers.cend())
		{
			for (IRawInputObserver* const observer : observerPosition->second)
			{
				try
				{
					observer->Observe(*input);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On calling '{}' raw input observer.", typeid(*observer).name());
				}
				catch (...)
				{
					PONY_LOG(application->Logger(), Log::LogType::Error, "Unknown exception on calling '{}' raw input observer.", typeid(*observer).name());
				}
			}
		}

		return 0;
	}

	constexpr DWORD SurfaceService::Pack(const USHORT first, const USHORT second) noexcept
	{
		return static_cast<DWORD>(first) << 16 | second;
	}

	constexpr std::pair<USHORT, USHORT> SurfaceService::Unpack(const DWORD value) noexcept
	{
		return std::pair(static_cast<USHORT>(value >> 16), static_cast<USHORT>(value));
	}
}
#endif
