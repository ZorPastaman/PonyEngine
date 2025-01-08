/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Windows.Detail:WindowSystemFactoryImpl;

import <memory>;
import <typeinfo>;
import <utility>;

import PonyBase.Utility;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import :WindowSystem;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows window factory.
	class WindowSystemFactoryImpl final : public WindowSystemFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param application Application context.
		/// @param factoryParams Windows window system factory parameters.
		/// @param systemParams Windows window system parameters.
		[[nodiscard("Pure constructor")]]
		explicit WindowSystemFactoryImpl(Core::IApplicationContext& application, const WindowSystemFactoryParams& factoryParams, const WindowSystemParams& systemParams);
		WindowSystemFactoryImpl(const WindowSystemFactoryImpl&) = delete;
		WindowSystemFactoryImpl(WindowSystemFactoryImpl&&) = delete;

		virtual ~WindowSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const std::type_info& SystemType() const noexcept override;

		WindowSystemFactoryImpl& operator =(const WindowSystemFactoryImpl&) = delete;
		WindowSystemFactoryImpl& operator =(WindowSystemFactoryImpl&&) = delete;

	private:
		WindowSystemParams windowSystemParams; ///< Window system parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Window::Windows
{
	WindowSystemFactoryImpl::WindowSystemFactoryImpl(Core::IApplicationContext& application, const WindowSystemFactoryParams&, const WindowSystemParams& systemParams) :
		windowSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		auto system = std::make_unique<WindowSystem>(engine, params, windowSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<Window::IWindowSystem, IWindowSystem>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::TickableSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	const std::type_info& WindowSystemFactoryImpl::SystemType() const noexcept
	{
		return typeid(WindowSystem);
	}
}
