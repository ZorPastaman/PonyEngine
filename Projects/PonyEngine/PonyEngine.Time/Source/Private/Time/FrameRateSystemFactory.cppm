/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Time.Implementation:FrameRateSystemFactory;

import <string_view>;
import <utility>;

import PonyBase.Memory;

import PonyEngine.Core.Factory;
import PonyEngine.Time.Factory;

import :FrameRateSystem;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class FrameRateSystemFactory final : public IFrameRateSystemFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		FrameRateSystemFactory() noexcept = default;
		FrameRateSystemFactory(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory(FrameRateSystemFactory&&) = delete;

		~FrameRateSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::EngineSystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual FrameRateSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const FrameRateSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		FrameRateSystemFactory& operator =(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory& operator =(FrameRateSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Time::FrameRateSystemFactory"; ///< Class name.

	private:
		FrameRateSystemParams frameRateSystemParams;
	};
}

namespace PonyEngine::Time
{
	Core::SystemData FrameRateSystemFactory::Create(Core::IEngineContext& engine, const Core::EngineSystemParams&)
	{
		auto system = PonyBase::Memory::UniquePointer<FrameRateSystem>::Create(engine);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IFrameRateSystem>(*system);

		return Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<Core::ITickableEngineSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	FrameRateSystemParams& FrameRateSystemFactory::SystemParams() noexcept
	{
		return frameRateSystemParams;
	}

	const FrameRateSystemParams& FrameRateSystemFactory::SystemParams() const noexcept
	{
		return frameRateSystemParams;
	}

	std::string_view FrameRateSystemFactory::SystemName() const noexcept
	{
		return FrameRateSystem::StaticName;
	}

	std::string_view FrameRateSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
