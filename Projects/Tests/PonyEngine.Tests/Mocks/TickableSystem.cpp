/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "TickableSystem.h"

namespace Core
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
