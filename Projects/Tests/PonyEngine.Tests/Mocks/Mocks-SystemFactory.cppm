/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:SystemFactory;

import <cstddef>;
import <memory>;
import <utility>;

import PonyBase.Utility;

import PonyEngine.Core;

import :System;

export namespace Mocks
{
	class SystemFactory final : public PonyEngine::Core::ISystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual const PonyEngine::Core::ISystemInfo& SystemInfo() const noexcept override;

		[[nodiscard("Pure function")]]
		System* GetSystem() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;

	private:
		PonyEngine::Core::SystemInfo<System, ISystemInterface> systemInfo;
		System* createdSystem = nullptr;
		std::size_t version = 0;
	};
}

namespace Mocks
{
	PonyEngine::Core::SystemData SystemFactory::Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params)
	{
		auto system = std::make_shared<System>(engine, params);
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

	const PonyEngine::Core::ISystemInfo& SystemFactory::SystemInfo() const noexcept
	{
		return systemInfo;
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
