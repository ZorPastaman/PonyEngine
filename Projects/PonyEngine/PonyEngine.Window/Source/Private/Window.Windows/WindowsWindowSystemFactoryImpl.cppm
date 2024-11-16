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

export module PonyEngine.Window.Windows.Detail:WindowsWindowSystemFactoryImpl;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import :WindowsWindowSystem;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class WindowsWindowSystemFactoryImpl final : public WindowSystemFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param application Application context.
		/// @param factoryParams Windows window system factory parameters.
		/// @param systemParams Windows window system parameters.
		[[nodiscard("Pure constructor")]]
		explicit WindowsWindowSystemFactoryImpl(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& factoryParams, const WindowsWindowSystemParams& systemParams);
		WindowsWindowSystemFactoryImpl(const WindowsWindowSystemFactoryImpl&) = delete;
		WindowsWindowSystemFactoryImpl(WindowsWindowSystemFactoryImpl&&) = delete;

		virtual ~WindowsWindowSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsWindowSystemFactoryImpl& operator =(const WindowsWindowSystemFactoryImpl&) = delete;
		WindowsWindowSystemFactoryImpl& operator =(WindowsWindowSystemFactoryImpl&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Window::WindowsWindowSystemFactoryImpl"; ///< Class name.

	private:
		WindowsWindowSystemParams windowSystemParams; ///< Window system parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystemFactoryImpl::WindowsWindowSystemFactoryImpl(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams&, const WindowsWindowSystemParams& systemParams) :
		windowSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowsWindowSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		auto system = std::make_unique<WindowsWindowSystem>(engine, params, windowSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IWindowSystem, IWindowsWindowSystem, Input::IKeyboardProvider>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::TickableSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	std::string_view WindowsWindowSystemFactoryImpl::SystemName() const noexcept
	{
		return WindowsWindowSystem::StaticName;
	}

	std::string_view WindowsWindowSystemFactoryImpl::Name() const noexcept
	{
		return StaticName;
	}
}
