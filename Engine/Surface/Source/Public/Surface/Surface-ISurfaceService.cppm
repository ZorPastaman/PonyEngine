/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

export module PonyEngine.Surface:ISurfaceService;

import std;

import PonyEngine.Math;

import :IMessageObserver;
import :IRawInputObserver;
import :SurfaceStyle;

export namespace PonyEngine::Surface
{
#if PONY_WINDOWS
	namespace Windows
	{
		/// @brief Windows service surface.
		class ISurfaceService;
	}

	/// @brief Windows service surface.
	using INativeSurfaceService = Windows::ISurfaceService;
#else
#error "Unsupported platform!"
#endif

	/// @brief Surface service.
	class ISurfaceService
	{
		INTERFACE_BODY(ISurfaceService)

		/// @brief Gets a screen resolution.
		/// @return Screen resolution.
		[[nodiscard("Pure funtion")]]
		virtual Math::Vector2<std::int32_t> ScreenResolution() const = 0;
		/// @brief Gets a client rectangle.
		/// @return Client rectangle.
		/// @remark The reference point is a screen center.
		[[nodiscard("Pure function")]]
		virtual Math::Rect<std::int32_t> ClientRect() const = 0;
		/// @brief Sets a client rectangle.
		/// @param rect Client rectangle.
		/// @remark The reference point is a screen center.
		/// @remark If the platform doesn't support client rectangles, the function does nothing.
		virtual void ClientRect(const Math::Rect<std::int32_t>& rect) = 0;
		/// @brief Gets the minimal client size.
		/// @return Minimal client size.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> MinimalClientSize() const = 0;
		/// @brief Sets the minimal client size.
		/// @param size Minimal client size.
		/// @remark If the platform doesn't support surface rectangles, the function does nothing.
		virtual void MinimalClientSize(const Math::Vector2<std::int32_t>& size) = 0;

		/// @brief Checks if the surface is active.
		/// @return @a True if the surface is active; @a false otherwise.
		[[nodiscard("Pure funtion")]]
		virtual bool IsActive() const = 0;
		/// @brief Checks if the surface is in focus.
		/// @return @a True if the surface is in focus; @a false otherwise.
		[[nodiscard("Pure funtion")]]
		virtual bool IsInFocus() const = 0;

		/// @brief Gets a client title.
		/// @return Client title.
		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const = 0;
		/// @brief Sets a client title.
		/// @param title Client title.
		/// @remark If the platform doesn't support client titles, the function does nothing.
		virtual void Title(std::string_view title) = 0;

		/// @brief Gets a surface style.
		/// @return Surface style.
		[[nodiscard("Pure function")]]
		virtual SurfaceStyle Style() const = 0;
		/// @brief Sets a surface style.
		/// @param style Surface style.
		/// @rematk If the platform doesn't support a style flag, it'll be ignored.
		virtual void Style(SurfaceStyle style) = 0;

		/// @brief Gets a cursor position.
		/// @return Cursor position in screen coordinates.
		/// @remark The reference point is a screen center.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> CursorPosition() const = 0;
		/// @brief Sets a cursor position.
		/// @param position Cursor position in screen coordinates.
		/// @remark The reference point is a screen center.
		/// @note If the window isn't active, the function does nothing.
		virtual void CursorPosition(const Math::Vector2<std::int32_t>& position) = 0;
		/// @brief Gets if a cursor is visible.
		/// @return @a True if a cursor is visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCursorVisible() const = 0;
		/// @brief Gets if a cursor is really visible.
		/// @details Some platforms control the cursor visibility by a value counter. The surface service by itself adds either -1 or 0.
		///          This function checks the real visibility state.
		/// @return @a True if a cursor is visible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCursorReallyVisible() const = 0;
		/// @brief Shows or hides a cursor.
		/// @param visible If it's @a true, shows a cursor; otherwise, hides it.
		/// @remark if the platform doesn't support cursors, the function does nothing.
		virtual void ShowCursor(bool visible) = 0;
		/// @brief Gets a cursor clipping rectangle.
		/// @return Cursor clipping rectangle in client coordinates. If it's @a std::nullopt, the cursor isn't clipped. The range is [-1, 1].
		/// @remark The reference point is a screen center.
		[[nodiscard("Pure function")]]
		virtual std::optional<Math::Rect<float>> CursorClippingRect() const = 0;
		/// @brief Sets a cursor clipping rectangle.
		/// @param rect Cursor clipping rectangle in client coordinates. If it's @a std::nullopt, the cursor isn't clipped. The range is [-1, 1].
		/// @remark The reference point is a screen center.
		/// @remark if the platform doesn't support cursors, the function does nothing.
		virtual void CursorClippingRect(const std::optional<Math::Rect<float>>& rect) = 0;

		/// @brief Converts the client point to a screen point.
		/// @param clientPoint Client point.
		/// @return Screen point.
		/// @remark The reference point is a screen center.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ClientToScreen(const Math::Vector2<std::int32_t>& clientPoint) const = 0;
		/// @brief Converts the screen point to a client point.
		/// @param screenPoint Screen point.
		/// @return Client point.
		/// @remark The reference point is a screen center.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> ScreenToClient(const Math::Vector2<std::int32_t>& screenPoint) const = 0;

		/// @brief Gets the native service surface.
		/// @return Native service surface.
		[[nodiscard("Pure function")]]
		INativeSurfaceService& Native() noexcept;
		/// @brief Gets the native service surface.
		/// @return Native service surface.
		[[nodiscard("Pure function")]]
		const INativeSurfaceService& Native() const noexcept;
		/// @brief Gets the native service surface.
		/// @return Native service surface.
		[[nodiscard("Pure function")]]
		INativeSurfaceService* NativePtr() noexcept;
		/// @brief Gets the native service surface.
		/// @return Native service surface.
		[[nodiscard("Pure function")]]
		const INativeSurfaceService* NativePtr() const noexcept;
	};
}

#if PONY_WINDOWS
export namespace PonyEngine::Surface::Windows
{
	/// @brief Windows surface service.
	class ISurfaceService : public Surface::ISurfaceService
	{
		INTERFACE_BODY(ISurfaceService)

		/// @brief Gets the native handle.
		/// @return Native handle.
		[[nodiscard("Pure function")]]
		virtual HWND Handle() noexcept = 0;

		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageType Message type to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) = 0;
		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageTypes Message types to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) = 0;
		/// @brief Removes the message observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param messageType Message type to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept = 0;
		/// @brief Removes the message observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param messageTypes Message types to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept = 0;
		/// @brief Removes the message observer from all the message types.
		/// @param observer Observer to remove.
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept = 0;

		/// @brief Adds the raw input observer.
		/// @param observer Observer to add.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		virtual void AddRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) = 0;
		/// @brief Adds the raw input observer.
		/// @param observer Observer to add.
		/// @param rawInputUsages Pairs of usage page and usage.
		virtual void AddRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) = 0;
		/// @brief Removes the raw input observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) noexcept = 0;
		/// @brief Removes the raw input observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param rawInputUsages Pairs of usage page and usage.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept = 0;
		/// @brief Removes the raw input observer from all the message types.
		/// @param observer Observer to remove.
		virtual void RemoveRawInputObserver(IRawInputObserver& observer) noexcept = 0;
	};
}
#endif

namespace PonyEngine::Surface
{
	INativeSurfaceService& ISurfaceService::Native() noexcept
	{
		return static_cast<INativeSurfaceService&>(*this);
	}

	const INativeSurfaceService& ISurfaceService::Native() const noexcept
	{
		return static_cast<const INativeSurfaceService&>(*this);
	}

	INativeSurfaceService* ISurfaceService::NativePtr() noexcept
	{
		return static_cast<INativeSurfaceService*>(this);
	}

	const INativeSurfaceService* ISurfaceService::NativePtr() const noexcept
	{
		return static_cast<const INativeSurfaceService*>(this);
	}
}
