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
import PonyEngine.Screen.Windows.Factory;

import :WindowsScreenSystem;

export namespace PonyEngine::Screen
{
	class WindowsScreenSystemFactory final : public IWindowsScreenSystemFactory, public Core::ISystemDestroyer
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit WindowsScreenSystemFactory(Core::IApplication& application) noexcept;
		WindowsScreenSystemFactory(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory(WindowsScreenSystemFactory&&) = delete;

		~WindowsScreenSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngine& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual WindowsScreenSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowsScreenSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(Core::IEngineSystem* system) const noexcept override;
		virtual void Destroy(Core::IEngineSystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsScreenSystemFactory& operator =(const WindowsScreenSystemFactory&) = delete;
		WindowsScreenSystemFactory& operator =(WindowsScreenSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Screen::WindowsScreenSystemFactory"; ///< Class name.

	private:
		WindowsScreenSystemParams systemParams;
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
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IScreenSystem>(*system);

		return Core::SystemData
		{
			.system = Core::SystemUniquePtr<Core::IEngineSystem>(*system, *this),
			.publicInterfaces = std::move(interfaces)
		};
	}

	WindowsScreenSystemParams& WindowsScreenSystemFactory::SystemParams() noexcept
	{
		return systemParams;
	}

	const WindowsScreenSystemParams& WindowsScreenSystemFactory::SystemParams() const noexcept
	{
		return systemParams;
	}

	bool WindowsScreenSystemFactory::IsCompatible(Core::IEngineSystem* const system) const noexcept
	{
		return dynamic_cast<WindowsScreenSystem*>(system);
	}

	void WindowsScreenSystemFactory::Destroy(Core::IEngineSystem* system) noexcept
	{
		assert(dynamic_cast<WindowsScreenSystem*>(system) && "Tried to destroy a system of the wrong type.");
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
