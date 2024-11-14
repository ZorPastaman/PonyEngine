/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Impl:WindowsScreenSystemFactory;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.Memory;
import PonyBase.ObjectUtility;

import PonyEngine.Core.Factory;
import PonyEngine.Screen.Windows.Factory;

import :WindowsScreenSystem;

export namespace PonyEngine::Screen
{
	/// @brief Windows screen system factory.
	class WindowsScreenSystemFactory final : public IWindowsScreenSystemFactory
	{
	public:
		/// @brief Creates a @p WindowsScreenSystemFactory.
		/// @param application Application context.
		/// @param factoryParams Windows screen system factory parameters.
		/// @param systemParams Windows screen system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsScreenSystemFactory(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams& factoryParams, const WindowsScreenSystemParams& systemParams) noexcept;
		WindowsScreenSystemFactory(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory(WindowsScreenSystemFactory&&) = delete;

		~WindowsScreenSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsScreenSystemFactory& operator =(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory& operator =(WindowsScreenSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Screen::WindowsScreenSystemFactory"; ///< Class name.

	private:
		WindowsScreenSystemParams screenSystemParams; ///< Screen system parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystemFactory::WindowsScreenSystemFactory(Core::IApplicationContext& application, const WindowsScreenSystemFactoryParams&, const WindowsScreenSystemParams& systemParams) noexcept :
		screenSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowsScreenSystemFactory::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
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

	std::string_view WindowsScreenSystemFactory::SystemName() const noexcept
	{
		return WindowsScreenSystem::StaticName;
	}

	std::string_view WindowsScreenSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
