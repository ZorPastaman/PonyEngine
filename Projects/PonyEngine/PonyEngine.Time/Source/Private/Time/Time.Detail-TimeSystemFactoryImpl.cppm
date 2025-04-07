/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Detail:TimeSystemFactoryImpl;

import <memory>;

import PonyBase.Utility;

import PonyEngine.Core;
import PonyEngine.Time;

import :TimeSystem;

export namespace PonyEngine::Time
{
	/// @brief Time system factory.
	class TimeSystemFactoryImpl final : public TimeSystemFactory
	{
	public:
		/// @brief Creates a @p TimeSystemFactoryImpl.
		/// @param application Application context.
		/// @param factoryParams Time system factory parameters.
		/// @param systemParams Time system parameters.
		[[nodiscard("Pure constructor")]]
		TimeSystemFactoryImpl(Core::IApplicationContext& application, const TimeSystemFactoryParams& factoryParams, const TimeSystemParams& systemParams) noexcept;
		TimeSystemFactoryImpl(const TimeSystemFactoryImpl&) = delete;
		TimeSystemFactoryImpl(TimeSystemFactoryImpl&&) = delete;

		virtual ~TimeSystemFactoryImpl() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const Core::ISystemInfo& SystemInfo() const noexcept override;

		TimeSystemFactoryImpl& operator =(const TimeSystemFactoryImpl&) = delete;
		TimeSystemFactoryImpl& operator =(TimeSystemFactoryImpl&&) = delete;

	private:
		TimeSystemParams timeSystemParams; ///< Time system parameters.
		Core::SystemInfo<TimeSystem, ITimeSystem> timeSystemInfo; ///< Time system info.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Time
{
	TimeSystemFactoryImpl::TimeSystemFactoryImpl(Core::IApplicationContext& application, const TimeSystemFactoryParams&, const TimeSystemParams& systemParams) noexcept :
		timeSystemParams(systemParams),
		application{&application}
	{
	}

	Core::SystemData TimeSystemFactoryImpl::Create(Core::IEngineContext& engine, const Core::SystemParams& params)
	{
		return timeSystemInfo.CreateSystemData(std::make_unique<TimeSystem>(engine, params, timeSystemParams));
	}

	const Core::ISystemInfo& TimeSystemFactoryImpl::SystemInfo() const noexcept
	{
		return timeSystemInfo;
	}
}
