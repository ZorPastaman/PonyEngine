/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Screen.Windows.Implementation:WindowsScreenSystemFactory;

import <utility>;

import PonyEngine.Core.Factory;

import :WindowsScreenSystem;

export namespace PonyEngine::Screen
{
	class WindowsScreenSystemFactory final : public Core::ISystemFactory, public Core::ISystemDestroyer
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit WindowsScreenSystemFactory(Core::IApplication& application) noexcept;
		WindowsScreenSystemFactory(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory(WindowsScreenSystemFactory&&) = delete;

		~WindowsScreenSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngine& engine, const Core::SystemParams& params) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsScreenSystemFactory& operator =(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory& operator =(WindowsScreenSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Screen::WindowsScreenSystemFactory"; ///< Class name.
	};
}

namespace PonyEngine::Screen
{
	WindowsScreenSystemFactory::WindowsScreenSystemFactory(Core::IApplication&) noexcept
	{
	}

	Core::SystemData WindowsScreenSystemFactory::Create(Core::IEngine& engine, const Core::SystemParams&)
	{
		const auto system = new WindowsScreenSystem(engine);
		const auto deleter = Core::SystemDeleter(*this);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IScreenSystem>(*system);

		return Core::SystemData
		{
			.system = Core::SystemUniquePtr(system, deleter),
			.tickableSystem = nullptr,
			.publicInterfaces = std::move(interfaces)
		};
	}

	void WindowsScreenSystemFactory::Destroy(Core::ISystem* system) noexcept
	{
		assert((dynamic_cast<WindowsScreenSystem*>(system) && "Tried to destroy a system of the wrong type."));

		delete static_cast<WindowsScreenSystem*>(system);
	}

	const char* WindowsScreenSystemFactory::SystemName() const noexcept
	{
		return WindowsScreenSystem::StaticName;
	}

	const char* WindowsScreenSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
