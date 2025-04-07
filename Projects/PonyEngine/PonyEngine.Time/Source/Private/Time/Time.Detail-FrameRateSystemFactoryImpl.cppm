/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Detail:FrameRateSystemFactory;

import <memory>;

import PonyBase.Utility;

import PonyEngine.Core;
import PonyEngine.Time;

import :FrameRateSystem;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class FrameRateSystemFactoryImpl final : public FrameRateSystemFactory
	{
	public:
		/// @brief Creates a @p FrameRateSystemFactoryImpl.
		/// @param application Application context.
		/// @param factoryParams Frame rate system factory parameters.
		/// @param systemParams Frame rate system parameters.
		[[nodiscard("Pure constructor")]]
		FrameRateSystemFactoryImpl(Core::IApplicationContext& application, const FrameRateSystemFactoryParams& factoryParams, const FrameRateSystemParams& systemParams) noexcept;
		FrameRateSystemFactoryImpl(const FrameRateSystemFactoryImpl&) = delete;
		FrameRateSystemFactoryImpl(FrameRateSystemFactoryImpl&&) = delete;

		virtual ~FrameRateSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const Core::ISystemInfo& SystemInfo() const noexcept override;

		FrameRateSystemFactoryImpl& operator =(const FrameRateSystemFactoryImpl&) = delete;
		FrameRateSystemFactoryImpl& operator =(FrameRateSystemFactoryImpl&&) = delete;

	private:
		FrameRateSystemParams frameRateSystemParams; ///< Frame rate system parameters.
		Core::SystemInfo<FrameRateSystem, IFrameRateSystem> frameRateSystemInfo; ///< Frame rate system info.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Time
{
	FrameRateSystemFactoryImpl::FrameRateSystemFactoryImpl(Core::IApplicationContext& application, const FrameRateSystemFactoryParams&, const FrameRateSystemParams& systemParams) noexcept :
		frameRateSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData FrameRateSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		return frameRateSystemInfo.CreateSystemData(std::make_unique<FrameRateSystem>(engine, params, frameRateSystemParams));
	}

	const Core::ISystemInfo& FrameRateSystemFactoryImpl::SystemInfo() const noexcept
	{
		return frameRateSystemInfo;
	}
}
