/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Screen.Windows.Detail:WindowsScreenSystem;

import <cstdint>;

import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

import :Utility;

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

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> DisplayResolution() const noexcept override;

		WindowsScreenSystem& operator =(const WindowsScreenSystem&) = delete;
		WindowsScreenSystem& operator =(WindowsScreenSystem&&) = delete;

	private:
		PonyMath::Utility::Resolution<std::uint32_t> displayResolution; ///< Display resolution.
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystem::WindowsScreenSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsScreenSystemParams&) noexcept :
		System(engine, systemParams),
		displayResolution(GetDisplayResolution())
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Display resolution is '{}'.", displayResolution.ToString());
	}

	void WindowsScreenSystem::Begin() noexcept
	{
	}

	void WindowsScreenSystem::End() noexcept
	{
	}

	PonyMath::Utility::Resolution<std::uint32_t> WindowsScreenSystem::DisplayResolution() const noexcept
	{
		return displayResolution;
	}
}
