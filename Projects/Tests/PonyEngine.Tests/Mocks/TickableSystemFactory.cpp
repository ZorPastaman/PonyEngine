/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "TickableSystemFactory.h"

#include <memory>
#include <utility>

import PonyBase.ObjectUtility;

namespace Core
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
