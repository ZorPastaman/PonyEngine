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

export module PonyEngine.Screen.Windows.Detail:ScreenSystem;

import <cstdint>;

import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

import :Utility;

export namespace PonyEngine::Screen::Windows
{
	/// @brief Windows screen system.
	class ScreenSystem final : public Core::System, public IScreenSystem
	{
	public:
		/// @brief Creates a @p ScreenSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param screenParams Screen system parameters.
		[[nodiscard("Pure constructor")]]
		ScreenSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const ScreenSystemParams& screenParams) noexcept;
		ScreenSystem(const ScreenSystem&) = delete;
		ScreenSystem(ScreenSystem&&) = delete;

		virtual ~ScreenSystem() noexcept override = default;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> DisplayResolution() const noexcept override;

		ScreenSystem& operator =(const ScreenSystem&) = delete;
		ScreenSystem& operator =(ScreenSystem&&) = delete;

	private:
		PonyMath::Utility::Resolution<std::uint32_t> displayResolution; ///< Display resolution.
	};
}

namespace PonyEngine::Screen::Windows
{
	ScreenSystem::ScreenSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const ScreenSystemParams&) noexcept :
		System(engine, systemParams),
		displayResolution(GetDisplayResolution())
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Display resolution is '{}'.", displayResolution.ToString());
	}

	void ScreenSystem::Begin() noexcept
	{
	}

	void ScreenSystem::End() noexcept
	{
	}

	PonyMath::Utility::Resolution<std::uint32_t> ScreenSystem::DisplayResolution() const noexcept
	{
		return displayResolution;
	}
}
