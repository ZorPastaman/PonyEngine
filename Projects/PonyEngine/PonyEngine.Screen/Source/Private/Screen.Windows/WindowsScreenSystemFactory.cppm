/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Screen.Windows.Implementation:WindowsScreenSystemFactory;

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
		[[nodiscard("Pure constructor")]]
		WindowsScreenSystemFactory() noexcept = default;
		WindowsScreenSystemFactory(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory(WindowsScreenSystemFactory&&) = delete;

		~WindowsScreenSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::EngineSystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsScreenSystemFactory& operator =(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory& operator =(WindowsScreenSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Screen::WindowsScreenSystemFactory"; ///< Class name.
	};
}

namespace PonyEngine::Screen
{
	Core::SystemData WindowsScreenSystemFactory::Create(Core::IEngineContext& engine, const Core::EngineSystemParams&)
	{
		auto system = PonyBase::Memory::UniquePointer<WindowsScreenSystem>::Create(engine);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IScreenSystem, IWindowsScreenSystem>(*system);

		return Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<Core::IEngineSystem>(std::move(system)),
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
