/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Detail:WindowsScreenSystemFactoryImpl;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

import PonyEngine.Core;
import PonyEngine.Screen.Windows;

import :WindowsScreenSystem;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system factory.
	class WindowsScreenSystemFactoryImpl final : public ScreenSystemFactory
	{
	public:
		/// @brief Creates a @p WindowsScreenSystemFactoryImpl.
		/// @param application Application context.
		/// @param factoryParams Windows screen system factory parameters.
		/// @param systemParams Windows screen system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsScreenSystemFactoryImpl(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams& factoryParams, const WindowsScreenSystemParams& systemParams) noexcept;
		WindowsScreenSystemFactoryImpl(const WindowsScreenSystemFactoryImpl&) = delete;
		WindowsScreenSystemFactoryImpl(WindowsScreenSystemFactoryImpl&&) = delete;

		virtual ~WindowsScreenSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsScreenSystemFactoryImpl& operator =(const WindowsScreenSystemFactoryImpl&) = delete;
		WindowsScreenSystemFactoryImpl& operator =(WindowsScreenSystemFactoryImpl&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Screen::WindowsScreenSystemFactoryImpl"; ///< Class name.

	private:
		WindowsScreenSystemParams screenSystemParams; ///< Screen system parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystemFactoryImpl::WindowsScreenSystemFactoryImpl(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams&, const WindowsScreenSystemParams& systemParams) noexcept :
		screenSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowsScreenSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		auto system = std::make_unique<WindowsScreenSystem>(engine, params, screenSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IScreenSystem, IWindowsScreenSystem>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::System>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	std::string_view WindowsScreenSystemFactoryImpl::SystemName() const noexcept
	{
		return WindowsScreenSystem::StaticName;
	}

	std::string_view WindowsScreenSystemFactoryImpl::Name() const noexcept
	{
		return StaticName;
	}
}
