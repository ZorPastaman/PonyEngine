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

export module PonyEngine.Surface.Main.Windows:SurfaceService;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Surface.Main;
import PonyEngine.Surface.Windows;
import PonyEngine.Utility;

import :MessageHandler;
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
		/// @param clientRect Client rect.
		/// @param minimalClientSize Minimal window size.
		/// @param style Window style.
		/// @param showCursor Show cursor.
		/// @param cursorClippingRect Cursor clipping rect.
		[[nodiscard("Pure constructor")]]
		SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, std::string_view title, const Math::Rect<std::int32_t>& clientRect, 
			const Math::Vector2<std::int32_t>& minimalClientSize, SurfaceStyle style, bool showCursor, const std::optional<Math::Rect<float>>& cursorClippingRect);
		SurfaceService(const SurfaceService&) = delete;
		SurfaceService(SurfaceService&&) = delete;

		~SurfaceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const override;
		[[nodiscard("Pure function")]]
		virtual Math::Rect<std::int32_t> ClientRect() const override;
		virtual void ClientRect(const Math::Rect<std::int32_t>& rect) override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> MinimalClientSize() const override;
		virtual void MinimalClientSize(const Math::Vector2<std::int32_t>& size) override;

		[[nodiscard("Pure funtion")]]
		virtual bool IsActive() const override;
		[[nodiscard("Pure funtion")]]
		virtual bool IsInFocus() const override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const override;
		virtual void Title(std::string_view title) override;

		[[nodiscard("Pure function")]]
		virtual SurfaceStyle Style() const override;
		virtual void Style(SurfaceStyle style) override;

		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> CursorPosition() const override;
		virtual void CursorPosition(const Math::Vector2<std::int32_t>& position) override;
		[[nodiscard("Pure function")]]
		virtual bool IsCursorVisible() const override;
		[[nodiscard("Pure function")]]
		virtual bool IsCursorReallyVisible() const override;
		virtual void ShowCursor(bool visible) override;
		[[nodiscard("Pure function")]]
		virtual std::optional<Math::Rect<float>> CursorClippingRect() const override;
		virtual void CursorClippingRect(const std::optional<Math::Rect<float>>& rect) override;

		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const override;
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const override;

		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept override;

		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) override;
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept override;
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept override;

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
		/// @return Engine point.
		[[nodiscard("Pure function")]]
		static Math::Vector2<std::int32_t> CalculateEnginePoint(const Math::Vector2<int>& windowsPoint);
		/// @brief Calculates a Windows point.
		/// @param enginePoint Engine point.
		/// @return Windows point.
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> CalculateWindowsPoint(const Math::Vector2<std::int32_t>& enginePoint);
		/// @brief Calculates an engine rectangle.
		/// @param position Window client position.
		/// @param size Window client size.
		/// @return Engine rectangle.
		[[nodiscard("Pure function")]]
		static Math::Rect<std::int32_t> CalculateEngineRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size);
		/// @brief Calculates a Windows rectangle.
		/// @param rect Engine rectangle.
		/// @return Windows position and size.
		[[nodiscard("Pure function")]]
		static std::pair<Math::Vector2<int>, Math::Vector2<int>> CalculateWindowsRect(const Math::Rect<std::int32_t>& rect);
		/// @brief Adjust the rectangle by the style.
		/// @param position Position.
		/// @param size Size.
		/// @param style Style.
		/// @param styleEx Extended style.
		/// @return Adjusted position and size.
		[[nodiscard("Pure function")]]
		static std::pair<Math::Vector2<int>, Math::Vector2<int>> AdjustRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size, DWORD style, DWORD styleEx);
		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> GetResolution();
		/// @brief Gets a screen center.
		/// @return Screen center.
		[[nodiscard("Pure function")]]
		static Math::Vector2<int> GetScreenCenter();
		/// @brief Clamps the rect inside [-1, 1].
		/// @param rect Rect.
		/// @return Clamped rect.
		[[nodiscard("Pure function")]]
		static Math::Rect<float> ClampRect(const Math::Rect<float>& rect) noexcept;

		/// @brief Gets a window style.
		/// @return Window style and extended style.
		[[nodiscard("Pure function")]]
		std::pair<DWORD, DWORD> GetStyle() const;
		/// @brief Sets a window style.
		/// @param style Style.
		/// @param styleEx Extended style.
		void SetStyle(DWORD style, DWORD styleEx);
		/// @brief Converts an engine style to a Windows style.
		/// @param style Engine style.
		/// @return Windows style.
		[[nodiscard("Pure function")]]
		static constexpr DWORD ConvertToWindowsStyle(SurfaceStyle style) noexcept;
		/// @brief Converts an engine style to a Windows style ex.
		/// @param style Engine style.
		/// @return Windows style ex.
		[[nodiscard("Pure function")]]
		static constexpr DWORD ConvertToWindowsStyleEx(SurfaceStyle style) noexcept;
		/// @brief Converts a Windows style to a surface style.
		/// @param style Windows style.
		/// @return Surface style.
		[[nodiscard("Pure function")]]
		static constexpr SurfaceStyle ConvertToSurfaceStyle(DWORD style) noexcept;
		/// @brief Converts a Windows style ex to a surface style.
		/// @param style Windows style ex.
		/// @return Surface style.
		[[nodiscard("Pure function")]]
		static constexpr SurfaceStyle ConvertExToSurfaceStyle(DWORD style) noexcept;

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

		/// @brief Calls message observers.
		/// @param uMsg Message type.
		/// @param wParam WParam.
		/// @param lParam LParam.
		void ObserveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

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

		Math::Vector2<int> minimalClientSize; ///< Minimal client size.
		std::optional<Math::Rect<float>> cursorClippingRect; ///< Cursor clipping position and size.
		bool cursorVisible; ///< Is the cursor visible?
		bool windowActive; ///< Is the window active?
		bool windowInFocus; ///< Is the window in focus?
		bool erased; ///< Is the background erased? It's erased only once. A render system must paint the window after that.
		bool painted; ///< Is the window painted? It's painted only once. A render system must paint the window after that.

		std::shared_ptr<WindowClass> windowClass; ///< Window class.

		HWND windowHandle; ///< Window handle.

		std::unordered_map<UINT, std::vector<IMessageObserver*>> messageObservers; ///< Message observers.
		std::unordered_map<DWORD, std::vector<IRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		mutable std::string titleCache; ///< Title cache.
		std::vector<BYTE> rawInputCache; ///< Raw input cache.
	};
}

namespace PonyEngine::Surface::Windows
{
	SurfaceService::SurfaceService(Application::IApplicationContext& application, const std::shared_ptr<WindowClass>& windowClass, 
		const std::string_view title, const Math::Rect<std::int32_t>& clientRect, const Math::Vector2<std::int32_t>& minimalClientSize, const SurfaceStyle style,
		const bool showCursor, const std::optional<Math::Rect<float>>& cursorClippingRect) :
		application{&application},
		minimalClientSize(minimalClientSize),
		cursorClippingRect(cursorClippingRect ? std::optional(ClampRect(*cursorClippingRect)) : std::nullopt),
		cursorVisible{showCursor},
		windowActive{false},
		windowInFocus{false},
		erased{false},
		painted{false},
		windowClass(windowClass)
	{
		assert(this->windowClass && "The window class is nullptr!");

		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Calculating window rect.");
		const DWORD usualStyle = ConvertToWindowsStyle(style);
		const DWORD exStyle = ConvertToWindowsStyleEx(style) | WS_EX_APPWINDOW;
		const auto [clientPosition, clientSize] = CalculateWindowsRect(clientRect);
		const auto [windowPosition, windowSize] = AdjustRect(clientPosition, Math::Max(clientSize, minimalClientSize), usualStyle, exStyle);

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window... Window class: '0x{:X}'; Title: '{}'; Position: '{}'; Size: '{}'; Style: '{}'.", 
			windowClass->ClassHandle(), title, windowPosition, windowSize, style);
		windowHandle = CreateWindowExA(
			exStyle,
			reinterpret_cast<LPCSTR>(this->windowClass->ClassHandle()),
			title.data(),
			usualStyle,
			windowPosition.X(),
			windowPosition.Y(),
			windowSize.X(),
			windowSize.Y(),
			nullptr,
			nullptr,
			windowClass->ModuleHandle(),
			static_cast<IMessageHandler*>(this)
		);
		if (!windowHandle) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to create window. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating window done. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(windowHandle));

		PONY_LOG(this->application->Logger(), Log::LogType::Debug, "Show window.");
		const auto mainData = this->application->FindService<Application::Windows::IMainDataService>();
		assert(mainData && "The main data service is nullptr.");
		ShowWindow(windowHandle, mainData->ShowCommand());
	}

	SurfaceService::~SurfaceService() noexcept
	{
		if (IsWindow(windowHandle))
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
	}

	void SurfaceService::End()
	{
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenResolution() const
	{
		return static_cast<Math::Vector2<std::int32_t>>(GetResolution());
	}

	Math::Rect<std::int32_t> SurfaceService::ClientRect() const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return Math::Rect<std::int32_t>(static_cast<Math::Vector2<std::int32_t>>(minimalClientSize));
		}

		RECT rect;
		if (!GetClientRect(windowHandle, &rect)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get client rect. Error code: '0x{:X}'.", GetLastError()));
		}
		auto screenPosition = POINT{.x = rect.top, .y = rect.top};
		if (!::ClientToScreen(windowHandle, &screenPosition)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get client position. Error code: '0x{:X}'.", GetLastError()));
		}
		const auto position = Math::Vector2<int>(static_cast<int>(screenPosition.x), static_cast<int>(screenPosition.y));
		const auto size = Math::Vector2<int>(static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top));

		return CalculateEngineRect(position, size);
	}

	void SurfaceService::ClientRect(const Math::Rect<std::int32_t>& rect)
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return;
		}

		const auto [style, styleEx] = GetStyle();
		const auto [clientPosition, clientSize] = CalculateWindowsRect(rect);
		const auto [windowPosition, windowSize] = AdjustRect(clientPosition, clientSize, style, styleEx);
		if (!SetWindowPos(windowHandle, nullptr, windowPosition.X(), windowPosition.Y(), windowSize.X(), windowSize.Y(), SWP_NOZORDER)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set window rect. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	Math::Vector2<std::int32_t> SurfaceService::MinimalClientSize() const
	{
		return static_cast<Math::Vector2<std::int32_t>>(minimalClientSize);
	}

	void SurfaceService::MinimalClientSize(const Math::Vector2<std::int32_t>& size)
	{
		minimalClientSize = static_cast<Math::Vector2<int>>(size);
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
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return std::string_view();
		}

		SetLastError(DWORD{0});
		const int length = GetWindowTextLengthA(windowHandle);
		if (!length) [[unlikely]]
		{
			if (const DWORD errorCode = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get window title length. Error code: '0x{:X}'.", errorCode));
			}

			return std::string_view();
		}

		titleCache.clear();
		titleCache.reserve(length + 1);
		const int copied = GetWindowTextA(windowHandle, titleCache.data(), length + 1);
		if (!copied) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get window title. Error code: '0x{:X}'.", GetLastError()));
		}
		titleCache.resize(copied);

		return titleCache;
	}

	void SurfaceService::Title(const std::string_view title)
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return;
		}

		if (!SetWindowTextA(windowHandle, title.data())) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set window title. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	SurfaceStyle SurfaceService::Style() const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return SurfaceStyle::None;
		}

		const auto [style, styleEx] = GetStyle();
		return ConvertToSurfaceStyle(style) | ConvertExToSurfaceStyle(styleEx);
	}

	void SurfaceService::Style(const SurfaceStyle style)
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return;
		}

		SetStyle(ConvertToWindowsStyle(style), ConvertToWindowsStyleEx(style) | WS_EX_APPWINDOW);
	}

	Math::Vector2<std::int32_t> SurfaceService::CursorPosition() const
	{
		POINT position;
		if (!GetCursorPos(&position)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get cursor position. Error code: '0x{:X}'.", GetLastError()));
		}

		return CalculateEnginePoint(Math::Vector2<int>(position.x, position.y));
	}

	void SurfaceService::CursorPosition(const Math::Vector2<std::int32_t>& position)
	{
		if (!windowInFocus) [[unlikely]]
		{
			return;
		}

		const Math::Vector2<int> pos = CalculateWindowsPoint(position);
		if (!SetCursorPos(pos.X(), pos.Y())) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to set cursor position. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	bool SurfaceService::IsCursorVisible() const
	{
		return cursorVisible;
	}

	bool SurfaceService::IsCursorReallyVisible() const
	{
		CURSORINFO cursorInfo;
		cursorInfo.cbSize = sizeof(CURSORINFO);
		if (!GetCursorInfo(&cursorInfo)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get cursor visibility. Error code: '0x{:X}'.", GetLastError()));
		}

		return cursorInfo.flags & CURSOR_SHOWING;
	}

	void SurfaceService::ShowCursor(const bool visible)
	{
		if (cursorVisible == visible)
		{
			return;
		}

		cursorVisible = visible;

		if (windowInFocus)
		{
			::ShowCursor(visible);
		}
	}

	std::optional<Math::Rect<float>> SurfaceService::CursorClippingRect() const
	{
		return cursorClippingRect;
	}

	void SurfaceService::CursorClippingRect(const std::optional<Math::Rect<float>>& rect)
	{
		const std::optional<Math::Rect<float>> clippingRect = rect
			? std::optional(ClampRect(*rect))
			: std::nullopt;

		if (windowInFocus)
		{
			ClipCursor(clippingRect);
		}

		cursorClippingRect = clippingRect;
	}

	Math::Vector2<std::int32_t> SurfaceService::ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return Math::Vector2<std::int32_t>::Zero();
		}

		const Math::Vector2<int> windowsClient = CalculateWindowsPoint(clientPoint);
		auto screenPoint = POINT{.x = static_cast<LONG>(windowsClient.X()), .y = static_cast<LONG>(windowsClient.Y())};
		if (!::ClientToScreen(windowHandle, &screenPoint)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get screen point. Error code: '0x{:X}'.", GetLastError()));
		}

		return CalculateEnginePoint(Math::Vector2<int>(static_cast<int>(screenPoint.x), static_cast<int>(screenPoint.y)));
	}

	Math::Vector2<std::int32_t> SurfaceService::ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const
	{
		if (!IsWindow(windowHandle)) [[unlikely]]
		{
			return Math::Vector2<std::int32_t>::Zero();
		}

		const Math::Vector2<int> windowsScreen = CalculateWindowsPoint(screenPoint);
		auto clientPoint = POINT{.x = static_cast<LONG>(windowsScreen.X()), .y = static_cast<LONG>(windowsScreen.Y())};
		if (!::ScreenToClient(windowHandle, &clientPoint)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get client point. Error code: '0x{:X}'.", GetLastError()));
		}

		return CalculateEnginePoint(Math::Vector2<int>(static_cast<int>(clientPoint.x), static_cast<int>(clientPoint.y)));
	}

	HWND SurfaceService::Handle() noexcept
	{
		return windowHandle;
	}

	void SurfaceService::AddMessageObserver(IMessageObserver& observer, const UINT messageType)
	{
		std::vector<IMessageObserver*>& observers = messageObservers[messageType];
		assert(std::ranges::find(observers, &observer) == observers.cend() && "The observer has already been added.");
		observers.push_back(&observer);
	}

	void SurfaceService::AddMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		for (std::size_t i = 0uz; i < messageTypes.size(); ++i)
		{
			try
			{
				AddMessageObserver(observer, messageTypes[i]);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveMessageObserver(observer, messageTypes[i]);
				}

				throw;
			}
		}
	}

	void SurfaceService::RemoveMessageObserver(IMessageObserver& observer, const UINT messageType) noexcept
	{
		if (const auto position = messageObservers.find(messageType); position != messageObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove observer of '{}' message type but it hadn't been added.", messageType);
	}

	void SurfaceService::RemoveMessageObserver(IMessageObserver& observer, const std::span<const UINT> messageTypes) noexcept
	{
		for (const UINT messageType : messageTypes)
		{
			RemoveMessageObserver(observer, messageType);
		}
	}

	void SurfaceService::RemoveMessageObserver(IMessageObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (std::vector<IMessageObserver*>& observers : std::views::values(messageObservers))
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove message observer but it hadn't been added.");
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

		ObserveMessage(uMsg, wParam, lParam);

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
		case WM_MOVE:
			return ObserveMove(wParam, lParam);
		case WM_SIZE:
			return ObserveSize(wParam, lParam);
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

	Math::Vector2<std::int32_t> SurfaceService::CalculateEnginePoint(const Math::Vector2<int>& windowsPoint)
	{
		const auto screenCenter = static_cast<Math::Vector2<std::int32_t>>(GetScreenCenter());
		const auto point = static_cast<Math::Vector2<std::int32_t>>(windowsPoint);

		return Math::Vector2<std::int32_t>(point.X() - screenCenter.X(), screenCenter.Y() - point.Y());
	}

	Math::Vector2<int> SurfaceService::CalculateWindowsPoint(const Math::Vector2<std::int32_t>& enginePoint)
	{
		const Math::Vector2<int> screenCenter = GetScreenCenter();
		const auto point = static_cast<Math::Vector2<int>>(enginePoint);

		return Math::Vector2<int>(point.X() + screenCenter.X(), screenCenter.Y() - point.Y());
	}

	Math::Rect<std::int32_t> SurfaceService::CalculateEngineRect(const Math::Vector2<int>& position, const Math::Vector2<int>& size)
	{
		const auto extents = static_cast<Math::Vector2<std::int32_t>>(size) / 2;
		const Math::Vector2<std::int32_t> pos = CalculateEnginePoint(position);
		const auto center = Math::Vector2<std::int32_t>(pos.X() + extents.X(), pos.Y() - extents.Y());

		return Math::Rect<std::int32_t>(center, extents);
	}

	std::pair<Math::Vector2<int>, Math::Vector2<int>> SurfaceService::CalculateWindowsRect(const Math::Rect<std::int32_t>& rect)
	{
		const auto extents = static_cast<Math::Vector2<int>>(rect.Extents());
		const Math::Vector2<int> size = extents * 2;
		const Math::Vector2<int> center = CalculateWindowsPoint(rect.Center());
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
			throw std::runtime_error(Utility::SafeFormat("Failed to adjust window rect. Error code: '0x{:X}'.", GetLastError()));
		}

		return std::pair(
			Math::Vector2<int>(static_cast<int>(windowRect.left), static_cast<int>(windowRect.top)),
			Math::Vector2<int>(static_cast<int>(windowRect.right - windowRect.left), static_cast<int>(windowRect.bottom - windowRect.top))
		);
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

	Math::Vector2<int> SurfaceService::GetScreenCenter()
	{
		return GetResolution() / 2;
	}

	Math::Rect<float> SurfaceService::ClampRect(const Math::Rect<float>& rect) noexcept
	{
		const Math::Vector2<float> min = Math::Clamp(rect.Min(), Math::Vector2<float>::Negative(), Math::Vector2<float>::One());
		const Math::Vector2<float> max = Math::Clamp(rect.Max(), Math::Vector2<float>::Negative(), Math::Vector2<float>::One());
		const Math::Vector2<float> center = Math::Lerp(min, max, 0.5f);
		const Math::Vector2<float> extents = max - center;

		return Math::Rect<float>(center, extents);
	}

	std::pair<DWORD, DWORD> SurfaceService::GetStyle() const
	{
		SetLastError(DWORD{0});

		const auto style = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_STYLE));
		if (!style) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get window style. Error code: '0x{:X}'.", error));
			}
		}

		const auto styleEx = static_cast<DWORD>(GetWindowLongPtrA(windowHandle, GWL_EXSTYLE));
		if (!styleEx) [[unlikely]]
		{
			if (const auto error = GetLastError()) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to get extended window style. Error code: '0x{:X}'.", error));
			}
		}

		return std::pair(style, styleEx);
	}

	void SurfaceService::SetStyle(const DWORD style, const DWORD styleEx)
	{
		const Math::Rect<std::int32_t> rect = ClientRect();
		const auto [currentStyle, currentStyleEx] = GetStyle();

		SetLastError(DWORD{0});

		try
		{
			if (!SetWindowLongPtrA(windowHandle, GWL_STYLE, static_cast<LONG_PTR>(style))) [[unlikely]]
			{
				if (const auto error = GetLastError()) [[unlikely]]
				{
					throw std::runtime_error(Utility::SafeFormat("Failed to set window style. Error code: '0x{:X}'.", error));
				}
			}

			if (!SetWindowLongPtrA(windowHandle, GWL_EXSTYLE, static_cast<LONG_PTR>(styleEx))) [[unlikely]]
			{
				if (const auto error = GetLastError()) [[unlikely]]
				{
					throw std::runtime_error(Utility::SafeFormat("Failed to set extended window style. Error code: '0x{:X}'.", error));
				}
			}

			ClientRect(rect);
		}
		catch (...)
		{
			SetWindowLongPtrA(windowHandle, GWL_STYLE, static_cast<LONG_PTR>(currentStyle));
			SetWindowLongPtrA(windowHandle, GWL_EXSTYLE, static_cast<LONG_PTR>(currentStyleEx));

			throw;
		}
	}

	constexpr DWORD SurfaceService::ConvertToWindowsStyle(const SurfaceStyle style) noexcept
	{
		DWORD windowsStyle = 0;
		windowsStyle |= style == SurfaceStyle::None ? WS_POPUP : 0;
		windowsStyle |= Any(SurfaceStyle::Border, style) ? WS_BORDER : 0;
		windowsStyle |= Any(SurfaceStyle::Title, style) ? WS_CAPTION : 0;
		windowsStyle |= Any(SurfaceStyle::Close, style) ? WS_SYSMENU : 0;
		windowsStyle |= Any(SurfaceStyle::Maximize, style) ? WS_SYSMENU | WS_MAXIMIZEBOX : 0;
		windowsStyle |= Any(SurfaceStyle::Minimize, style) ? WS_SYSMENU | WS_MINIMIZEBOX : 0;
		windowsStyle |= Any(SurfaceStyle::Movable, style) ? WS_BORDER : 0;
		windowsStyle |= Any(SurfaceStyle::Resizable, style) ? WS_THICKFRAME : 0;

		return windowsStyle;
	}

	constexpr DWORD SurfaceService::ConvertToWindowsStyleEx(const SurfaceStyle style) noexcept
	{
		return Any(SurfaceStyle::AlwaysOnTop, style) ? WS_EX_TOPMOST : 0;
	}

	constexpr SurfaceStyle SurfaceService::ConvertToSurfaceStyle(const DWORD style) noexcept
	{
		auto surfaceStyle = SurfaceStyle::None;
		surfaceStyle |= style & (WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_SYSMENU) ? SurfaceStyle::Border : SurfaceStyle::None;
		surfaceStyle |= style & (WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_SYSMENU) ? SurfaceStyle::Title : SurfaceStyle::None;
		surfaceStyle |= style & WS_SYSMENU ? SurfaceStyle::Close : SurfaceStyle::None;
		surfaceStyle |= style & WS_MAXIMIZEBOX && style & WS_SYSMENU ? SurfaceStyle::Maximize : SurfaceStyle::None;
		surfaceStyle |= style & WS_MINIMIZEBOX && style & WS_SYSMENU ? SurfaceStyle::Minimize : SurfaceStyle::None;
		surfaceStyle |= style & (WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_SYSMENU) ? SurfaceStyle::Movable : SurfaceStyle::None;
		surfaceStyle |= style & WS_THICKFRAME ? SurfaceStyle::Resizable : SurfaceStyle::None;

		return surfaceStyle;
	}

	constexpr SurfaceStyle SurfaceService::ConvertExToSurfaceStyle(const DWORD style) noexcept
	{
		return style & WS_EX_TOPMOST ? SurfaceStyle::AlwaysOnTop : SurfaceStyle::None;
	}

	void SurfaceService::ClipCursor(const std::optional<Math::Rect<float>>& clippingRect)
	{
		if (clippingRect)
		{
			const Math::Rect<std::int32_t> clientRect = ClientRect();
			const Math::Vector2<int> clippingPosition = CalculateWindowsPoint(RelativeToAbsolute(clippingRect->Center(), clientRect.Extents()) + clientRect.Center());
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
				throw std::runtime_error(Utility::SafeFormat("Failed to clip cursor. Error code: '0x{:X}'.", GetLastError()));
			}
		}
		else
		{
			if (!::ClipCursor(nullptr)) [[unlikely]]
			{
				throw std::runtime_error(Utility::SafeFormat("Failed to free cursor. Error code: '0x{:X}'.", GetLastError()));
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
			throw std::runtime_error(Utility::SafeFormat("Failed to register/unregister raw input device. Usage page: '0x{:X}'; Usage: '0x{:X}'; Flags: '0x{:X}'; Window handle: '0x{:X}'. Error code: '0x{:X}'.", rid.usUsagePage, rid.usUsage, rid.dwFlags, reinterpret_cast<std::uintptr_t>(rid.hwndTarget), GetLastError()));
		}
	}

	DWORD SurfaceService::GetHidType(const RAWINPUT& input)
	{
		auto info = RID_DEVICE_INFO{.cbSize = sizeof(RID_DEVICE_INFO)};
		UINT size = sizeof(info);
		if (!GetRawInputDeviceInfoA(input.header.hDevice, RIDI_DEVICEINFO, &info, &size)) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to get hid device info. Error code: '0x{:X}'.", GetLastError()));
		}

		if (info.dwType != RIM_TYPEHID) [[unlikely]]
		{
			throw std::runtime_error("Wrong hid device!");
		}

		return Pack(info.hid.usUsagePage, info.hid.usUsage);
	}

	void SurfaceService::ObserveMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (const auto position = messageObservers.find(uMsg); position != messageObservers.cend())
		{
			for (IMessageObserver* const observer : position->second)
			{
				try
				{
					observer->Observe(uMsg, wParam, lParam);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On calling '{}' Windows message observer.", typeid(*observer).name());
				}
			}
		}
	}

	LRESULT SurfaceService::ObserveCreate(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		return 0;
	}

	LRESULT SurfaceService::ObserveDestroy(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		application->Stop();
		PostQuitMessage(0);

		return 0;
	}

	LRESULT SurfaceService::ObserveActivate(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowActive = wParam != WA_INACTIVE;
		return 0;
	}

	LRESULT SurfaceService::ObserveSetFocus(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowInFocus = true;

		if (!cursorVisible)
		{
			::ShowCursor(false);
		}
		if (cursorClippingRect)
		{
			try
			{
				ClipCursor(cursorClippingRect);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On clipping cursor on window activation.");
				cursorClippingRect = std::nullopt;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on clipping cursor on window activation.");
				cursorClippingRect = std::nullopt;
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveKillFocus(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		windowInFocus = false;

		if (!cursorVisible)
		{
			::ShowCursor(true);
		}
		if (cursorClippingRect)
		{
			try
			{
				ClipCursor(std::nullopt);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On freeing cursor on window deactivation.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on freeing cursor on window deactivation.");
			}
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveGetMinMaxInfo(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto [style, styleEx] = GetStyle();
		const auto [position, size] = AdjustRect(Math::Vector2<int>::Zero(), minimalClientSize, style, styleEx);

		const auto minMax = reinterpret_cast<MINMAXINFO*>(lParam);
		minMax->ptMinTrackSize.x = size.X();
		minMax->ptMinTrackSize.y = size.Y();

		return 0;
	}

	LRESULT SurfaceService::ObserveMove(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (cursorClippingRect)
		{
			ClipCursor(cursorClippingRect);
		}

		return 0;
	}

	LRESULT SurfaceService::ObserveSize(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (cursorClippingRect)
		{
			ClipCursor(cursorClippingRect);
		}

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
