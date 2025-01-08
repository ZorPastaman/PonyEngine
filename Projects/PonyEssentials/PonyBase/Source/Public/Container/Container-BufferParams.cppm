/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Container:BufferParams;

import <cstdint>;

export namespace PonyBase::Container
{
	struct BufferParams final
	{
		std::uint32_t stride = 0u;
		std::uint32_t count = 0u;
	};
}
