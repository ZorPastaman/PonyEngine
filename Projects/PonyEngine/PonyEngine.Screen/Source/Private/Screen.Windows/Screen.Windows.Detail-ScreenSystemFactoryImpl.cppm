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
import <typeinfo>;
import <utility>;

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
		virtual const std::type_info& SystemType() const noexcept override;

		ScreenSystemFactoryImpl& operator =(const ScreenSystemFactoryImpl&) = delete;
		ScreenSystemFactoryImpl& operator =(ScreenSystemFactoryImpl&&) = delete;

	private:
		ScreenSystemParams screenSystemParams; ///< Screen system parameters.

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
		auto system = std::make_unique<ScreenSystem>(engine, params, screenSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<Screen::IScreenSystem, IScreenSystem>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::System>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	const std::type_info& ScreenSystemFactoryImpl::SystemType() const noexcept
	{
		return typeid(ScreenSystem);
	}
}
