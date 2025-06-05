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
		virtual const Core::ISystemInfo& SystemInfo() const noexcept override;

		WindowSystemFactoryImpl& operator =(const WindowSystemFactoryImpl&) = delete;
		WindowSystemFactoryImpl& operator =(WindowSystemFactoryImpl&&) = delete;

	private:
		WindowSystemParams windowSystemParams; ///< Window system parameters.
		Core::SystemInfo<WindowSystem, Window::IWindowSystem, IWindowSystem> windowSystemInfo; ///< Window system info.

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
		return windowSystemInfo.CreateSystemData(std::make_shared<WindowSystem>(engine, params, windowSystemParams));
	}

	const Core::ISystemInfo& WindowSystemFactoryImpl::SystemInfo() const noexcept
	{
		return windowSystemInfo;
	}
}
