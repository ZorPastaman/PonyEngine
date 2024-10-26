/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "DerivedWithParams.h"

namespace Memory
{
	DerivedWithParams::DerivedWithParams(const int i, const bool b) noexcept :
		iParam{i},
		bParam{b}
	{
	}

	int DerivedWithParams::GetIParam() const noexcept
	{
		return iParam;
	}

	bool DerivedWithParams::GetBParam() const noexcept
	{
		return bParam;
	}
}
