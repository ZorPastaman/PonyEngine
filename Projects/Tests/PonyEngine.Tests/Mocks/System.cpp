/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "System.h"

namespace Core
{
	System::System(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) noexcept :
		PonyEngine::Core::System(engine, params)
	{
	}

	System::~System() noexcept
	{
		if (onDestructed)
		{
			*onDestructed = true;
		}
	}

	void System::Begin()
	{
		++beginCount;
	}

	void System::End()
	{
		++endCount;
	}

	std::size_t System::BeginCount() const noexcept
	{
		return beginCount;
	}

	std::size_t System::EndCount() const noexcept
	{
		return endCount;
	}

	std::string_view System::Name() const noexcept
	{
		return "TestSystem";
	}
}
