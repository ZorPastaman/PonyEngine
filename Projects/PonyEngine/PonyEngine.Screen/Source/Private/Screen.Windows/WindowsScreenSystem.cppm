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

export module PonyEngine.Screen.Windows.Implementation:WindowsScreenSystem;

import <string_view>;

import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system.
	class WindowsScreenSystem final : public Core::IEngineSystem, public IWindowsScreenSystem
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit WindowsScreenSystem(Core::IEngineContext& engine) noexcept;
		WindowsScreenSystem(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem(WindowsScreenSystem&&) = delete;

		~WindowsScreenSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<unsigned int> DisplayResolution() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsScreenSystem& operator =(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem& operator =(WindowsScreenSystem&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Screen::WindowsScreenSystem"; ///< Class name.

	private:
		PonyMath::Utility::Resolution<unsigned int> displayResolution; ///< Display resolution.

		Core::IEngineContext* engine; ///< Engine.
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystem::WindowsScreenSystem(Core::IEngineContext& engine) noexcept :
		displayResolution(),
		engine{&engine}
	{
	}

	void WindowsScreenSystem::Begin()
	{
		displayResolution.Width() = static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN));
		displayResolution.Height() = static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN));
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Display resolution is '{}'.", displayResolution.ToString());
	}

	void WindowsScreenSystem::End()
	{
	}

	PonyMath::Utility::Resolution<unsigned int> WindowsScreenSystem::DisplayResolution() const noexcept
	{
		return displayResolution;
	}

	std::string_view WindowsScreenSystem::Name() const noexcept
	{
		return StaticName;
	}
}
