/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Base.h"

namespace Memory
{
	Base::~Base() noexcept
	{
		if (onBaseDestructed)
		{
			*onBaseDestructed = true;
		}
	}

	void Base::SetOnBaseDestructed(bool* const onDestructed)
	{
		onBaseDestructed = onDestructed;
	}
}
