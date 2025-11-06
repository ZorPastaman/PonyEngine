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

export module PonyEngine.Surface.Impl:SurfaceService;

import std;

import PonyEngine.Application.Ext;
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
		[[nodiscard("Pure constructor")]]
		SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, std::string_view title);
		SurfaceService(const SurfaceService&) = delete;
		SurfaceService(SurfaceService&&) = delete;

		~SurfaceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual SurfaceFeature SupportedFeatures() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Surface::RectStyle RectStyle() const noexcept override;
		virtual void RectStyle(const Surface::RectStyle& rectStyle) override;

		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const override;
		[[nodiscard("Pure function")]]
		virtual Math::CornerRect<std::int32_t> ClientRect() const override;
		virtual void ClientRect(const Math::CornerRect<std::int32_t>& clientRect) override;
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
		virtual std::optional<Math::CornerRect<float>> CursorClippingRect() const override;
		virtual void CursorClippingRect(const std::optional<Math::CornerRect<float>>& clippingRect) override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> CursorPosition() const override;
		[[nodiscard("Pure function")]]
		virtual bool IsCursorVisible() const override;

		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const override;

		virtual void AddObserver(ISurfaceObserver& observer) override;
		virtual void RemoveObserver(ISurfaceObserver& observer) noexcept override;

		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept override;

		virtual void AddRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) override;
		virtual void AddRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) noexcept override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept override;
		virtual void RemoveRawInputObserver(IRawInputObserver& observer) noexcept override;

		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept override;

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
		/// @brief Style wrapper.
		struct Style final
		{
			DWORD style; ///< Style.
			DWORD styleEx; ///< Extended style.
		};

		/// @brief Updates a focus change.
		void UpdateFocus() noexcept;

		/// @brief Adjust the rectangle by the style.
		/// @param rect Rectangle.
		/// @param style Style.
		/// @return Adjusted rectangle.
		[[nodiscard("Pure function")]]
		static Math::CornerRect<int> AdjustRect(const Math::CornerRect<int>& rect, Style style);
		/// @brief Gets the client rectangle.
		/// @return Client rectangle.
		[[nodiscard("Pure function")]]
		Math::CornerRect<int> GetClientRect() const;
		/// @brief Gets the window rectangle.
		/// @return Window rectangle.
		[[nodiscard("Pure function")]]
		Math::CornerRect<int> GetWindowRect() const;
		/// @brief Sets the window rectangle.
		/// @param rect Window rectangle.
		void SetWindowRect(const Math::CornerRect<int>& rect);
		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> GetResolution();

		/// @brief Gets a window style.
		/// @return Window style and extended style.
		[[nodiscard("Pure function")]]
		Style GetStyle() const;
		/// @brief Sets a window style.
		/// @param style Style.
		void SetStyle(Style style);
		/// @brief Converts a rectangle style to a Windows style.
		/// @param style Rectangle style.
		/// @return Windows style.
		[[nodiscard("Pure function")]]
		static constexpr Style ConvertToWindowsStyle(const Surface::RectStyle& style) noexcept;

		/// @brief Clips the cursor to the specified rectangle.
		/// @param clippingRect Clipping rectangle. If std::nullopt, the cursor will be free to move.
		void ClipCursor(const std::optional<Math::CornerRect<float>>& clippingRect);
		/// @brief Checks if the window in valid state to apply a cursor clipping.
		/// @return @a True if it's a valid state; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool CanApplyCursorClipping() const noexcept;
		/// @brief Updates cursor clipping.
		void UpdateCursorClipping() noexcept;

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
		/// @brief Observes the WM_MOVE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveMove(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_SIZE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveSize(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_WM_DISPLAYCHANGE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveDisplayChange(WPARAM wParam, LPARAM lParam) noexcept;
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

		Application::Windows::IApplicationContext* application; ///< Application context.

		Surface::RectStyle rectStyle; ///< Client rectangle style.
		Math::Vector2<int> minimalClientSize; ///< Minimal client size.

		std::optional<Math::CornerRect<float>> cursorClippingRect; ///< Cursor clipping rectangle.
		bool cursorVisible; ///< Is cursor visible?

		bool unlocked; ///< Is the window changing unlocked?
		bool windowActive; ///< Is the window active?
		bool windowInFocus; ///< Is the window in focus?
		bool windowRepositioning; ///< Is window being moved?

		std::shared_ptr<WindowClass> windowClass; ///< Window class.

		HWND windowHandle; ///< Window handle.

		std::vector<ISurfaceObserver*> observers; ///< Surface observer.
		std::unordered_map<DWORD, std::vector<IRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		mutable std::string titleTemp; ///< Title temp data.
		std::vector<BYTE> rawInputTemp; ///< Raw input temp data.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Surface::Windows
{
	SurfaceService::SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, const std::string_view title) :
		application{application.NativePtr()},
		rectStyle(FullscreenRectStyle{.alwaysOnTop = false}),
		minimalClientSize(Math::Vector2<int>::One()),
		cursorClippingRect(Math::CornerRect<float>(Math::Vector2<float>::One())),
		cursorVisible{true},
		unlocked{false},
		windowActive{false},
		windowInFocus{false},
		windowRepositioning{false},
		windowClass(windowClass)
	{
		assert(this->windowClass && "The window class is nullptr.");

		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Calculating window rect.");
		const Style style = ConvertToWindowsStyle(rectStyle);
		const Math::CornerRect<int> rect = AdjustRect(Math::CornerRect<int>(GetResolution()), style);

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window... Window class: '0x{:X}'; Title: '{}'; Position: '{}'; Size: '{}'; Style: '{}'; StyleEx: '{}'.", 
			windowClass->ClassHandle(), title, rect.Position(), rect.Size(), style.style, style.styleEx);
		windowHandle = CreateWindowExA(
			style.styleEx,
			reinterpret_cast<LPCSTR>(this->windowClass->ClassHandle()),
			title.data(),
			style.style,
			rect.Position().X(),
			rect.Position().Y(),
			rect.Size().X(),
			rect.Size().Y(),
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
		if (CanApplyCursorClipping())
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

	SurfaceFeature SurfaceService::SupportedFeatures() const noexcept
	{
		return SurfaceFeature::FullscreenStyle | SurfaceFeature::WindowStyle | SurfaceFeature::ClientRect | SurfaceFeature::Title | SurfaceFeature::HardwareCursor;
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

		const Style originalStyle = GetStyle();
		const Style style = ConvertToWindowsStyle(rectStyle);
		Math::CornerRect<int> rect = GetClientRect();
		if (std::holds_alternative<WindowRectStyle>(rectStyle))
		{
			rect.Size(Math::Max(rect.Size(), minimalClientSize));
		}
		const Math::CornerRect<int> adjustedRect = AdjustRect(rect, style);
		try
		{
			SetStyle(style);
			SetWindowRect(adjustedRect);
		}
		catch (...)
		{
			SetStyle(originalStyle);
			throw;
		}

		this->rectStyle = rectStyle;
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenResolution() const
	{
		return static_cast<Math::Vector2<std::int32_t>>(GetResolution());
	}

	Math::CornerRect<std::int32_t> SurfaceService::ClientRect() const
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		return static_cast<Math::CornerRect<std::int32_t>>(GetClientRect());
	}

	void SurfaceService::ClientRect(const Math::CornerRect<std::int32_t>& clientRect)
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
				if (clientRect.Size().X() < minimalClientSize.X() || clientRect.Size().Y() < minimalClientSize.Y()) [[unlikely]]
				{
					throw std::invalid_argument("Size is less than minimal size.");
				}

				const Math::CornerRect<int> currentRect = GetClientRect();
				if (!s.movable && currentRect.Position() != clientRect.Position()) [[unlikely]]
				{
					throw std::invalid_argument("Can't move unmovable window.");
				}
				if (!s.resizable && currentRect.Size() != clientRect.Size()) [[unlikely]]
				{
					throw std::invalid_argument("Can't resize non-resizable window.");
				}

				const Math::CornerRect<int> adjustedRect = AdjustRect(static_cast<Math::CornerRect<int>>(clientRect), GetStyle());
				SetWindowRect(adjustedRect);
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

		if (std::holds_alternative<WindowRectStyle>(rectStyle))
		{
			const Math::CornerRect<int> clientRect = GetClientRect();
			if (clientRect.Size().X() < minSize.X() || clientRect.Size().Y() < minSize.Y()) [[unlikely]]
			{
				throw std::invalid_argument("Minimal size is bigger than current client rect.");
			}
		}

		minimalClientSize = minSize;
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

		titleTemp.clear();
		titleTemp.reserve(length + 1);
		const int copied = GetWindowTextA(windowHandle, titleTemp.data(), length + 1);
		if (!copied) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get window title. Error code: '0x{:X}'.", GetLastError()));
		}
		titleTemp.resize(copied);

		return titleTemp;
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
		if (cursorVisible != visible)
		{
			ShowCursor(visible);
		}

		cursorVisible = visible;
	}

	std::optional<Math::CornerRect<float>> SurfaceService::CursorClippingRect() const
	{
		return cursorClippingRect;
	}

	void SurfaceService::CursorClippingRect(const std::optional<Math::CornerRect<float>>& clippingRect)
	{
		if (CanApplyCursorClipping())
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

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(position.x), static_cast<std::int32_t>(position.y));
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

		auto screenPoint = POINT{.x = static_cast<LONG>(clientPoint.X()), .y = static_cast<LONG>(clientPoint.Y())};
		if (!::ClientToScreen(windowHandle, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(screenPoint.x), static_cast<std::int32_t>(screenPoint.y));
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const
	{
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead.");
		}

		auto clientPoint = POINT{.x = static_cast<LONG>(screenPoint.X()), .y = static_cast<LONG>(screenPoint.Y())};
		if (!::ScreenToClient(windowHandle, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get client point. Error code: '0x{:X}'.", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(clientPoint.x), static_cast<std::int32_t>(clientPoint.y));
	}

	void SurfaceService::AddObserver(ISurfaceObserver& observer)
	{
#if !NDEBUG
		if (std::ranges::find(observers, &observer) != observers.cend()) [[unlikely]]
		{
			throw std::invalid_argument("The observer has already been added.");
		}
#endif

		observers.push_back(&observer);
	}

	void SurfaceService::RemoveObserver(ISurfaceObserver& observer) noexcept
	{
		if (const auto position = std::ranges::find(observers, &observer); position != observers.cend()) [[likely]]
		{
			observers.erase(position);
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove surface observer that hadn't been added.");
		}
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

#if !NDEBUG
		if (std::ranges::find(observers, &observer) != observers.cend()) [[unlikely]]
		{
			throw std::invalid_argument("The raw input observer has already been added.");
		}
#endif

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

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer that hadn't been added. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
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

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer that hadn't been added.");
	}

	Application::IApplicationContext& SurfaceService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplicationContext& SurfaceService::Application() const noexcept
	{
		return *application;
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
		case WM_MOVE:
			return ObserveMove(wParam, lParam);
		case WM_SIZE:
			return ObserveSize(wParam, lParam);
		case WM_DISPLAYCHANGE:
			return ObserveDisplayChange(wParam, lParam);
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

	void SurfaceService::UpdateFocus() noexcept
	{
		UpdateCursorClipping();

		for (ISurfaceObserver* const observer : observers)
		{
			try
			{
				observer->OnFocusChanged(windowInFocus);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing focus change.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing focus change.");
			}
		}
	}

	Math::CornerRect<int> SurfaceService::AdjustRect(const Math::CornerRect<int>& rect, const Style style)
	{
		auto windowRect = RECT
		{
			.left = static_cast<LONG>(rect.Position().X()),
			.top = static_cast<LONG>(rect.Position().Y()),
			.right = static_cast<LONG>(rect.Position().X() + rect.Size().X()),
			.bottom = static_cast<LONG>(rect.Position().Y() + rect.Size().Y())
		};
		if (!AdjustWindowRectEx(&windowRect, style.style, false, style.styleEx)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		const auto position = Math::Vector2<int>(static_cast<int>(windowRect.left), static_cast<int>(windowRect.top));
		const auto size = Math::Vector2<int>(static_cast<int>(windowRect.right - windowRect.left), static_cast<int>(windowRect.bottom - windowRect.top));

		return Math::CornerRect<int>(position, size);
	}

	Math::CornerRect<int> SurfaceService::GetClientRect() const
	{
		RECT rect;
		if (!::GetClientRect(windowHandle, &rect)) [[unlikely]]
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

		return Math::CornerRect<int>(position, size);
	}

	Math::CornerRect<int> SurfaceService::GetWindowRect() const
	{
		RECT rect;
		if (!::GetWindowRect(windowHandle, &rect)) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to get window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		const auto position = Math::Vector2<int>(static_cast<int>(rect.left), static_cast<int>(rect.bottom));
		const auto size = Math::Vector2<int>(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));

		return Math::CornerRect<int>(position, size);
	}

	void SurfaceService::SetWindowRect(const Math::CornerRect<int>& rect)
	{
		const HWND insert = std::visit(Type::Overload
		{
			[&](const FullscreenRectStyle& s) noexcept
			{
				return s.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST;
			},
			[&](const WindowRectStyle& s) noexcept
			{
				return s.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST;
			}
		}, rectStyle);

		unlocked = true;
		if (!SetWindowPos(windowHandle, insert, rect.Position().X(), rect.Position().Y(), rect.Size().X(), rect.Size().Y(), SWP_NOACTIVATE | SWP_FRAMECHANGED)) [[unlikely]]
		{
			unlocked = false;
			throw std::runtime_error(Text::FormatSafe("Failed to set window rect. Error code: '0x{:X}'.", GetLastError()));
		}
		unlocked = false;
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

	SurfaceService::Style SurfaceService::GetStyle() const
	{
		SetLastError(DWORD{0});

		Style style;
		style.style = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_STYLE));
		if (!style.style) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to get window style. Error code: '0x{:X}'.", error));
			}
		}

		style.styleEx = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_EXSTYLE));
		if (!style.styleEx) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Text::FormatSafe("Failed to get extended window style. Error code: '0x{:X}'.", error));
			}
		}

		return style;
	}

	void SurfaceService::SetStyle(const Style style)
	{
		SetLastError(DWORD{0});

		unlocked = true;
		if (!SetWindowLongPtrA(windowHandle, GWL_STYLE, static_cast<LONG_PTR>(style.style))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				unlocked = false;
				throw std::runtime_error(Text::FormatSafe("Failed to set window style. Error code: '0x{:X}'.", error));
			}
		}

		if (!SetWindowLongPtrA(windowHandle, GWL_EXSTYLE, static_cast<LONG_PTR>(style.styleEx))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				unlocked = false;
				throw std::runtime_error(Text::FormatSafe("Failed to set extended window style. Error code: '0x{:X}'.", error));
			}
		}
		unlocked = false;
	}

	constexpr SurfaceService::Style SurfaceService::ConvertToWindowsStyle(const Surface::RectStyle& style) noexcept
	{
		return Style
		{
			.style = std::visit<DWORD>(Type::Overload
			{
				[](const FullscreenRectStyle&) constexpr noexcept
				{
					return WS_POPUP;
				},
				[](const WindowRectStyle& s) constexpr noexcept
				{
					DWORD windowsStyle = 0;
					windowsStyle |= WS_CAPTION & (0 - (s.hasFrame | s.movable));
					windowsStyle |= (WS_CAPTION | WS_THICKFRAME) & (0 - s.resizable);
					windowsStyle |= (WS_CAPTION | WS_SYSMENU) & (0 - s.closable);
					windowsStyle |= (WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX) & (0 - s.maximizable);
					windowsStyle |= (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX) & (0 - s.minimizable);

					return windowsStyle == 0 ? WS_POPUP : windowsStyle;
				}
			}, style),
			.styleEx = std::visit<DWORD>(Type::Overload
			{
				[](const FullscreenRectStyle& s) constexpr noexcept
				{
					DWORD windowsStyle = WS_EX_APPWINDOW;
					windowsStyle |= WS_EX_TOPMOST & (0 - s.alwaysOnTop);

					return windowsStyle;
				},
				[](const WindowRectStyle& s) constexpr noexcept
				{
					DWORD windowsStyle = WS_EX_APPWINDOW;
					windowsStyle |= WS_EX_TOPMOST & (0 - s.alwaysOnTop);

					return windowsStyle;
				}
			}, style)
		};
	}

	void SurfaceService::ClipCursor(const std::optional<Math::CornerRect<float>>& clippingRect)
	{
		if (clippingRect)
		{
			const Math::CornerRect<int> clientRect = GetClientRect();
			const Math::Vector2<int> clippingPosition = clientRect.Position() + 
				static_cast<Math::Vector2<int>>(Math::Multiply(clippingRect->Position(), static_cast<Math::Vector2<float>>(clientRect.Size())));
			const Math::Vector2<int> clippingSize = static_cast<Math::Vector2<int>>(Math::Multiply(clippingRect->Size(), static_cast<Math::Vector2<float>>(clientRect.Size())));
			const auto rect = RECT
			{
				.left = static_cast<LONG>(clippingPosition.X()),
				.top = static_cast<LONG>(clippingPosition.Y()),
				.right = static_cast<LONG>(clippingPosition.X() + clippingSize.X()),
				.bottom = static_cast<LONG>(clippingPosition.Y() + clippingSize.Y())
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

	bool SurfaceService::CanApplyCursorClipping() const noexcept
	{
		return windowInFocus && !windowRepositioning;
	}

	void SurfaceService::UpdateCursorClipping() noexcept
	{
		if (CanApplyCursorClipping()) [[likely]]
		{
			try
			{
				ClipCursor(cursorClippingRect);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On updating cursor clipping.");
				cursorClippingRect = std::nullopt;
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
		PONY_LOG(application->Logger(), Log::LogType::Info, "Window created.");
		return 0;
	}

	LRESULT SurfaceService::ObserveDestroy(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Window destroyed. Stopping engine.");
		application->Stop();

		return 0;
	}

	LRESULT SurfaceService::ObserveActivate(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowActive = wParam != WA_INACTIVE;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Window activate changed to '{}'.", windowActive);

		for (ISurfaceObserver* const observer : observers)
		{
			try
			{
				observer->OnActiveChanged(windowActive);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing active change.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing active change.");
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveSetFocus(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowInFocus = true;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Window focus changed to '{}'.", windowInFocus);

		UpdateFocus();

		return 0;
	}

	LRESULT SurfaceService::ObserveKillFocus(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowInFocus = false;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Window focus changed to '{}'.", windowInFocus);

		UpdateFocus();

		return 0;
	}

	LRESULT SurfaceService::ObserveGetMinMaxInfo(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		try
		{
			const auto minMax = reinterpret_cast<MINMAXINFO*>(lParam);
			const Math::Vector2<int> resolution = GetResolution();
			const Math::CornerRect<int> rect = AdjustRect(Math::CornerRect<int>(minimalClientSize), GetStyle());

			minMax->ptMaxSize = POINT{.x = resolution.X(), .y = resolution.Y()};
			minMax->ptMaxPosition = POINT{.x = 0l, .y = 0l};
			minMax->ptMinTrackSize = POINT{.x = rect.Size().X(), .y = rect.Size().Y()};
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
		UpdateCursorClipping();

		return 0;
	}

	LRESULT SurfaceService::ObserveExitSizeMove(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowRepositioning = false;
		UpdateCursorClipping();

		return 0;
	}

	LRESULT SurfaceService::ObserveWindowPosChanging(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (unlocked)
		{
			return 0;
		}

		try
		{
			const auto windowPos = reinterpret_cast<WINDOWPOS*>(lParam);
			std::visit(Type::Overload
			{
				[&](const FullscreenRectStyle&) noexcept
				{
					windowPos->flags |= SWP_NOMOVE | SWP_NOSIZE;
				},
				[&](const WindowRectStyle& s)
				{
					const Math::CornerRect<int> rect = AdjustRect(Math::CornerRect<int>(minimalClientSize), GetStyle());
					windowPos->cx = std::max(windowPos->cx, rect.Size().X());
					windowPos->cy = std::max(windowPos->cy, rect.Size().Y());
					windowPos->flags |= SWP_NOMOVE & (0 - !s.movable);
					windowPos->flags |= SWP_NOSIZE & (0 - !s.resizable);
				}
			}, rectStyle);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On window position changing.");
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveWindowPosChanged(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		UpdateCursorClipping();

		return DefWindowProcA(windowHandle, WM_WINDOWPOSCHANGED, wParam, lParam);
	}

	LRESULT SurfaceService::ObserveMove(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const std::int32_t x = static_cast<std::int32_t>(LOWORD(lParam));
		const std::int32_t y = static_cast<std::int32_t>(HIWORD(lParam));
		const auto position = Math::Vector2<std::int32_t>(x, y);

		for (ISurfaceObserver* const observer : observers)
		{
			try
			{
				observer->OnMoved(position);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing move.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing move.");
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveSize(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const std::int32_t newWidth = static_cast<std::int32_t>(LOWORD(lParam));
		const std::int32_t newHeight = static_cast<std::int32_t>(HIWORD(lParam));
		const auto size = Math::Vector2<std::int32_t>(newWidth, newHeight);

		for (ISurfaceObserver* const observer : observers)
		{
			try
			{
				observer->OnResized(size);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing resize.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing resize.");
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveDisplayChange(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const int newWidth = LOWORD(lParam);
		const int newHeight = HIWORD(lParam);
		const auto resolution = Math::Vector2<std::int32_t>(static_cast<std::int32_t>(newWidth), static_cast<std::int32_t>(newHeight));

		for (ISurfaceObserver* const observer : observers)
		{
			try
			{
				observer->OnResolutionChanged(resolution);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing display change.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing display change.");
			}
		}

		std::visit(Type::Overload
		{
			[&](const FullscreenRectStyle& s)
			{
				try
				{
					const Math::CornerRect<int> rect = AdjustRect(Math::CornerRect<int>(static_cast<Math::Vector2<int>>(resolution)), GetStyle());
					SetWindowRect(rect);

					UpdateCursorClipping();
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On window display change.");
					cursorClippingRect = std::nullopt;
				}
			},
			[&](const WindowRectStyle& s)
			{
				UpdateCursorClipping();
			}
		}, rectStyle);

		return 0;
	}

	LRESULT SurfaceService::ObserveStyleChanging(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (unlocked)
		{
			return 0;
		}

		const auto style = reinterpret_cast<STYLESTRUCT*>(lParam);
		style->styleNew = style->styleOld;

		return 0;
	}

	LRESULT SurfaceService::ObserveEraseBackground(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		return 1;
	}

	LRESULT SurfaceService::ObservePaint(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (!ValidateRect(windowHandle, nullptr)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to validate rect. Error code: '0x{:X}'.", GetLastError());
		}

		return 0;
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
			rawInputTemp.resize(size);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(application->Logger(), e, "On resizing raw input cache.");
			return 0;
		}
		if (GetRawInputData(rawInputInfo, RID_INPUT, rawInputTemp.data(), &size, sizeof(RAWINPUTHEADER)) != rawInputTemp.size()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}

		const RAWINPUT* const input = reinterpret_cast<RAWINPUT*>(rawInputTemp.data());
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
			const std::chrono::time_point<std::chrono::steady_clock> time = application->LastMessageTime();
			const Math::Vector2<std::int32_t> cursorPosition = application->LastMessageCursorPosition();

			for (IRawInputObserver* const observer : observerPosition->second)
			{
				try
				{
					observer->Observe(*input, time, cursorPosition);
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
