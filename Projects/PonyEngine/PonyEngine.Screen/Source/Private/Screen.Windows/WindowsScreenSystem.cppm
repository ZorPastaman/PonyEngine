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

export module PonyEngine.Screen.Windows.Detail:WindowsScreenSystem;

import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system.
	class WindowsScreenSystem final : public Core::System, public IWindowsScreenSystem
	{
	public:
		/// @brief Creates a @p WindowsScreenSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param screenParams Screen system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsScreenSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsScreenSystemParams& screenParams) noexcept;
		WindowsScreenSystem(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem(WindowsScreenSystem&&) = delete;

		virtual ~WindowsScreenSystem() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<unsigned int> DisplayResolution() const noexcept override;

		WindowsScreenSystem& operator =(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem& operator =(WindowsScreenSystem&&) = delete;

	private:
		PonyMath::Utility::Resolution<unsigned int> displayResolution; ///< Display resolution.
	};
}

namespace PonyEngine::Screen
{
	/// @brief Gets a current display resolution.
	/// @return Display resolution.
	[[nodiscard("Pure function")]]
	PonyMath::Utility::Resolution<unsigned int> GetDisplayResolution() noexcept;

	WindowsScreenSystem::WindowsScreenSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsScreenSystemParams&) noexcept :
		System(engine, systemParams),
		displayResolution(GetDisplayResolution())
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Display resolution is '{}'.", displayResolution.ToString());
	}

	void WindowsScreenSystem::Begin()
	{
	}

	void WindowsScreenSystem::End()
	{
	}

	PonyMath::Utility::Resolution<unsigned int> WindowsScreenSystem::DisplayResolution() const noexcept
	{
		return displayResolution;
	}

	PonyMath::Utility::Resolution<unsigned int> GetDisplayResolution() noexcept
	{
		PonyMath::Utility::Resolution<unsigned int> resolution;
		resolution.Width() = static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN));
		resolution.Height() = static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN));

		return resolution;
	}
}
