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
		/// @param mainTitle Current main title.
		[[nodiscard("Pure constructor")]]
		TitleBar(IWindowSystemContext& windowSystem, std::string_view mainTitle);
		TitleBar(const TitleBar&) = delete;
		[[nodiscard("Pure constructor")]]
		TitleBar(TitleBar&& other) noexcept = default;

		~TitleBar() noexcept = default;

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

		TitleBar& operator =(const TitleBar&) = delete;
		TitleBar& operator =(TitleBar&& other) noexcept = default;

	private:
		/// @brief Update the window title.
		void UpdateWindowTitle() const;

		IWindowSystemContext* windowSystem; ///< Windows window system context.

		std::string mainTitle; ///< Window main title cache.
		std::string secondaryTitle; ///< Window title text cache.
	};
}

namespace PonyEngine::Window::Windows
{
	TitleBar::TitleBar(IWindowSystemContext& windowSystem, const std::string_view mainTitle) :
		windowSystem{&windowSystem},
		mainTitle(mainTitle)
	{
	}

	std::string_view TitleBar::MainTitle() const noexcept
	{
		return mainTitle;
	}

	void TitleBar::MainTitle(const std::string_view title)
	{
		mainTitle = title;
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "Main title set to '{}'.", mainTitle);
		UpdateWindowTitle();
	}

	std::string_view TitleBar::SecondaryTitle() const noexcept
	{
		return secondaryTitle;
	}

	void TitleBar::SecondaryTitle(const std::string_view title)
	{
		secondaryTitle = title;
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Secondary title set to '{}'.", secondaryTitle);
		UpdateWindowTitle();
	}

	void TitleBar::UpdateWindowTitle() const
	{
		if (!IsWindow(windowSystem->WindowHandle())) [[unlikely]]
		{
			return;
		}

		const std::string windowTitle = secondaryTitle.length() > 0 ? std::format("{} - {}", mainTitle, secondaryTitle) : mainTitle;

		if (!SetWindowTextW(windowSystem->WindowHandle(), PonyBase::Utility::ConvertToWideString(windowTitle).c_str())) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set new window title. Error code: '0x{:X}'.", GetLastError()));
		}

		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Window title set to '{}'.", windowTitle);
	}
}
