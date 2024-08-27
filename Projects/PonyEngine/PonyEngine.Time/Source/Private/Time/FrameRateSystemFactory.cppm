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

import <utility>;

import PonyEngine.Core.Factory;
import PonyEngine.Time.Factory;

import :FrameRateSystem;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class FrameRateSystemFactory final : public Core::ISystemFactory, public Core::ISystemDestroyer
	{
	public:
		[[nodiscard("Pure constructor")]]
		FrameRateSystemFactory() noexcept = default;
		FrameRateSystemFactory(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory(FrameRateSystemFactory&&) = delete;

		~FrameRateSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(const Core::SystemParams& params) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		FrameRateSystemFactory& operator =(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory& operator =(FrameRateSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Time::FrameRateSystemFactory"; ///< Class name.
	};
}

namespace PonyEngine::Time
{
	Core::SystemData FrameRateSystemFactory::Create(const Core::SystemParams& params)
	{
		const auto system = new FrameRateSystem(params.engine);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IFrameRateSystem>(*system);

		return Core::SystemData
		{
			.system = Core::SystemUniquePtr(system, Core::SystemDeleter(*this)),
			.tickableSystem = system,
			.publicInterfaces = std::move(interfaces)
		};
	}

	void FrameRateSystemFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<FrameRateSystem*>(system) && "Tried to destroy a system of the wrong type."));
		delete static_cast<FrameRateSystem*>(system);
	}

	const char* FrameRateSystemFactory::SystemName() const noexcept
	{
		return FrameRateSystem::StaticName;
	}

	const char* FrameRateSystemFactory::Name() const noexcept
	{
		return StaticName;
	}
}
