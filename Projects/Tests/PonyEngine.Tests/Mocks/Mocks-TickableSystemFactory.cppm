/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:TickableSystemFactory;

import <cstddef>;
import <memory>;
import <typeinfo>;
import <utility>;

import PonyBase.Utility;

import PonyEngine.Core;

import :TickableSystem;

export namespace Mocks
{
	class TickableSystemFactory final : public PonyEngine::Core::ISystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) override;
		[[nodiscard("Pure function")]]
		virtual const type_info& SystemType() const noexcept override;

		[[nodiscard("Pure function")]]
		TickableSystem* GetSystem() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;

	private:
		TickableSystem* createdSystem = nullptr;
		std::size_t version = 0;
	};
}

namespace Mocks
{
	PonyEngine::Core::SystemData TickableSystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
	{
		auto system = std::make_unique<TickableSystem>(engine, params);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<ITickableSystemInterface>(*system);

		createdSystem = system.get();
		++version;

		return PonyEngine::Core::SystemData
		{
			.system = std::unique_ptr<PonyEngine::Core::TickableSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	const type_info& TickableSystemFactory::SystemType() const noexcept
	{
		return typeid(TickableSystem);
	}

	TickableSystem* TickableSystemFactory::GetSystem() const noexcept
	{
		return createdSystem;
	}

	std::size_t TickableSystemFactory::Version() const noexcept
	{
		return version;
	}
}
