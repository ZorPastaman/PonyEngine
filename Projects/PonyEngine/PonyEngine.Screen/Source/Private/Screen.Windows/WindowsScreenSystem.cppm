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

import PonyEngine.Core;
import PonyEngine.Screen;

export namespace PonyEngine::Screen
{
	class WindowsScreenSystem final : public Core::ISystem, public IScreenSystem
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit WindowsScreenSystem(Core::IEngine& engine) noexcept;
		WindowsScreenSystem(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem(WindowsScreenSystem&&) = delete;

		~WindowsScreenSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual Resolution<unsigned int> DisplayResolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsScreenSystem& operator =(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem& operator =(WindowsScreenSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Screen::WindowsScreenSystem"; ///< Class name.

	private:
		Resolution<unsigned int> displayResolution;
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystem::WindowsScreenSystem(Core::IEngine&) noexcept :
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

	const char* WindowsScreenSystem::Name() const noexcept
	{
		return StaticName;
	}
}
