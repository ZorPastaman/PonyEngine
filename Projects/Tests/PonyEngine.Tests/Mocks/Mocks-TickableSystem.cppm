/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module Mocks:TickableSystem;

import <cstddef>;

import PonyEngine.Core;

export namespace Mocks
{
	class ITickableSystemInterface
	{
		INTERFACE_BODY(ITickableSystemInterface)
	};

	class TickableSystem final : public PonyEngine::Core::TickableSystem, public ITickableSystemInterface
	{
	public:
		[[nodiscard("Pure constructor")]]
		TickableSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) noexcept;
		[[nodiscard("Pure constructor")]]
		TickableSystem(const TickableSystem& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		TickableSystem(TickableSystem&& other) noexcept = default;

		virtual ~TickableSystem() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		std::size_t BeginCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t EndCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t TickCount() const noexcept;

		TickableSystem& operator =(const TickableSystem& other) noexcept = default;
		TickableSystem& operator =(TickableSystem&& other) noexcept = default;

		bool* onDestructed = nullptr;

	private:
		std::size_t beginCount = 0;
		std::size_t endCount = 0;
		std::size_t tickCount = 0;
	};
}

namespace Mocks
{
	TickableSystem::TickableSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) noexcept :
		PonyEngine::Core::TickableSystem(engine, params)
	{
	}

	TickableSystem::~TickableSystem() noexcept
	{
		if (onDestructed)
		{
			*onDestructed = true;
		}
	}

	void TickableSystem::Begin()
	{
		++beginCount;
	}

	void TickableSystem::End()
	{
		++endCount;
	}

	void TickableSystem::Tick()
	{
		++tickCount;
	}

	std::size_t TickableSystem::BeginCount() const noexcept
	{
		return beginCount;
	}

	std::size_t TickableSystem::EndCount() const noexcept
	{
		return endCount;
	}

	std::size_t TickableSystem::TickCount() const noexcept
	{
		return tickCount;
	}
}
