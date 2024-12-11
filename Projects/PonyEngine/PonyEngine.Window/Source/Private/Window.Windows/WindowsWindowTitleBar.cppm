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

export module PonyEngine.Window.Windows.Detail:WindowsWindowTitleBar;

import <format>;
import <string>;
import <string_view>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Window.Windows;

import :IWindowsWindowSystemContext;

export namespace PonyEngine::Window
{
	/// @brief Windows window title bar.
	class WindowsWindowTitleBar final : public IWindowsWindowTitleBar
	{
	public:
		/// @brief Creates a @p WindowsWindowTitleBar.
		/// @param windowSystem Window system context.
		/// @param mainTitle Current main title.
		[[nodiscard("Pure constructor")]]
		WindowsWindowTitleBar(IWindowsWindowSystemContext& windowSystem, std::string_view mainTitle);
		WindowsWindowTitleBar(const WindowsWindowTitleBar&) = delete;
		[[nodiscard("Pure constructor")]]
		WindowsWindowTitleBar(WindowsWindowTitleBar&& other) noexcept = default;

		~WindowsWindowTitleBar() noexcept = default;

		/// @brief Gets the main title.
		/// @return Main title.
		[[nodiscard("Pure function")]]
		virtual std::string_view MainTitle() const noexcept override;
		/// @brief Sets the main title.
		/// @param title Main title to set.
		virtual void MainTitle(std::string_view title) override;

		/// @brief Gets the secondary title.
		/// @return Secondary title.
		[[nodiscard("Pure function")]]
		virtual std::string_view SecondaryTitle() const noexcept override;
		/// @brief Sets the secondary title.
		/// @param title Secondary title to set.
		virtual void SecondaryTitle(std::string_view title) override;

		WindowsWindowTitleBar& operator =(const WindowsWindowTitleBar&) = delete;
		WindowsWindowTitleBar& operator =(WindowsWindowTitleBar&& other) noexcept = default;

	private:
		/// @brief Update the window title.
		void UpdateWindowTitle() const;

		IWindowsWindowSystemContext* windowSystem; ///< Windows window system context.

		std::string mainTitle; ///< Window main title cache.
		std::string secondaryTitle; ///< Window title text cache.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowTitleBar::WindowsWindowTitleBar(IWindowsWindowSystemContext& windowSystem, const std::string_view mainTitle) :
		windowSystem{&windowSystem},
		mainTitle(mainTitle)
	{
	}

	std::string_view WindowsWindowTitleBar::MainTitle() const noexcept
	{
		return mainTitle;
	}

	void WindowsWindowTitleBar::MainTitle(const std::string_view title)
	{
		mainTitle = title;
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "Main title set to '{}'.", mainTitle);
		UpdateWindowTitle();
	}

	std::string_view WindowsWindowTitleBar::SecondaryTitle() const noexcept
	{
		return secondaryTitle;
	}

	void WindowsWindowTitleBar::SecondaryTitle(const std::string_view title)
	{
		secondaryTitle = title;
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "Secondary title set to '{}'.", secondaryTitle);
		UpdateWindowTitle();
	}

	void WindowsWindowTitleBar::UpdateWindowTitle() const
	{
		const std::string titleToSet = secondaryTitle.length() > 0 ? std::format("{} - {}", mainTitle, secondaryTitle) : mainTitle;

		if (!SetWindowTextW(windowSystem->WindowHandle(), PonyBase::Utility::ConvertToWideString(titleToSet).c_str()))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set new window title. Error code: '0x{:X}'.", GetLastError()));
		}

		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "Window title set to '{}'.", titleToSet);
	}
}
