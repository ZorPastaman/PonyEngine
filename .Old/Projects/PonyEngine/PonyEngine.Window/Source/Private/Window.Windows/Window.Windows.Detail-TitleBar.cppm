/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Detail:TitleBar;

import <format>;
import <string>;
import <string_view>;

import PonyBase.Utility;

import PonyDebug.Log;

import PonyEngine.Window.Windows;

import :IWindowSystemContext;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows window title bar.
	class TitleBar final : public ITitleBar
	{
	public:
		/// @brief Creates a @p TitleBar.
		/// @param windowSystem Window system context.
		/// @param title Title.
		[[nodiscard("Pure constructor")]]
		TitleBar(IWindowSystemContext& windowSystem, std::string_view title);
		TitleBar(const TitleBar&) = delete;
		[[nodiscard("Pure constructor")]]
		TitleBar(TitleBar&& other) noexcept = default;

		~TitleBar() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::string_view Title() const noexcept override;
		virtual void Title(std::string_view title) override;

		TitleBar& operator =(const TitleBar&) = delete;
		TitleBar& operator =(TitleBar&& other) noexcept = default;

	private:
		IWindowSystemContext* windowSystem; ///< Windows window system context.

		std::string title; ///< Window main title cache.
	};
}

namespace PonyEngine::Window::Windows
{
	TitleBar::TitleBar(IWindowSystemContext& windowSystem, const std::string_view title) :
		windowSystem{&windowSystem},
		title(title)
	{
	}

	std::string_view TitleBar::Title() const noexcept
	{
		return title;
	}

	void TitleBar::Title(const std::string_view title)
	{
		if (!IsWindow(windowSystem->WindowHandle())) [[unlikely]]
		{
			throw std::logic_error("Window is destroyed.");
		}

		auto newTitle = std::string(title);

		if (!SetWindowTextW(windowSystem->WindowHandle(), PonyBase::Utility::ConvertToWideString(newTitle).c_str())) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set new window title. Error code: '0x{:X}'.", GetLastError()));
		}

		this->title = std::move(newTitle);
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Window title set to '{}'.", this->title);
	}
}
