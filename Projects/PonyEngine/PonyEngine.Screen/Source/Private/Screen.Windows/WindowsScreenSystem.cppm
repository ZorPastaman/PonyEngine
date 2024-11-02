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

export module PonyEngine.Screen.Windows.Implementation:WindowsScreenSystem;

import <string_view>;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

export namespace PonyEngine::Screen
{
	class WindowsScreenSystem final : public Core::IEngineSystem, public IWindowsScreenSystem
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsScreenSystem() noexcept;
		WindowsScreenSystem(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem(WindowsScreenSystem&&) = delete;

		~WindowsScreenSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual Resolution<unsigned int> DisplayResolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsScreenSystem& operator =(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem& operator =(WindowsScreenSystem&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Screen::WindowsScreenSystem"; ///< Class name.

	private:
		Resolution<unsigned int> displayResolution;
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystem::WindowsScreenSystem() noexcept :
		displayResolution(PonyEngine::Screen::Resolution<unsigned int>(static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN)), static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN))))
	{
	}

	void WindowsScreenSystem::Begin()
	{
	}

	void WindowsScreenSystem::End()
	{
	}

	Resolution<unsigned int> WindowsScreenSystem::DisplayResolution() const noexcept
	{
		return displayResolution;
	}

	std::string_view WindowsScreenSystem::Name() const noexcept
	{
		return StaticName;
	}
}
