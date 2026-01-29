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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Surface.Impl.Windows:SurfaceService;

import std;

import PonyEngine.Application.Ext.Windows;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.MessagePump;
import PonyEngine.Surface.Windows;
import PonyEngine.Type;

import :MemoryManager;
import :MessageHandler;
import :RawInputManager;
import :WindowClass;

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
		SurfaceService(Application::Windows::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, std::string_view title);
		SurfaceService(const SurfaceService&) = delete;
		SurfaceService(SurfaceService&&) = delete;

		~SurfaceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		SurfaceService& operator =(const SurfaceService&) = delete;
		SurfaceService& operator =(SurfaceService&&) = delete;

	private:
		/// @brief Style wrapper.
		struct Style final
		{
			DWORD style; ///< Style.
			DWORD styleEx; ///< Extended style.
		};

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

		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> LastMessageCursorPosition() const noexcept override;

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

		Application::Windows::IApplicationContext* application; ///< Application context.
		MessagePump::IMessagePumpService* pumpService; ///< Message pump service.

		Surface::RectStyle rectStyle; ///< Client rectangle style.
		Math::Vector2<int> minimalClientSize; ///< Minimal client size.

		std::optional<Math::CornerRect<float>> cursorClippingRect; ///< Cursor clipping rectangle.
		bool cursorVisible; ///< Is cursor visible?

		bool unlocked; ///< Is the window changing unlocked?
		bool windowActive; ///< Is the window active?
		bool windowInFocus; ///< Is the window in focus?
		bool windowRepositioning; ///< Is window being moved?

		std::chrono::time_point<std::chrono::steady_clock> lastMessageTime; ///< Last message time.
		Math::Vector2<std::int32_t> lastMessageCursorPosition; ///< Last message cursor position.

		std::shared_ptr<WindowClass> windowClass; ///< Window class.
		MemoryManager memoryManager; ///< Memory manager.
		RawInputManager rawInputManager; ///< Raw input manager.

		HWND windowHandle; ///< Window handle.

		std::vector<ISurfaceObserver*> observers; ///< Surface observer.
	};
}

namespace PonyEngine::Surface::Windows
{
	SurfaceService::SurfaceService(Application::Windows::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, const std::string_view title) :
		application{&application},
		pumpService{&this->application->GetService<MessagePump::IMessagePumpService>()},
		rectStyle(FullscreenRectStyle{.alwaysOnTop = false}),
		minimalClientSize(Math::Vector2<int>::One()),
		cursorClippingRect(Math::CornerRect<float>(Math::Vector2<float>::One())),
		cursorVisible{true},
		unlocked{false},
		windowActive{false},
		windowInFocus{false},
		windowRepositioning{false},
		windowClass(windowClass),
		memoryManager(0uz, 64uz),
		rawInputManager(*this->application, *this, memoryManager)
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
			throw std::runtime_error(std::format("Failed to create window: ErrorCode = '0x{:X}'", GetLastError()));
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
				catch (...)
				{
					PONY_LOG_X(application->Logger(), std::current_exception(), "On freeing cursor.");
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
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Show window.");
		ShowWindow(windowHandle, application->ShowCommand());
	}

	void SurfaceService::End()
	{
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Hide window.");
		ShowWindow(windowHandle, SW_HIDE);
	}

	void SurfaceService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<Surface::ISurfaceService>(*this);
		adder.AddInterface<ISurfaceService>(*this);
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
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		const Style originalStyle = GetStyle();
		const Style style = ConvertToWindowsStyle(rectStyle);
		Math::CornerRect<int> rect = std::holds_alternative<FullscreenRectStyle>(rectStyle)
			? Math::CornerRect<int>(GetResolution())
			: GetClientRect();
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
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		return static_cast<Math::CornerRect<std::int32_t>>(GetClientRect());
	}

	void SurfaceService::ClientRect(const Math::CornerRect<std::int32_t>& clientRect)
	{
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		std::visit(Type::Overload
		{
			[](const FullscreenRectStyle&)
			{
#ifndef NDEBUG
				throw std::logic_error("Rect is fullscreen");
#endif
			},
			[&](const WindowRectStyle& s)
			{
#ifndef NDEBUG
				if (clientRect.Size().X() < minimalClientSize.X() || clientRect.Size().Y() < minimalClientSize.Y()) [[unlikely]]
				{
					throw std::invalid_argument("Size is less than minimal size");
				}
#endif

				const Math::CornerRect<int> currentRect = GetClientRect();
#ifndef NDEBUG
				if (!s.movable && currentRect.Position() != clientRect.Position()) [[unlikely]]
				{
					throw std::invalid_argument("Can't move unmovable window");
				}
				if (!s.resizable && currentRect.Size() != clientRect.Size()) [[unlikely]]
				{
					throw std::invalid_argument("Can't resize non-resizable window");
				}
#endif

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
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
		if (minimalSize.X() <= 0 || minimalSize.Y() <= 0) [[unlikely]]
		{
			throw std::invalid_argument("Minimal size must be at least one pixel");
		}
#endif

		const auto minSize = static_cast<Math::Vector2<int>>(minimalSize);

#ifndef NDEBUG
		if (std::holds_alternative<WindowRectStyle>(rectStyle))
		{
			const Math::CornerRect<int> clientRect = GetClientRect();
			if (clientRect.Size().X() < minSize.X() || clientRect.Size().Y() < minSize.Y()) [[unlikely]]
			{
				throw std::invalid_argument("Minimal size is bigger than current client rect");
			}
		}
#endif

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
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		SetLastError(DWORD{0});
		const int length = GetWindowTextLengthA(windowHandle);
		if (!length) [[unlikely]]
		{
			if (const DWORD errorCode = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to get window title length: ErrorCode = '0x{:X}'", errorCode));
			}

			return std::string_view();
		}

		const std::span<char> title = memoryManager.AllocateTemp<char>(length + 1);
		const int copied = GetWindowTextA(windowHandle, title.data(), length + 1);
		if (!copied) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get window title: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return std::string_view(title.data(), copied);
	}

	void SurfaceService::Title(const std::string_view title)
	{
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		if (!SetWindowTextA(windowHandle, title.data())) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set window title: ErrorCode = '0x{:X}'", GetLastError()));
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
			throw std::runtime_error(std::format("Failed to get cursor position: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(position.x), static_cast<std::int32_t>(position.y));
	}

	bool SurfaceService::IsCursorVisible() const
	{
		CURSORINFO cursorInfo;
		cursorInfo.cbSize = sizeof(CURSORINFO);
		if (!GetCursorInfo(&cursorInfo)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get cursor visibility: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return cursorInfo.flags & CURSOR_SHOWING;
	}

	Math::Vector2<std::int32_t> SurfaceService::ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const
	{
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		auto screenPoint = POINT{.x = static_cast<LONG>(clientPoint.X()), .y = static_cast<LONG>(clientPoint.Y())};
		if (!::ClientToScreen(windowHandle, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get screen point: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(screenPoint.x), static_cast<std::int32_t>(screenPoint.y));
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const
	{
#ifndef NDEBUG
		if (!IsAlive()) [[unlikely]]
		{
			throw std::logic_error("Window is dead");
		}
#endif

		auto clientPoint = POINT{.x = static_cast<LONG>(screenPoint.X()), .y = static_cast<LONG>(screenPoint.Y())};
		if (!::ScreenToClient(windowHandle, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get client point: ErrorCode = '0x{:X}'", GetLastError()));
		}

		return Math::Vector2<std::int32_t>(static_cast<std::int32_t>(clientPoint.x), static_cast<std::int32_t>(clientPoint.y));
	}

	void SurfaceService::AddObserver(ISurfaceObserver& observer)
	{
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

	std::chrono::time_point<std::chrono::steady_clock> SurfaceService::LastMessageTime() const noexcept
	{
		return lastMessageTime;
	}

	Math::Vector2<std::int32_t> SurfaceService::LastMessageCursorPosition() const noexcept
	{
		return lastMessageCursorPosition;
	}

	void SurfaceService::AddRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage)
	{
		rawInputManager.AddRawInputObserver(observer, usagePage, usage);
	}

	void SurfaceService::AddRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages)
	{
		rawInputManager.AddRawInputObserver(observer, rawInputUsages);
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage) noexcept
	{
		rawInputManager.RemoveRawInputObserver(observer, usagePage, usage);
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept
	{
		rawInputManager.RemoveRawInputObserver(observer, rawInputUsages);
	}

	void SurfaceService::RemoveRawInputObserver(IRawInputObserver& observer) noexcept
	{
		rawInputManager.RemoveRawInputObserver(observer);
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

		lastMessageTime = pumpService->LastMessageTime();
		lastMessageCursorPosition = pumpService->LastMessageCursorPosition();

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
			return rawInputManager.ObserveRawInput(wParam, lParam);
		case WM_INPUT_DEVICE_CHANGE:
			return rawInputManager.ObserveInputDeviceChange(wParam, lParam);
		default:
			return DefWindowProcA(windowHandle, uMsg, wParam, lParam);
		}
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
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On observing focus change.");
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
			throw std::runtime_error(std::format("Failed to adjust window rect: ErrorCode = '0x{:X}'", GetLastError()));
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
			throw std::runtime_error(std::format("Failed to get client rect: ErrorCode = '0x{:X}'", GetLastError()));
		}
		auto screenPosition = POINT{.x = rect.top, .y = rect.top};
		if (!::ClientToScreen(windowHandle, &screenPosition)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get client position: ErrorCode = '0x{:X}'", GetLastError()));
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
			throw std::runtime_error(std::format("Failed to get window rect: ErrorCode = '0x{:X}'", GetLastError()));
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
			throw std::runtime_error(std::format("Failed to set window rect: ErrorCode = '0x{:X}'", GetLastError()));
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
			throw std::runtime_error("Failed to get screen resolution");
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
				throw std::runtime_error(std::format("Failed to get window style: ErrorCode = '0x{:X}'", error));
			}
		}

		style.styleEx = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_EXSTYLE));
		if (!style.styleEx) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to get extended window style: ErrorCode = '0x{:X}'", error));
			}
		}

		return style;
	}

	void SurfaceService::SetStyle(const Style style)
	{
		SetLastError(DWORD{0});

		unlocked = true;
		const DWORD styleValue = style.style | (WS_VISIBLE & (0 - IsWindowVisible(windowHandle)));
		if (!SetWindowLongPtrA(windowHandle, GWL_STYLE, static_cast<LONG_PTR>(styleValue))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				unlocked = false;
				throw std::runtime_error(std::format("Failed to set window style: ErrorCode = '0x{:X}'", error));
			}
		}

		if (!SetWindowLongPtrA(windowHandle, GWL_EXSTYLE, static_cast<LONG_PTR>(style.styleEx))) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				unlocked = false;
				throw std::runtime_error(std::format("Failed to set extended window style: ErrorCode = '0x{:X}'", error));
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
				throw std::runtime_error(std::format("Failed to clip cursor: ErrorCode = '0x{:X}'", GetLastError()));
			}
		}
		else
		{
			if (!::ClipCursor(nullptr)) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to free cursor: ErrorCode = '0x{:X}'", GetLastError()));
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
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On updating cursor clipping.");
				cursorClippingRect = std::nullopt;
			}
		}
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
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On observing active change.");
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
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On getting min max info.");
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
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On window position changing.");
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
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On observing move.");
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
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On observing resize.");
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
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On observing display change.");
			}
		}

		std::visit(Type::Overload
		{
			[&](const FullscreenRectStyle&)
			{
				try
				{
					const Math::CornerRect<int> rect = AdjustRect(Math::CornerRect<int>(static_cast<Math::Vector2<int>>(resolution)), GetStyle());
					SetWindowRect(rect);

					UpdateCursorClipping();
				}
				catch (...)
				{
					PONY_LOG_X(application->Logger(), std::current_exception(), "On window display change.");
					cursorClippingRect = std::nullopt;
				}
			},
			[&](const WindowRectStyle&)
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
}
