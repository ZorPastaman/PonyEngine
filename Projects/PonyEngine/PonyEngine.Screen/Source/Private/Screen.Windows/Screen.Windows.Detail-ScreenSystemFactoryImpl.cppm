/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Detail:ScreenSystemFactoryImpl;

import <memory>;

import PonyBase.Utility;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

import :ScreenSystem;

export namespace PonyEngine::Screen::Windows
{
	/// @brief Windows screen system factory.
	class ScreenSystemFactoryImpl final : public ScreenSystemFactory
	{
	public:
		/// @brief Creates a @p ScreenSystemFactoryImpl.
		/// @param application Application context.
		/// @param factoryParams Windows screen system factory parameters.
		/// @param systemParams Windows screen system parameters.
		[[nodiscard("Pure constructor")]]
		ScreenSystemFactoryImpl(Core::IApplicationContext& application, const ScreenSystemFactoryParams& factoryParams, const ScreenSystemParams& systemParams) noexcept;
		ScreenSystemFactoryImpl(const ScreenSystemFactoryImpl&) = delete;
		ScreenSystemFactoryImpl(ScreenSystemFactoryImpl&&) = delete;

		virtual ~ScreenSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const Core::ISystemInfo& SystemInfo() const noexcept override;

		ScreenSystemFactoryImpl& operator =(const ScreenSystemFactoryImpl&) = delete;
		ScreenSystemFactoryImpl& operator =(ScreenSystemFactoryImpl&&) = delete;

	private:
		ScreenSystemParams screenSystemParams; ///< Screen system parameters.
		Core::SystemInfo<ScreenSystem, Screen::IScreenSystem, IScreenSystem> screenSystemInfo;

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Screen::Windows
{
	ScreenSystemFactoryImpl::ScreenSystemFactoryImpl(Core::IApplicationContext& application, const ScreenSystemFactoryParams&, const ScreenSystemParams& systemParams) noexcept :
		screenSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData ScreenSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		return screenSystemInfo.CreateSystemData(std::make_unique<ScreenSystem>(engine, params, screenSystemParams));
	}

	const Core::ISystemInfo& ScreenSystemFactoryImpl::SystemInfo() const noexcept
	{
		return screenSystemInfo;
	}
}
