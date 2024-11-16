/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows.Detail:WindowsDirect3D12RenderSystemFactory;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows;

import :WindowsDirect3D12RenderSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory.
	class WindowsDirect3D12RenderSystemFactoryImpl final : public RenderSystemFactory
	{
	public:
		/// @brief Creates a Direct3D 12 render system factory.
		/// @param application Application context.
		/// @param factoryParams Render system factory parameters.
		/// @param systemParams Render system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystemFactoryImpl(Core::IApplicationContext& application, const WindowsDirect3D12RenderSystemFactoryParams& factoryParams, const WindowsDirect3D12RenderSystemParams& systemParams) noexcept;
		WindowsDirect3D12RenderSystemFactoryImpl(const WindowsDirect3D12RenderSystemFactoryImpl&) = delete;
		WindowsDirect3D12RenderSystemFactoryImpl(WindowsDirect3D12RenderSystemFactoryImpl&&) = delete;

		virtual ~WindowsDirect3D12RenderSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsDirect3D12RenderSystemFactoryImpl& operator =(const WindowsDirect3D12RenderSystemFactoryImpl&) = delete;
		WindowsDirect3D12RenderSystemFactoryImpl& operator =(WindowsDirect3D12RenderSystemFactoryImpl&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystemFactoryImpl"; ///< Class name.

	private:
		WindowsDirect3D12RenderSystemParams renderSystemParams; ///< Render system parameters

		Core::IApplicationContext* application; ///< Application.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystemFactoryImpl::WindowsDirect3D12RenderSystemFactoryImpl(Core::IApplicationContext& application, const WindowsDirect3D12RenderSystemFactoryParams&, const WindowsDirect3D12RenderSystemParams& systemParams) noexcept :
		renderSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowsDirect3D12RenderSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		auto system = std::make_unique<WindowsDirect3D12RenderSystem>(engine, params, renderSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IRenderSystem, IDirect3D12RenderSystem, IWindowsDirect3D12RenderSystem>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::TickableSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	std::string_view WindowsDirect3D12RenderSystemFactoryImpl::SystemName() const noexcept
	{
		return WindowsDirect3D12RenderSystem::StaticName;
	}

	std::string_view WindowsDirect3D12RenderSystemFactoryImpl::Name() const noexcept
	{
		return StaticName;
	}
}
