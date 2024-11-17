/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "SystemFactory.h"

#include <memory>
#include <utility>

import PonyBase.ObjectUtility;

namespace Core
{
	PonyEngine::Core::SystemData SystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
	{
		auto system = std::make_unique<System>(engine, params);
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<ISystemInterface>(*system);

		createdSystem = system.get();
		++version;

		return PonyEngine::Core::SystemData
		{
			.system = std::move(system),
			.publicInterfaces = std::move(interfaces)
		};
	}

	const type_info& SystemFactory::SystemType() const noexcept
	{
		return typeid(System);
	}

	System* SystemFactory::GetSystem() const noexcept
	{
		return createdSystem;
	}

	std::size_t SystemFactory::Version() const noexcept
	{
		return version;
	}
}
