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

export module PonyEngine.Window.Windows.Detail:WindowsCursor;

import <array>;
import <cstdint>;
import <exception>;
import <optional>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Shape;

import PonyDebug.Log;

import PonyEngine.Window.Windows;

import :IWindowsWindowSystemContext;
import :WindowsUtility;

export namespace PonyEngine::Window
{
	/// @brief Windows cursor.
	class WindowsCursor final : public IWindowsCursor, private IWindowsMessageObserver
	{
	public:
		/// @brief Creates a @p WindowsCursor.
		/// @param windowSystem Windows window system context.
		/// @param params Cursor parameters.
		[[nodiscard("Pure constructor")]]
		WindowsCursor(IWindowsWindowSystemContext& windowSystem, const CursorParams& params) noexcept;
		WindowsCursor(const WindowsCursor&) = delete;
		WindowsCursor(WindowsCursor&&) = delete;

		~WindowsCursor() noexcept;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Vector2<std::int32_t> CursorPosition() const override;
		virtual void CursorPosition(const PonyMath::Core::Vector2<std::int32_t>& position) override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible() const noexcept override;
		virtual void IsVisible(bool isVisible) override;

		[[nodiscard("Pure function")]]
		virtual std::optional<PonyMath::Shape::Rect<float>> ClippingRect() const noexcept override;
		virtual void ClippingRect(const std::optional<PonyMath::Shape::Rect<float>>& clippingRect) override;

		WindowsCursor& operator =(const WindowsCursor&) = delete;
		WindowsCursor& operator =(WindowsCursor&&) = delete;

	private:
		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		/// @brief Observes activate command.
		/// @param wParam WParam.
		void ObserveActivate(WPARAM wParam);

		/// @brief Updates a cursor clipping.
		void UpdateClipping() const;

		IWindowsWindowSystemContext* windowSystem; ///< Windows window system context.

		std::optional<PonyMath::Shape::Rect<float>> clipping; ///< Cursor clipping area.

		bool visible; ///< Is the cursor visible?
		bool active; ///< Is the window active?
	};
}

namespace PonyEngine::Window
{
	WindowsCursor::WindowsCursor(IWindowsWindowSystemContext& windowSystem, const CursorParams& params) noexcept :
		windowSystem{&windowSystem},
		clipping(params.cursorClipping),
		visible{true},
		active{GetForegroundWindow() == this->windowSystem->WindowHandle()}
	{
		this->windowSystem->MessagePump().AddMessageObserver(*this, std::array<UINT, 3> { WM_ACTIVATE, WM_MOVE, WM_SIZE });

		if (params.cursorPosition)
		{
			const auto rect = static_cast<PonyMath::Shape::Rect<float>>(this->windowSystem->WindowClientRect());
			const auto cursorPosition = static_cast<PonyMath::Core::Vector2<std::int32_t>>(rect.Unnormalize(params.cursorPosition.value()));
			CursorPosition(cursorPosition);
		}

		IsVisible(params.visible);
		UpdateClipping();
	}

	WindowsCursor::~WindowsCursor() noexcept
	{
		if (!visible)
		{
			ShowCursor(true);
		}
		ClipCursor(nullptr);

		try
		{
			windowSystem->MessagePump().RemoveMessageObserver(*this);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(windowSystem->Logger(), e, "On removing message observer.");
		}
	}

	PonyMath::Core::Vector2<std::int32_t> WindowsCursor::CursorPosition() const
	{
		POINT position;
		if (!GetCursorPos(&position)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get cursor position. Error code: '0x{:X}'.", GetLastError()));
		}

		return PonyMath::Core::Vector2<std::int32_t>(static_cast<std::int32_t>(position.x), static_cast<std::int32_t>(position.y));
	}

	void WindowsCursor::CursorPosition(const PonyMath::Core::Vector2<std::int32_t>& position)
	{
		if (!SetCursorPos(static_cast<int>(position.X()), static_cast<int>(position.Y()))) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set cursor position. Error code: '0x{:X}'.", GetLastError()));
		}

		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Cursor position set to '{}'.", position.ToString());
	}

	bool WindowsCursor::IsVisible() const noexcept
	{
		return visible;
	}

	void WindowsCursor::IsVisible(const bool isVisible)
	{
		if (isVisible == visible)
		{
			return;
		}

		visible = isVisible;
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Cursor visibility set to '{}'.", visible);

		if (active)
		{
			ShowCursor(visible);
		}
	}

	std::optional<PonyMath::Shape::Rect<float>> WindowsCursor::ClippingRect() const noexcept
	{
		return clipping;
	}

	void WindowsCursor::ClippingRect(const std::optional<PonyMath::Shape::Rect<float>>& clippingRect)
	{
		if (clipping == clippingRect)
		{
			return;
		}

		clipping = clippingRect;
		UpdateClipping();
	}

	void WindowsCursor::Observe(const UINT uMsg, const WPARAM wParam, const LPARAM)
	{
		switch (uMsg)
		{
		case WM_ACTIVATE:
			ObserveActivate(wParam);
			break;
		case WM_MOVE:
		case WM_SIZE:
			UpdateClipping();
			break;
		default: [[unlikely]]
			assert(false && "The wrong message type has been received.");
			break;
		}
	}

	void WindowsCursor::ObserveActivate(const WPARAM wParam)
	{
		const bool isActive = wParam != WA_INACTIVE;
		if (active == isActive)
		{
			return;
		}

		active = isActive;

		if (!visible)
		{
			ShowCursor(!active);
		}

		UpdateClipping();
	}

	void WindowsCursor::UpdateClipping() const
	{
		if (active && clipping)
		{
			const RECT rect = ConvertToWindowsRect(static_cast<PonyMath::Shape::Rect<float>>(windowSystem->WindowClientRect()).Unnormalize(clipping.value()));
			if (!ClipCursor(&rect)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to clip cursor. Error code: '0x{:X}'.", GetLastError()));
			}
		}
		else
		{
			if (!ClipCursor(nullptr)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to free cursor. Error code: '0x{:X}'.", GetLastError()));
			}
		}
	}
}
