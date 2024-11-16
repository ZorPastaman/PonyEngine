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
import <string_view>;
import <utility>;

import PonyBase.ObjectUtility;

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

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		FrameRateSystemFactoryImpl& operator =(const FrameRateSystemFactoryImpl&) = delete;
		FrameRateSystemFactoryImpl& operator =(FrameRateSystemFactoryImpl&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Time::FrameRateSystemFactoryImpl"; ///< Class name.

	private:
		FrameRateSystemParams frameRateSystemParams; //< Frame rate system parameters.

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
		auto system = std::make_unique<FrameRateSystem>(engine, params, frameRateSystemParams);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IFrameRateSystem>(*system);

		return Core::SystemData
		{
			.system = std::unique_ptr<Core::TickableSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	std::string_view FrameRateSystemFactoryImpl::SystemName() const noexcept
	{
		return FrameRateSystem::StaticName;
	}

	std::string_view FrameRateSystemFactoryImpl::Name() const noexcept
	{
		return StaticName;
	}
}
