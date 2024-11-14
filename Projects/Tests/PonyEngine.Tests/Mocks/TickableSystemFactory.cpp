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

#include <memory>
#include <utility>

import PonyBase.Memory;
import PonyBase.ObjectUtility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	PonyEngine::Core::SystemData TickableSystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
	{
		Assert::IsNull(system);

		auto tickableSystem = std::make_unique<TickableSystem>(engine, params);
		system = tickableSystem.get();
		auto interfaces = PonyBase::Utility::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<ITickableSystemInterface>(*tickableSystem);

		return PonyEngine::Core::SystemData
		{
			.system = std::unique_ptr<PonyEngine::Core::TickableSystem>(std::move(tickableSystem)),
			.publicInterfaces = std::move(interfaces)
		};
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
