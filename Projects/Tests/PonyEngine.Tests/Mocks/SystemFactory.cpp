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

#include <utility>

import PonyBase.Memory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	PonyEngine::Core::SystemData SystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::EngineSystemParams& params)
	{
		Assert::IsNull(system);

		auto createdSystem = PonyBase::Memory::UniquePointer<System>::Create();
		system = createdSystem.Get();
		auto interfaces = PonyEngine::Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<ISystemInterface>(*system);

		return PonyEngine::Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<PonyEngine::Core::IEngineSystem>(std::move(createdSystem)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	PonyEngine::Core::SystemParams& SystemFactory::SystemParams() noexcept
	{
		return systemParams;
	}

	const PonyEngine::Core::SystemParams& SystemFactory::SystemParams() const noexcept
	{
		return systemParams;
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
