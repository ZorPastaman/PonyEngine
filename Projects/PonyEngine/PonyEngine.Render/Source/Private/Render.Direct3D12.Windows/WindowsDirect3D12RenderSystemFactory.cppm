/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows.Impl:WindowsDirect3D12RenderSystemFactory;

import <memory>;
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

import PonyEngine.Core.Factory;
import PonyEngine.Render.Direct3D12.Windows.Factory;

import :WindowsDirect3D12RenderSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows factory.
	class WindowsDirect3D12RenderSystemFactory final : public IWindowsDirect3D12RenderSystemFactory
	{
	public:
		/// @brief Creates a Direct3D 12 render system factory.
		/// @param application Application context.
		/// @param factoryParams Render system factory parameters.
		/// @param systemParams Render system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystemFactory(Core::IApplicationContext& application, const WindowsDirect3D12RenderSystemFactoryParams& factoryParams, const WindowsDirect3D12RenderSystemParams& systemParams) noexcept;
		WindowsDirect3D12RenderSystemFactory(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory(WindowsDirect3D12RenderSystemFactory&&) = delete;

		~WindowsDirect3D12RenderSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsDirect3D12RenderSystemFactory& operator =(const WindowsDirect3D12RenderSystemFactory&) = delete;
		WindowsDirect3D12RenderSystemFactory& operator =(WindowsDirect3D12RenderSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystemFactory"; ///< Class name.

	private:
		WindowsDirect3D12RenderSystemParams renderSystemParams; ///< Render system parameters

		Core::IApplicationContext* application; ///< Application.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystemFactory::WindowsDirect3D12RenderSystemFactory(Core::IApplicationContext& application, const WindowsDirect3D12RenderSystemFactoryParams&, const WindowsDirect3D12RenderSystemParams& systemParams) noexcept :
		renderSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData WindowsDirect3D12RenderSystemFactory::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
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

	std::string_view WindowsDirect3D12RenderSystemFactory::SystemName() const noexcept
	{
		return WindowsDirect3D12RenderSystem::StaticName;
	}

	std::string_view WindowsDirect3D12RenderSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
