/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Derived.h"

namespace Memory
{
	Derived::~Derived() noexcept
	{
		if (onDerivedDestructed)
		{
			*onDerivedDestructed = true;
		}
	}

	void Derived::SetOnDerivedDestructed(bool* const onDestructed) noexcept
	{
		onDerivedDestructed = onDestructed;
	}
}
