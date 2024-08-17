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

import PonyEngine.Core.Factory;
import PonyEngine.Time.Factory;

import :FrameRateSystem;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class FrameRateSystemFactory final : public IFrameRateSystemFactory, public Core::ISystemDestroyer
	{
	public:
		[[nodiscard("Pure constructor")]]
		FrameRateSystemFactory() noexcept = default;
		FrameRateSystemFactory(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory(FrameRateSystemFactory&&) = delete;

		~FrameRateSystemFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual Core::SystemUniquePtr Create(Core::IEngine& engine) override;
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
	Core::SystemUniquePtr FrameRateSystemFactory::Create(Core::IEngine& engine)
	{
		return Core::SystemUniquePtr(new FrameRateSystem(engine), Core::SystemDeleter(*this));
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
