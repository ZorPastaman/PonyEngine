/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "SystemFactory.h"

#include "CppUnitTest.h"

#include <memory>
#include <utility>

import PonyBase.Memory;
import PonyBase.ObjectUtility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	PonyEngine::Core::SystemData SystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
	{
		Assert::IsNull(system);

		auto createdSystem = std::make_unique<System>(engine, params);
		system = createdSystem.get();
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<ISystemInterface>(*system);

		return PonyEngine::Core::SystemData
		{
			.system = std::move(createdSystem),
			.publicInterfaces = std::move(interfaces)
		};
	}

	System* SystemFactory::GetSystem() const noexcept
	{
		return system;
	}

	void SystemFactory::Reset() noexcept
	{
		system = nullptr;
	}

	std::string_view SystemFactory::SystemName() const noexcept
	{
		return "TestSystem";
	}

	std::string_view SystemFactory::Name() const noexcept
	{
		return "TestSystemFactory";
	}
}
