/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "TickableSystemFactory.h"

#include "CppUnitTest.h"

#include <utility>

import PonyBase.Memory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	PonyEngine::Core::SystemData TickableSystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::EngineSystemParams& params)
	{
		Assert::IsNull(system);

		auto tickableSystem = PonyBase::Memory::UniquePointer<TickableSystem>::Create();
		system = tickableSystem.Get();
		auto interfaces = PonyEngine::Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<ITickableSystemInterface>(*tickableSystem);

		return PonyEngine::Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<PonyEngine::Core::ITickableEngineSystem>(std::move(tickableSystem)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	PonyEngine::Core::SystemParams& TickableSystemFactory::SystemParams() noexcept
	{
		return systemParams;
	}

	const PonyEngine::Core::SystemParams& TickableSystemFactory::SystemParams() const noexcept
	{
		return systemParams;
	}

	TickableSystem* TickableSystemFactory::GetSystem() const noexcept
	{
		return system;
	}

	void TickableSystemFactory::Reset() noexcept
	{
		system = nullptr;
	}

	std::string_view TickableSystemFactory::SystemName() const noexcept
	{
		return "TestTickableSystem";
	}

	std::string_view TickableSystemFactory::Name() const noexcept
	{
		return "TestTickableSystemFactory";
	}
}
