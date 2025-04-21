/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows.Detail:RenderSystemFactory;

import <memory>;

import PonyBase.Utility;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows;

import :RenderSystem;

export namespace PonyEngine::Render::Direct3D12::Windows
{
	/// @brief Direct3D 12 render system for Windows factory.
	class RenderSystemFactoryImpl final : public RenderSystemFactory
	{
	public:
		/// @brief Creates a Direct3D 12 render system factory.
		/// @param application Application context.
		/// @param factoryParams Render system factory parameters.
		/// @param systemParams Render system parameters.
		[[nodiscard("Pure constructor")]]
		RenderSystemFactoryImpl(Core::IApplicationContext& application, const RenderSystemFactoryParams& factoryParams, const RenderSystemParams& systemParams) noexcept;
		RenderSystemFactoryImpl(const RenderSystemFactoryImpl&) = delete;
		RenderSystemFactoryImpl(RenderSystemFactoryImpl&&) = delete;

		virtual ~RenderSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const Core::ISystemInfo& SystemInfo() const noexcept override;

		RenderSystemFactoryImpl& operator =(const RenderSystemFactoryImpl&) = delete;
		RenderSystemFactoryImpl& operator =(RenderSystemFactoryImpl&&) = delete;

	private:
		RenderSystemParams renderSystemParams; ///< Render system parameters
		Core::SystemInfo<RenderSystem, Render::IRenderSystem, Direct3D12::IRenderSystem, IRenderSystem> renderSystemInfo; ///< Render system info.

		Core::IApplicationContext* application; ///< Application.
	};
}

namespace PonyEngine::Render::Direct3D12::Windows
{
	RenderSystemFactoryImpl::RenderSystemFactoryImpl(Core::IApplicationContext& application, const RenderSystemFactoryParams&, const RenderSystemParams& systemParams) noexcept :
		renderSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData RenderSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		return renderSystemInfo.CreateSystemData(std::make_unique<RenderSystem>(engine, params, renderSystemParams));
	}

	const Core::ISystemInfo& RenderSystemFactoryImpl::SystemInfo() const noexcept
	{
		return renderSystemInfo;
	}
}
