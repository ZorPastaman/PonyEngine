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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Detail:WindowsWindowSystemFactory;

import <cstdint>;
import <exception>;
import <format>;
import <stdexcept>;
import <string>;
import <string_view>;
import <utility>;

import PonyBase.Memory;
import PonyBase.ObjectUtility;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Window.Windows;

import :IWindowProc;
import :WindowsWindowSystem;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class WindowsWindowSystemFactory final : public IWindowsWindowSystemFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param application Application context.
		/// @param factoryParams Windows window system factory parameters.
		/// @param systemParams Windows window system parameters.
		[[nodiscard("Pure constructor")]]
		explicit WindowsWindowSystemFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams& factoryParams, const WindowsWindowSystemParams& systemParams);
		WindowsWindowSystemFactory(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory(WindowsWindowSystemFactory&&) = delete;

		~WindowsWindowSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsWindowSystemFactory& operator =(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory& operator =(WindowsWindowSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Window::WindowsWindowSystemFactory"; ///< Class name.

	private:
		WindowsWindowSystemParams windowSystemParams; ///< Window system parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Window
{
	WindowsWindowSystemFactory::WindowsWindowSystemFactory(Core::IApplicationContext& application, const WindowsWindowSystemFactoryParams&, const WindowsWindowSystemParams& systemParams) :
		windowSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowsWindowSystemFactory::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
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

	std::string_view WindowsWindowSystemFactory::SystemName() const noexcept
	{
		return WindowsWindowSystem::StaticName;
	}

	std::string_view WindowsWindowSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
